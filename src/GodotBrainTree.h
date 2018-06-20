#ifndef GODOTBRAINTREE_H
#define GODOTBRAINTREE_H

#include "Godot.hpp"
#include "Node.hpp"
#include "Resource.hpp"
#include "ResourceLoader.hpp"



class GodotBrainTree : public godot::GodotScript<godot::Node> {
	GODOT_CLASS(GodotBrainTree)
public:
    static void _register_methods();
    float version = 1.0f;
    godot::Dictionary dict;
    bool inspect = false;
    bool get_inspect() const;
    void set_inspect(bool);
    BrainTree::BehaviorTree tree = BrainTree::BehaviorTree();

    void set_dict(godot::Dictionary);
    godot::Dictionary get_dict() const;
    void is_brain_tree();

    void setup();
    void update();

    godot::Array get_status() const;

    BrainTree::Node::Ptr getFromDict(godot::Dictionary);

};

#endif