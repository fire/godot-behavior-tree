#ifndef VISUAL_ANL_NOISE_NODES_H
#define VISUAL_ANL_NOISE_NODES_H

#include "visual_brain_tree_behavior_tree.h"

class VisualBrainTreeBehaviorTreeNodeComposite : public VisualBrainTreeBehaviorTreeNode {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeComposite, VisualBrainTreeBehaviorTreeNode)
	StringName blackboard_based_condition;
	StringName service;

public:
	virtual String get_caption() const;
	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;
	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;
	virtual void set_blackboard_based_condition(const String p_blackboard_based_condition);
	virtual String get_blackboard_based_condition() const;
	virtual Vector<StringName> get_editable_properties() const;
	virtual void set_service(const String p_service);
	virtual StringName get_service() const;
	VisualBrainTreeBehaviorTreeNodeComposite();

protected:
	static void _bind_methods();
};

class VisualBrainTreeBehaviorTreeNodeSelector : public VisualBrainTreeBehaviorTreeNodeComposite {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeSelector, VisualBrainTreeBehaviorTreeNodeComposite)
public:
	virtual String get_caption() const;

	VisualBrainTreeBehaviorTreeNodeSelector();
};

class VisualBrainTreeBehaviorTreeNodeSequence : public VisualBrainTreeBehaviorTreeNodeComposite {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeSequence, VisualBrainTreeBehaviorTreeNodeComposite)
public:
	virtual String get_caption() const;

	VisualBrainTreeBehaviorTreeNodeSequence();
};

class VisualBrainTreeBehaviorTreeNodeTask : public VisualBrainTreeBehaviorTreeNode {
	GDCLASS(VisualBrainTreeBehaviorTreeNodeTask, VisualBrainTreeBehaviorTreeNode)

	StringName method;

public:
	virtual String get_caption() const;

	virtual void set_input_port_value(int p_port, const Variant &p_value);
	virtual Variant get_input_port_value(int p_port) const;
	;
	virtual int get_input_port_count() const;
	virtual PortType get_input_port_type(int p_port) const;
	virtual String get_input_port_name(int p_port) const;

	virtual int get_output_port_count() const;
	virtual PortType get_output_port_type(int p_port) const;
	virtual String get_output_port_name(int p_port) const;

	void set_action_method(const String p_method);

	String get_action_method() const;

	virtual Vector<StringName> get_editable_properties() const;

	VisualBrainTreeBehaviorTreeNodeTask();

protected:
	static void _bind_methods();
};

#endif
