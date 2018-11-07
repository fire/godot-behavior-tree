#include "visual_brain_tree_behavior_tree_nodes.h"

String VisualBrainTreeBehaviorTreeNodeSelector::get_caption() const {
	return "Selector";
}

void VisualBrainTreeBehaviorTreeNodeSelector::set_input_port_value(int p_port, const Variant &p_value) {
}

Variant VisualBrainTreeBehaviorTreeNodeSelector::get_input_port_value(int p_port) const {
	return Variant();
}

int VisualBrainTreeBehaviorTreeNodeSelector::get_input_port_count() const {
	return 1;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeSelector::get_input_port_type(int p_port) const {
	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeSelector::get_input_port_name(int p_port) const {
	return "";
}

int VisualBrainTreeBehaviorTreeNodeSelector::get_output_port_count() const {
	return 1;
}

VisualBrainTreeBehaviorTreeNode::PortType VisualBrainTreeBehaviorTreeNodeSelector::get_output_port_type(int p_port) const {
	return PORT_TYPE_INDEX;
}

String VisualBrainTreeBehaviorTreeNodeSelector::get_output_port_name(int p_port) const {
	return "";
}

Vector<StringName> VisualBrainTreeBehaviorTreeNodeSelector::get_editable_properties() const {
	return Vector<StringName>();
}

VisualBrainTreeBehaviorTreeNodeSelector::VisualBrainTreeBehaviorTreeNodeSelector() {
}

void VisualBrainTreeBehaviorTreeNodeSelector::_bind_methods() {
}
