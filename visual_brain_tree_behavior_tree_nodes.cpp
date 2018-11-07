#include "visual_brain_tree_behavior_tree_nodes.h"

String VisualBrainTreeBehaviorTreeNodeComposite::get_caption() const {
	return "Selector";
}

void VisualBrainTreeBehaviorTreeNodeComposite::set_input_port_value(int p_port, const Variant &p_value) {
}

Variant VisualBrainTreeBehaviorTreeNodeComposite::get_input_port_value(int p_port) const {
	return Variant();
}

int VisualBrainTreeBehaviorTreeNodeComposite::get_input_port_count() const {
	return 1;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeComposite::get_input_port_type(int p_port) const {
	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeComposite::get_input_port_name(int p_port) const {
	return "";
}

int VisualBrainTreeBehaviorTreeNodeComposite::get_output_port_count() const {
	return 1;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeComposite::get_output_port_type(int p_port) const {
	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeComposite::get_output_port_name(int p_port) const {
	return "";
}

void VisualBrainTreeBehaviorTreeNodeComposite::set_blackboard_based_condition(const String p_blackboard_based_condition) {
	blackboard_based_condition = p_blackboard_based_condition;
}

String VisualBrainTreeBehaviorTreeNodeComposite::get_blackboard_based_condition() const {
	return blackboard_based_condition;
}

Vector<StringName> VisualBrainTreeBehaviorTreeNodeComposite::get_editable_properties() const {
	Vector<StringName> props;
	props.push_back("blackboard_based_condition");
	return props;
}

VisualBrainTreeBehaviorTreeNodeComposite::VisualBrainTreeBehaviorTreeNodeComposite() {
}

void VisualBrainTreeBehaviorTreeNodeComposite::_bind_methods() {

	ClassDB::bind_method(D_METHOD("set_blackboard_based_condition", "blackboard_based_condition"), &VisualBrainTreeBehaviorTreeNodeComposite::set_blackboard_based_condition);
	ClassDB::bind_method(D_METHOD("get_blackboard_based_condition"), &VisualBrainTreeBehaviorTreeNodeComposite::get_blackboard_based_condition);

	ADD_PROPERTY(PropertyInfo(Variant::STRING, "blackboard_based_condition"), "set_blackboard_based_condition", "get_blackboard_based_condition");
}

String VisualBrainTreeBehaviorTreeNodeSequence::get_caption() const {
	return "Sequence";
}

VisualBrainTreeBehaviorTreeNodeSequence::VisualBrainTreeBehaviorTreeNodeSequence() {
}

String VisualBrainTreeBehaviorTreeNodeSelector::get_caption() const {
	return "Selector";
}

VisualBrainTreeBehaviorTreeNodeSelector::VisualBrainTreeBehaviorTreeNodeSelector() {
}

String VisualBrainTreeBehaviorTreeNodeTask::get_caption() const {
	return "Task";
}

void VisualBrainTreeBehaviorTreeNodeTask::set_input_port_value(int p_port, const Variant &p_value) {
}

Variant VisualBrainTreeBehaviorTreeNodeTask::get_input_port_value(int p_port) const {
	return Variant();
}

int VisualBrainTreeBehaviorTreeNodeTask::get_input_port_count() const {
	return 1;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeTask::get_input_port_type(int p_port) const {
	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeTask::get_input_port_name(int p_port) const {
	return String();
}

int VisualBrainTreeBehaviorTreeNodeTask::get_output_port_count() const {
	return 0;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeTask::get_output_port_type(int p_port) const {
	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeTask::get_output_port_name(int p_port) const {
	return String();
}

void VisualBrainTreeBehaviorTreeNodeTask::set_action_method(const String p_method) {
	method = p_method;
	emit_changed();
}

String VisualBrainTreeBehaviorTreeNodeTask::get_action_method() const {
	return method;
}

Vector<StringName> VisualBrainTreeBehaviorTreeNodeTask::get_editable_properties() const {
	Vector<StringName> props;
	props.push_back("action_method");
	return props;
}

VisualBrainTreeBehaviorTreeNodeTask::VisualBrainTreeBehaviorTreeNodeTask() {
}

void VisualBrainTreeBehaviorTreeNodeTask::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_action_method", "method"), &VisualBrainTreeBehaviorTreeNodeTask::set_action_method);
	ClassDB::bind_method(D_METHOD("get_action_method"), &VisualBrainTreeBehaviorTreeNodeTask::get_action_method);
	// @TODO DROP LIST
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "action_method"), "set_action_method", "get_action_method");
}
