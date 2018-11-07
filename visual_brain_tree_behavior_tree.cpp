#include "visual_brain_tree_behavior_tree.h"
#include "visual_brain_tree_behavior_tree_nodes.h"
#include "core/vmap.h"

void VisualBrainTreeBehaviorTreeNode::set_output_port_for_preview(int p_index) {

	port_preview = p_index;
}

int VisualBrainTreeBehaviorTreeNode::get_output_port_for_preview() const {

	return port_preview;
}

void VisualBrainTreeBehaviorTreeNode::set_input_port_value(int p_port, const Variant &p_value) {

	// nothing to set
}

Variant VisualBrainTreeBehaviorTreeNode::get_input_port_value(int p_port) const {

	return Variant();
}

void VisualBrainTreeBehaviorTreeNode::set_input_port_default_value(int p_port, const Variant &p_value) {

	default_input_values[p_port] = p_value;
	emit_changed();
}

Variant VisualBrainTreeBehaviorTreeNode::get_input_port_default_value(int p_port) const {

	if (default_input_values.has(p_port)) {
		return default_input_values[p_port];
	}
	return Variant();
}

bool VisualBrainTreeBehaviorTreeNode::is_port_separator(int p_index) const {

	return false;
}

Vector<StringName> VisualBrainTreeBehaviorTreeNode::get_editable_properties() const {
	return Vector<StringName>();
}

Array VisualBrainTreeBehaviorTreeNode::_get_default_input_values() const {

	Array ret;
	for (Map<int, Variant>::Element *E = default_input_values.front(); E; E = E->next()) {
		ret.push_back(E->key());
		ret.push_back(E->get());
	}
	return ret;
}

void VisualBrainTreeBehaviorTreeNode::_set_default_input_values(const Array &p_values) {

	if (p_values.size() % 2 == 0) {
		for (int i = 0; i < p_values.size(); i += 2) {
			default_input_values[p_values[i + 0]] = p_values[i + 1];
		}
	}

	emit_changed();
}

String VisualBrainTreeBehaviorTreeNode::get_warning() const {
	return String();
}

void VisualBrainTreeBehaviorTreeNode::set_output_port_value(int p_port, const Variant &p_value) {

	// nothing to do
}

Variant VisualBrainTreeBehaviorTreeNode::get_output_port_value(int p_port) const {

	return output_value;
}

void VisualBrainTreeBehaviorTreeNode::evaluate(Ref<VisualBrainTreeBehaviorTree> noise) {

	// nothing to do
}

void VisualBrainTreeBehaviorTreeNode::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_output_port_for_preview", "port"), &VisualBrainTreeBehaviorTreeNode::set_output_port_for_preview);
	ClassDB::bind_method(D_METHOD("get_output_port_for_preview"), &VisualBrainTreeBehaviorTreeNode::get_output_port_for_preview);

	ClassDB::bind_method(D_METHOD("set_input_port_default_value", "port", "value"), &VisualBrainTreeBehaviorTreeNode::set_input_port_default_value);
	ClassDB::bind_method(D_METHOD("get_input_port_default_value", "port"), &VisualBrainTreeBehaviorTreeNode::get_input_port_default_value);

	ClassDB::bind_method(D_METHOD("_set_default_input_values", "values"), &VisualBrainTreeBehaviorTreeNode::_set_default_input_values);
	ClassDB::bind_method(D_METHOD("_get_default_input_values"), &VisualBrainTreeBehaviorTreeNode::_get_default_input_values);

	ADD_PROPERTY(PropertyInfo(Variant::INT, "output_port_for_preview"), "set_output_port_for_preview", "get_output_port_for_preview");
	ADD_PROPERTYNZ(PropertyInfo(Variant::ARRAY, "default_input_values", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "_set_default_input_values", "_get_default_input_values");
	ADD_SIGNAL(MethodInfo("editor_refresh_request"));
}

VisualBrainTreeBehaviorTreeNode::VisualBrainTreeBehaviorTreeNode() {

	port_preview = -1;
}

/////////////////////////////////////////////////////////

void VisualBrainTreeBehaviorTreeNodeComponent::set_component_name(const String &p_name) {

	name = p_name;
}

String VisualBrainTreeBehaviorTreeNodeComponent::get_component_name() const {

	return name;
}

void VisualBrainTreeBehaviorTreeNodeComponent::add_node(const Ref<VisualBrainTreeBehaviorTreeNode> &p_node, const Vector2 &p_position, int p_id) {

	ERR_FAIL_COND(p_node.is_null());
	ERR_FAIL_COND(p_id < 2);
	ERR_FAIL_COND(graph.nodes.has(p_id));

	Node n;
	n.node = p_node;
	n.position = p_position;

	// n.node->connect("changed", this, "_queue_update");

	graph.nodes[p_id] = n;

	// _queue_update();
}

void VisualBrainTreeBehaviorTreeNodeComponent::set_node_position(int p_id, const Vector2 &p_position) {

	ERR_FAIL_COND(!graph.nodes.has(p_id));

	graph.nodes[p_id].position = p_position;
}

Vector2 VisualBrainTreeBehaviorTreeNodeComponent::get_node_position(int p_id) const {

	ERR_FAIL_COND_V(!graph.nodes.has(p_id), Vector2());

	return graph.nodes[p_id].position;
}

Ref<VisualBrainTreeBehaviorTreeNode> VisualBrainTreeBehaviorTreeNodeComponent::get_node(int p_id) const {

	ERR_FAIL_COND_V(!graph.nodes.has(p_id), Ref<VisualBrainTreeBehaviorTreeNode>());

	return graph.nodes[p_id].node;
}

Vector<int> VisualBrainTreeBehaviorTreeNodeComponent::get_node_list() const {

	Vector<int> ret;
	for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		ret.push_back(E->key());
	}

	return ret;
}

int VisualBrainTreeBehaviorTreeNodeComponent::get_valid_node_id() const {

	return graph.nodes.size() ? MAX(2, graph.nodes.back()->key() + 1) : 2;
}

int VisualBrainTreeBehaviorTreeNodeComponent::find_node_id(const Ref<VisualBrainTreeBehaviorTreeNode> &p_node) const {

	for (const Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {
		if (E->get().node == p_node)
			return E->key();
	}

	return NODE_ID_INVALID;
}

void VisualBrainTreeBehaviorTreeNodeComponent::remove_node(int p_id) {

	ERR_FAIL_COND(p_id < 2);

	ERR_FAIL_COND(!graph.nodes.has(p_id));

	// graph.nodes[p_id].node->disconnect("changed", this, "_queue_update");

	graph.nodes.erase(p_id);

	for (List<Connection>::Element *E = graph.connections.front(); E;) {
		List<Connection>::Element *N = E->next();
		if (E->get().from_node == p_id || E->get().to_node == p_id) {
			graph.connections.erase(E);
		}
		E = N;
	}

	// _queue_update();
}

bool VisualBrainTreeBehaviorTreeNodeComponent::is_node_connection(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const {

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			return true;
		}
	}

	return false;
}

bool VisualBrainTreeBehaviorTreeNodeComponent::can_connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) const {

	if (!graph.nodes.has(p_from_node))
		return false;

	if (p_from_port < 0 || p_from_port >= graph.nodes[p_from_node].node->get_output_port_count())
		return false;

	if (!graph.nodes.has(p_to_node))
		return false;

	if (p_to_port < 0 || p_to_port >= graph.nodes[p_to_node].node->get_input_port_count())
		return false;

	VisualBrainTreeBehaviorTreeNode::PortType from_port_type = graph.nodes[p_from_node].node->get_output_port_type(p_from_port);
	VisualBrainTreeBehaviorTreeNode::PortType to_port_type = graph.nodes[p_to_node].node->get_input_port_type(p_to_port);

	if (MAX(0, from_port_type - 1) != (MAX(0, to_port_type - 1))) {
		return false;
	}

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			return false;
		}
	}

	return true;
}

Error VisualBrainTreeBehaviorTreeNodeComponent::connect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) {

	ERR_FAIL_COND_V(!graph.nodes.has(p_from_node), ERR_INVALID_PARAMETER);
	ERR_FAIL_INDEX_V(p_from_port, graph.nodes[p_from_node].node->get_output_port_count(), ERR_INVALID_PARAMETER);
	ERR_FAIL_COND_V(!graph.nodes.has(p_to_node), ERR_INVALID_PARAMETER);
	ERR_FAIL_INDEX_V(p_to_port, graph.nodes[p_to_node].node->get_input_port_count(), ERR_INVALID_PARAMETER);

	VisualBrainTreeBehaviorTreeNode::PortType from_port_type = graph.nodes[p_from_node].node->get_output_port_type(p_from_port);
	VisualBrainTreeBehaviorTreeNode::PortType to_port_type = graph.nodes[p_to_node].node->get_input_port_type(p_to_port);

	if (MAX(0, from_port_type - 1) != (MAX(0, to_port_type - 1))) {
		ERR_EXPLAIN("Incompatible port types (scalar/index");
		ERR_FAIL_V(ERR_INVALID_PARAMETER)
		return ERR_INVALID_PARAMETER;
	}

	for (List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			ERR_FAIL_V(ERR_ALREADY_EXISTS);
		}
	}

	Connection c;
	c.from_node = p_from_node;
	c.from_port = p_from_port;
	c.to_node = p_to_node;
	c.to_port = p_to_port;
	graph.connections.push_back(c);

	// _queue_update();

	return OK;
}

void VisualBrainTreeBehaviorTreeNodeComponent::disconnect_nodes(int p_from_node, int p_from_port, int p_to_node, int p_to_port) {

	for (List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		if (E->get().from_node == p_from_node && E->get().from_port == p_from_port && E->get().to_node == p_to_node && E->get().to_port == p_to_port) {
			graph.connections.erase(E);
			// _queue_update();
			return;
		}
	}
}

Array VisualBrainTreeBehaviorTreeNodeComponent::_get_node_connections() const {

	Array ret;

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {
		Dictionary d;
		d["from_node"] = E->get().from_node;
		d["from_port"] = E->get().from_port;
		d["to_node"] = E->get().to_node;
		d["to_port"] = E->get().to_port;
		ret.push_back(d);
	}
	return ret;
}

void VisualBrainTreeBehaviorTreeNodeComponent::get_node_connections(List<Connection> *r_connections) const {

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {
		r_connections->push_back(E->get());
	}
}

void VisualBrainTreeBehaviorTreeNodeComponent::set_graph_offset(const Vector2 &p_offset) {

	graph_offset = p_offset;
}

Vector2 VisualBrainTreeBehaviorTreeNodeComponent::get_graph_offset() const {

	return graph_offset;
}

void VisualBrainTreeBehaviorTreeNodeComponent::evaluate(Ref<VisualBrainTreeBehaviorTree> noise) {

	// Make it faster to go around through noise nodes
	Connections input_connections;
	Connections output_connections;

	for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {

		ConnectionKey from_key;
		from_key.node = E->get().from_node;
		from_key.port = E->get().from_port;
		output_connections.insert(from_key, E);

		ConnectionKey to_key;
		to_key.node = E->get().to_node;
		to_key.port = E->get().to_port;
		input_connections.insert(to_key, E);
	}

	Set<int> processed;

	evaluate_node(NODE_ID_OUTPUT, noise, input_connections, output_connections, processed);

	const Ref<VisualBrainTreeBehaviorTreeNodeInput> &output = graph.nodes[NODE_ID_OUTPUT].node;
	ERR_FAIL_COND(output.is_null());

	output_value = output->get_output_port_value(0);
}

void VisualBrainTreeBehaviorTreeNodeComponent::evaluate_node(int node, Ref<VisualBrainTreeBehaviorTree> behavior_tree, Connections &input_connections, Connections &output_connections, Set<int> &processed) {

	Ref<VisualBrainTreeBehaviorTreeNode> &vanode = graph.nodes[node].node;

	// Evaluate inputs recursively first to retrieve needed indexes/values
	int input_count = vanode->get_input_port_count();
	for (int i = 0; i < input_count; i++) {

		ConnectionKey ck;
		ck.node = node;
		ck.port = i;

		if (input_connections.has(ck)) {
			int from_node = input_connections[ck]->get().from_node;

			if (processed.has(from_node)) {
				// Ensure not to re-evaluate nodes
				// Instruction indexes can be reused by other nodes as input
				continue;
			}
			evaluate_node(from_node, behavior_tree, input_connections, output_connections, processed);
		}
	}
	// Pass evaluated indexes/values to this node
	for (int i = 0; i < input_count; i++) {

		ConnectionKey ck;
		ck.node = node;
		ck.port = i;

		if (input_connections.has(ck)) {
			int from_node = input_connections[ck]->get().from_node;
			int from_port = input_connections[ck]->get().from_port;

			const Ref<VisualBrainTreeBehaviorTreeNode> &from_vanode = graph.nodes[from_node].node;

			VisualBrainTreeBehaviorTreeNode::PortType in_type = vanode->get_input_port_type(i);
			VisualBrainTreeBehaviorTreeNode::PortType out_type = from_vanode->get_output_port_type(from_port);

			vanode->set_input_port_value(i, from_vanode->get_output_port_value(0));
		}
	}
	// Ready to evaluate this node with inputs set
	vanode->evaluate(behavior_tree); // sets output value

	processed.insert(node);
}

// String VisualAnlNoiseNodeComponent::generate_preview_noise(int p_node, int p_port) const {

// 	Ref<VisualAnlNoiseNode> node = get_node(p_node);

// 	ERR_FAIL_COND_V(!node.is_valid(), String());
// 	ERR_FAIL_COND_V(p_port < 0 || p_port >= node->get_output_port_count(), String());

//     return String();
// }

bool VisualBrainTreeBehaviorTreeNodeComponent::_set(const StringName &p_name, const Variant &p_value) {

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String index = name.get_slicec('/', 1);
		if (index == "connections") {

			Vector<int> conns = p_value;
			if (conns.size() % 4 == 0) {
				for (int i = 0; i < conns.size(); i += 4) {
					connect_nodes(conns[i + 0], conns[i + 1], conns[i + 2], conns[i + 3]);
				}
			}
			return true;
		}

		int id = index.to_int();
		String what = name.get_slicec('/', 2);

		if (what == "node") {
			add_node(p_value, Vector2(), id);
			return true;
		} else if (what == "position") {
			set_node_position(id, p_value);
			return true;
		}
	}
	return false;
}

bool VisualBrainTreeBehaviorTreeNodeComponent::_get(const StringName &p_name, Variant &r_ret) const {

	String name = p_name;
	if (name.begins_with("nodes/")) {

		String index = name.get_slicec('/', 1);
		if (index == "connections") {

			Vector<int> conns;
			for (const List<Connection>::Element *E = graph.connections.front(); E; E = E->next()) {
				conns.push_back(E->get().from_node);
				conns.push_back(E->get().from_port);
				conns.push_back(E->get().to_node);
				conns.push_back(E->get().to_port);
			}

			r_ret = conns;
			return true;
		}

		int id = index.to_int();
		String what = name.get_slicec('/', 2);

		if (what == "node") {
			r_ret = get_node(id);
			return true;
		} else if (what == "position") {
			r_ret = get_node_position(id);
			return true;
		}
	}
	return false;
}

void VisualBrainTreeBehaviorTreeNodeComponent::_get_property_list(List<PropertyInfo> *p_list) const {

    for (Map<int, Node>::Element *E = graph.nodes.front(); E; E = E->next()) {

        String prop_name = "nodes/";
        prop_name += itos(E->key());

        if (E->key() != NODE_ID_OUTPUT) {

            p_list->push_back(PropertyInfo(Variant::OBJECT, prop_name + "/node", PROPERTY_HINT_RESOURCE_TYPE, "VisualAnlNoiseNode", PROPERTY_USAGE_NOEDITOR | PROPERTY_USAGE_DO_NOT_SHARE_ON_DUPLICATE));
        }
        p_list->push_back(PropertyInfo(Variant::VECTOR2, prop_name + "/position", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
    }
    p_list->push_back(PropertyInfo(Variant::POOL_INT_ARRAY, "nodes/connections", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR));
}

void VisualBrainTreeBehaviorTreeNodeComponent::_bind_methods() {


	ClassDB::bind_method(D_METHOD("set_component_name", "name"), &VisualBrainTreeBehaviorTreeNodeComponent::set_component_name);
	ClassDB::bind_method(D_METHOD("get_component_name"), &VisualBrainTreeBehaviorTreeNodeComponent::get_component_name);

	ClassDB::bind_method(D_METHOD("add_node", "node", "position", "id"), &VisualBrainTreeBehaviorTreeNodeComponent::add_node);
	ClassDB::bind_method(D_METHOD("set_node_position", "id", "position"), &VisualBrainTreeBehaviorTreeNodeComponent::set_node_position);

	ClassDB::bind_method(D_METHOD("get_node", "id"), &VisualBrainTreeBehaviorTreeNodeComponent::get_node);
	ClassDB::bind_method(D_METHOD("get_node_position", "id"), &VisualBrainTreeBehaviorTreeNodeComponent::get_node_position);

	ClassDB::bind_method(D_METHOD("get_node_list"), &VisualBrainTreeBehaviorTreeNodeComponent::get_node_list);
	ClassDB::bind_method(D_METHOD("get_valid_node_id"), &VisualBrainTreeBehaviorTreeNodeComponent::get_valid_node_id);

	ClassDB::bind_method(D_METHOD("remove_node", "id"), &VisualBrainTreeBehaviorTreeNodeComponent::remove_node);

	ClassDB::bind_method(D_METHOD("is_node_connection", "from_node", "from_port", "to_node", "to_port"), &VisualBrainTreeBehaviorTreeNodeComponent::is_node_connection);
	ClassDB::bind_method(D_METHOD("can_connect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualBrainTreeBehaviorTreeNodeComponent::is_node_connection);

	ClassDB::bind_method(D_METHOD("connect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualBrainTreeBehaviorTreeNodeComponent::connect_nodes);
	ClassDB::bind_method(D_METHOD("disconnect_nodes", "from_node", "from_port", "to_node", "to_port"), &VisualBrainTreeBehaviorTreeNodeComponent::disconnect_nodes);

	ClassDB::bind_method(D_METHOD("get_node_connections"), &VisualBrainTreeBehaviorTreeNodeComponent::_get_node_connections);

	ClassDB::bind_method(D_METHOD("set_graph_offset", "offset"), &VisualBrainTreeBehaviorTreeNodeComponent::set_graph_offset);
	ClassDB::bind_method(D_METHOD("get_graph_offset"), &VisualBrainTreeBehaviorTreeNodeComponent::get_graph_offset);

	ClassDB::bind_method(D_METHOD("evaluate", "noise"), &VisualBrainTreeBehaviorTreeNodeComponent::evaluate);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "name", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_component_name", "get_component_name");
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "graph_offset", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_graph_offset", "get_graph_offset");

	BIND_CONSTANT(NODE_ID_INVALID);
	BIND_CONSTANT(NODE_ID_OUTPUT);
}


VisualBrainTreeBehaviorTree::VisualBrainTreeBehaviorTree() :
		BrainTreeBehaviorTree() {
	dirty = true;
}

void VisualBrainTreeBehaviorTree::generate() {

	dirty = true;
	_update_noise();
}

void VisualBrainTreeBehaviorTree::_update_noise() {

	if (component.is_null()) {
		return;
	}

	if (!dirty)
		return;

	dirty = false;

	// reset();

	component->evaluate(Ref<VisualBrainTreeBehaviorTree>(this));
}

void VisualBrainTreeBehaviorTree::_queue_update() {

	if (dirty) {
		return;
	}

	dirty = true;

	call_deferred("_update_noise");
}

void VisualBrainTreeBehaviorTree::_bind_methods() {

	ClassDB::bind_method(D_METHOD("generate"), &VisualBrainTreeBehaviorTree::generate);

	ClassDB::bind_method(D_METHOD("set_component", "component"), &VisualBrainTreeBehaviorTree::set_component);
	ClassDB::bind_method(D_METHOD("get_component"), &VisualBrainTreeBehaviorTree::get_component);

	// ClassDB::bind_method(D_METHOD("_queue_update"), &VisualAnlNoiseNodeComponent::_queue_update);
	// ClassDB::bind_method(D_METHOD("_update_noise"), &VisualAnlNoiseNodeComponent::_update_noise);

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "component", PROPERTY_HINT_RESOURCE_TYPE, "VisualBrainTreeBehaviorTreeNodeComponent"), "set_component", "get_component");

	ADD_SIGNAL(MethodInfo("component_changed"));
}

void VisualBrainTreeBehaviorTree::set_component(const Ref<VisualBrainTreeBehaviorTreeNodeComponent> &p_component) {

	if(p_component.is_valid()) {
		component = p_component;
		emit_signal("component_changed");
	}
}


Ref<VisualBrainTreeBehaviorTreeNodeComponent> VisualBrainTreeBehaviorTree::get_component() const {

	return component;
}

//////////////////
// Component node
//////////////////

VisualBrainTreeBehaviorTreeNodeComponent::VisualBrainTreeBehaviorTreeNodeComponent() {

    Ref<VisualBrainTreeBehaviorTreeNodeInput> output;
    output.instance();
    graph.nodes[NODE_ID_OUTPUT].node = output;
    graph.nodes[NODE_ID_OUTPUT].position = Vector2(400, 150);

	name = "component";
}

int VisualBrainTreeBehaviorTreeNodeComponent::get_input_port_count() const {

	return 0;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeComponent::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeComponent::get_input_port_name(int p_port) const {

	return "";
}

int VisualBrainTreeBehaviorTreeNodeComponent::get_output_port_count() const {

	return 1;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeComponent::get_output_port_type(int p_port) const {

	// Should always return index of the noise function evaluated
	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeComponent::get_output_port_name(int p_port) const {

	return "";
}

String VisualBrainTreeBehaviorTreeNodeComponent::get_caption() const {

	return TTR("Component");
}

//////////////////
// Input node
//////////////////

int VisualBrainTreeBehaviorTreeNodeInput::get_input_port_count() const {

	return 0;
}

VisualBrainTreeBehaviorTreeNodeInput::PortType VisualBrainTreeBehaviorTreeNodeInput::get_input_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeInput::get_input_port_name(int p_port) const {

	return String();
}

Variant VisualBrainTreeBehaviorTreeNodeInput::get_input_port_default_value(int p_port) const {

	return Variant();
}

int VisualBrainTreeBehaviorTreeNodeInput::get_output_port_count() const {

	return 1;
}

VisualBrainTreeBehaviorTreeNodeInput::PortType VisualBrainTreeBehaviorTreeNodeInput::get_output_port_type(int p_port) const {

	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeInput::get_output_port_name(int p_port) const {

	return TTR("Index");
}

bool VisualBrainTreeBehaviorTreeNodeInput::is_port_separator(int p_index) const {

	return false;
}

String VisualBrainTreeBehaviorTreeNodeInput::get_caption() const {

	return TTR("Output");
}

void VisualBrainTreeBehaviorTreeNodeInput::set_input_port_value(int p_port, const Variant &p_value) {

	output_value = p_value;
}

Variant VisualBrainTreeBehaviorTreeNodeInput::get_input_port_value(int p_port) const {

	return output_value;
}

void VisualBrainTreeBehaviorTreeNodeInput::set_output_port_value(int p_port, const Variant &p_value) {

	output_value = p_value;
}

Variant VisualBrainTreeBehaviorTreeNodeInput::get_output_port_value(int p_port) const {

	return output_value;
}

VisualBrainTreeBehaviorTreeNodeInput::VisualBrainTreeBehaviorTreeNodeInput() {

}
