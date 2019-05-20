#include "brain_tree_behavior_tree.h"

#include "scene/main/canvas_layer.h"
#include "core/engine.h"
#include "src/GodotBrainTreeAction.h"
#include "scene/gui/graph_edit.h"

void BrainTreeBehaviorTree::_bind_methods() {
	ClassDB::bind_method("is_brain_tree", &BrainTreeBehaviorTree::is_brain_tree);
	ClassDB::bind_method("set_dict", &BrainTreeBehaviorTree::set_dict);
	ClassDB::bind_method("get_dict", &BrainTreeBehaviorTree::get_dict);
	ClassDB::bind_method("set_inspect", &BrainTreeBehaviorTree::set_inspect);
	ClassDB::bind_method("get_inspect", &BrainTreeBehaviorTree::get_inspect);
	ClassDB::bind_method("setup", &BrainTreeBehaviorTree::setup);
	ClassDB::bind_method("update", &BrainTreeBehaviorTree::update);
	ClassDB::bind_method("get_status", &BrainTreeBehaviorTree::get_status);

	ADD_PROPERTY(PropertyInfo(Variant::DICTIONARY, "dict", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_dict", "get_dict");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "inspect", PROPERTY_HINT_NONE, "", PROPERTY_USAGE_NOEDITOR), "set_inspect", "get_inspect");
}

void BrainTreeBehaviorTree::is_brain_tree() {
}

void BrainTreeBehaviorTree::set_dict(Dictionary in_dict) {
	dict = in_dict;
}

Dictionary BrainTreeBehaviorTree::get_dict() const {
	return dict;
}

void BrainTreeBehaviorTree::setup() {

	if (!dict.empty()) {
		auto node = getFromDict(dict);
		tree.setRoot(node);
	}
}

void BrainTreeBehaviorTree::update() {
	tree.update();
}

BrainTree::Node::Ptr BrainTreeBehaviorTree::getFromDict(Dictionary in_dict) {
	int type = in_dict["type"];

	switch (type) {
		case 0: {
			auto node = new BrainTree::Selector();
			Array nodes = in_dict["children"];
			for (int i = 0; i < nodes.size(); ++i) {
				node->addChild(getFromDict(nodes[i]));
			}

			return BrainTree::Node::Ptr(node);
		} break;
		case 1: {
			auto node = new BrainTree::Sequence();
			Array nodes = in_dict["children"];
			for (int i = 0; i < nodes.size(); ++i) {
				node->addChild(getFromDict(nodes[i]));
			}

			return BrainTree::Node::Ptr(node);
		} break;
		case 2: {
			auto node = new BrainTree::StatefulSelector();
			Array nodes = in_dict["children"];
			for (int i = 0; i < nodes.size(); ++i) {
				node->addChild(getFromDict(nodes[i]));
			}

			return BrainTree::Node::Ptr(node);
		} break;
		case 3: {
			auto node = new BrainTree::MemSequence();
			Array nodes = in_dict["children"];
			for (int i = 0; i < nodes.size(); ++i) {
				node->addChild(getFromDict(nodes[i]));
			}

			return BrainTree::Node::Ptr(node);
		} break;
		case 4: {
			auto node = new BrainTree::ParallelSequence();
			Array nodes = in_dict["children"];
			for (int i = 0; i < nodes.size(); ++i) {
				node->addChild(getFromDict(nodes[i]));
			}

			return BrainTree::Node::Ptr(node);
		} break;
		case 5: {
			auto node = new BrainTree::Succeeder();
			Array nodes = in_dict["children"];
			node->setChild(getFromDict(nodes[0]));

			return BrainTree::Node::Ptr(node);
		} break;
		case 6: {
			auto node = new BrainTree::Failer();
			Array nodes = in_dict["children"];
			node->setChild(getFromDict(nodes[0]));

			return BrainTree::Node::Ptr(node);
		} break;
		case 7: {
			auto node = new BrainTree::Inverter();
			Array nodes = in_dict["children"];
			node->setChild(getFromDict(nodes[0]));

			return BrainTree::Node::Ptr(node);
		} break;
		case 8: {
			auto node = new BrainTree::Repeater();
			Array nodes = in_dict["children"];
			node->setChild(getFromDict(nodes[0]));

			return BrainTree::Node::Ptr(node);
		} break;
		case 9: {
			auto node = new BrainTree::UntilSuccess();
			Array nodes = in_dict["children"];
			node->setChild(getFromDict(nodes[0]));

			return BrainTree::Node::Ptr(node);
		} break;
		case 10: {
			auto node = new BrainTree::UntilFailure();
			Array nodes = in_dict["children"];
			node->setChild(getFromDict(nodes[0]));

			return BrainTree::Node::Ptr(node);
		} break;
		case 11: {
			//auto node = new GodotBrainTreeAction();
			//node->owner = this;
			//node->func_name = in_dict["function_name"];

			//return BrainTree::Node::Ptr(node);
			return NULL;
		} break;
	}
	return NULL;
}

Vector<int> BrainTreeBehaviorTree::get_status() const {
	Vector<int> z = tree.getStatus();
	return z;
}

bool BrainTreeBehaviorTree::get_inspect() const {
	if (Engine::get_singleton()->is_editor_hint()) return false;
	return inspect;
}

void BrainTreeBehaviorTree::set_inspect(bool value) {
	if (Engine::get_singleton()->is_editor_hint()) return;
	inspect = value;
	if (inspect) {
		//auto canvas = new CanvasLayer();
		//canvas->set_name("BrainTreeInspector");
		//auto script = ResourceLoader::load("res://addons/kakoeimon.braintree/Inspector.gd");
		//auto graph = new GraphEdit();
		//graph->set_script(script.ptr());
		//canvas->add_child(graph);
		//owner->add_child(canvas);
	} else {
		//if (owner->has_node("BrainTreeInspector")) {
		//	owner->get_node("BrainTreeInspector")->queue_free();
		//}
	}
}
