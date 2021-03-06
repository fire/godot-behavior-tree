#ifndef VISUAL_BRAIN_TREE_BEHAVIOR_TREE_H
#define VISUAL_BRAIN_TREE_BEHAVIOR_TREE_H

#include "brain_tree_behavior_tree.h"

class VisualBrainTreeBehaviorTreeNode;
class VisualBrainTreeBehaviorTreeNodeComponent;

class VisualBrainTreeBehaviorTree : public BrainTreeBehaviorTree {
	GDCLASS(VisualBrainTreeBehaviorTree, BrainTreeBehaviorTree);

	Ref<VisualBrainTreeBehaviorTreeNodeComponent> component; // default, tree root

	void _update_noise();
	void _queue_update();

	volatile mutable bool dirty;

protected:
	static void _bind_methods();

public:
	void generate();

	void set_component(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_component);
	Ref<VisualBrainTreeBehaviorTreeNodeComponent> get_component() const;

	VisualBrainTreeBehaviorTree();
};

class VisualBrainTreeBehaviorTreeNode : public Resource {
	GDCLASS(VisualBrainTreeBehaviorTreeNode, Resource)

	int port_preview;

	Map<int, Variant> default_input_values;

	Array _get_default_input_values() const;
	void _set_default_input_values(const Array &p_values);

protected:
	Variant output_value;

	static void _bind_methods();

public:
	enum PortType {
		PORT_TYPE_SCALAR,
		PORT_TYPE_INDEX,
	};

	virtual String get_caption() const = 0;

	virtual int get_input_port_count() const = 0;
	virtual PortType get_input_port_type(int p_port) const = 0;
	virtual String get_input_port_name(int p_port) const = 0;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;

	void set_input_port_default_value(int p_port, const Variant &p_value);
	Variant get_input_port_default_value(int p_port) const; // if NIL (default if node does not set anything) is returned, it means no default value is wanted if disconnected, thus no input var must be supplied (empty string will be supplied)

	virtual int get_output_port_count() const = 0;
	virtual PortType get_output_port_type(int p_port) const = 0;
	virtual String get_output_port_name(int p_port) const = 0;

	virtual void set_output_port_value(int p_port, const Variant &p_value);
	virtual Variant get_output_port_value(int p_port) const;

	void set_output_port_for_preview(int p_index);
	int get_output_port_for_preview() const;

	virtual bool is_port_separator(int p_index) const;

	virtual Vector<StringName> get_editable_properties() const;

	virtual String get_warning() const;

	virtual void evaluate(Ref<VisualBrainTreeBehaviorTree> noise);

	VisualBrainTreeBehaviorTreeNode();
};

class VisualBrainTreeBehaviorTreeNodeComponent : public VisualBrainTreeBehaviorTreeNode {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeComponent, VisualBrainTreeBehaviorTreeNode)

	friend class VisualBrainTreeBehaviorTree;

public:
	struct Connection {
		int from_node;
		int from_port;
		int to_node;
		int to_port;
	};

private:
	StringName name;

	struct Node {
		Ref<VisualBrainTreeBehaviorTreeNode> node;
		Vector2 position;
	};

	struct Graph {
		Map<int, Node> nodes;
		List<Connection> connections;
	} graph;

	union ConnectionKey {

		struct {
			uint64_t node : 32;
			uint64_t port : 32;
		};
		uint64_t key;
		bool operator<(const ConnectionKey &p_key) const {
			return key < p_key.key;
		}
	};

	Vector2 graph_offset;

	Array _get_node_connections() const;

protected:
	static void _bind_methods();

	bool _set(const StringName &p_name, const Variant &p_value);
	bool _get(const StringName &p_name, Variant &r_ret) const;
	void _get_property_list(List<PropertyInfo> *p_list) const;

public:
	using Connections = VMap<ConnectionKey, const List<Connection>::Element *>;

	enum {
		NODE_ID_INVALID = -1,
		NODE_ID_OUTPUT = 0,
	};

	void set_component_name(const String &p_name);
	String get_component_name() const;

	void add_node(const Ref<VisualBrainTreeBehaviorTreeNode> &p_node, const Vector2 &p_position, int p_id);
	void set_node_position(int p_id, const Vector2 &p_position);

	Vector2 get_node_position(int p_id) const;
	Ref<VisualBrainTreeBehaviorTreeNode> get_node(int p_id) const;

	Vector<int> get_node_list() const;
	int get_valid_node_id() const;

	int find_node_id(const Ref<VisualBrainTreeBehaviorTreeNode> &p_node) const;
	void remove_node(int p_id);

	void evaluate_node(int p_id, Ref<VisualBrainTreeBehaviorTree> noise, Connections &input_connections, Connections &output_connections, Set<int> &processed);

	bool is_node_connection(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const;
	bool can_connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const;
	Error connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port);
	void disconnect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port);

	void get_node_connections(List<Connection> *r_connections) const;

	void set_graph_offset(const Vector2 &p_offset);
	Vector2 get_graph_offset() const;

	// String generate_preview_noise(int p_node, int p_port) const;

	VisualBrainTreeBehaviorTreeNodeComponent();

public:
	virtual String get_caption() const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void evaluate(Ref<VisualBrainTreeBehaviorTree> p_noise);
};

class VisualBrainTreeBehaviorTreeNodeInput : public VisualBrainTreeBehaviorTreeNode {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeInput, VisualBrainTreeBehaviorTreeNode)

public:
	friend class VisualBrainTreeBehaviorTree;

	struct Port {
		PortType type;
		const char *name;
		const char *string;
	};

	static const Port ports[];

public:
	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;

	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	Variant get_input_port_default_value(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	virtual void set_output_port_value(int p_port, const Variant &p_value);
	virtual Variant get_output_port_value(int p_port) const;

	virtual bool is_port_separator(int p_index) const;

	virtual String get_caption() const;

	VisualBrainTreeBehaviorTreeNodeInput();
};

class BehaviourTreePlayer : public Node {
	GDCLASS(BehaviourTreePlayer, Node);
	OBJ_CATEGORY("Behaviour Trees");
	Error add_animation(const StringName &p_name, const Ref<BrainTreeBehaviorTree> &p_) {
		return OK;
	}
	void remove_animation(const StringName &p_name) {
	}
};
#endif
