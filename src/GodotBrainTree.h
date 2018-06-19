#ifndef GODOTBRAINTREE_H
#define GODOTBRAINTREE_H

#include "Godot.hpp"
#include "Node.hpp"
//#include "Dictionary.hpp"



class GodotBrainTree : public godot::GodotScript<godot::Node> {
	GODOT_CLASS(GodotBrainTree)
public:
    static void _register_methods();
    float version = 1.0f;
    godot::Dictionary dict;
    BrainTree::BehaviorTree tree = BrainTree::BehaviorTree();

    void set_dict(godot::Dictionary);
    godot::Dictionary get_dict() const;
    void is_brain_tree();

    void setup();
    void update();

    void set_child(BrainTree::Sequence *, godot::Dictionary);

    BrainTree::Node::Ptr getFromDict(godot::Dictionary);

};

#endif