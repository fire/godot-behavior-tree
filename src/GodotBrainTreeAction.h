#ifndef GODOTBRAINTREEACTION_H
#define GODOTBRAINTREEACTION_H

#include "../thirdparty/braintree/BrainTree.h"
#include "../brain_tree_behavior_tree.h"

class GodotBrainTreeAction : public BrainTree::Node {
public:
	GodotBrainTreeAction() {}

	BrainTreeBehaviorTree *owner = nullptr;
	String func_name = "";

	//Status update() override {
	//	int s = owner->owner->get_parent()->call(func_name);
	//	return static_cast<Status>(s);
	//	/*
 //       switch(s){
 //           case 0:
 //               return Node::Status::Failure;
 //           case 1:
 //               return Node::Status::Success;
 //           case 2:
 //               return Node::Status::Running;
 //           default:
 //               return Node::Status::Invalid;
 //       }
 //       */
	//}
};

#endif
