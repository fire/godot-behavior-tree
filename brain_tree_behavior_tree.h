#ifndef BRAIN_TREE_BEHAVIOUR_TREE_H
#define BRAIN_TREE_BEHAVIOUR_TREE_H

#include "scene/main/node.h"
#include "src/BrainTree.h"

class BrainTreeBehaviorTree : public Resource {
	GDCLASS(BrainTreeBehaviorTree, Resource);

protected:
	static void _bind_methods();

public:
	float version = 1.0f;
	Dictionary dict;
	bool inspect = false;
	bool get_inspect() const;
	void set_inspect(bool);
	BrainTree::BehaviorTree tree = BrainTree::BehaviorTree();

	void set_dict(Dictionary);
	Dictionary get_dict() const;
	void is_brain_tree();

	void setup();
	void update();

	Vector<int> get_status() const;

	BrainTree::Node::Ptr getFromDict(Dictionary);
};

#endif

