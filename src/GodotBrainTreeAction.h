#ifndef GODOTBRAINTREEACTION_H
#define GODOTBRAINTREEACTION_H

#include "BrainTree.h"
#include "GodotBrainTree.h"



class GodotBrainTreeAction : public BrainTree::Node 
{
public:
    GodotBrainTreeAction(){}

    GodotBrainTree *owner = nullptr;
    godot::String func_name = "";

    Status update() override
    {
        int s = owner->owner->get_parent()->call(func_name);
        switch(s){
            case 0:
                return Node::Status::Failure;
            case 1:
                return Node::Status::Success;
            case 2:
                return Node::Status::Running;
            default:
                return Node::Status::Invalid;
        }
    }
    
};

#endif