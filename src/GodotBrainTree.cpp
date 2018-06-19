#include "GodotBrainTreeAction.h"

void GodotBrainTree::_register_methods()
{
    godot::register_property((char *)"BrainTree/dict", &GodotBrainTree::dict, godot::Dictionary());
   
    godot::register_method("is_brain_tree", &GodotBrainTree::is_brain_tree);

    godot::register_method("set_dict", &GodotBrainTree::set_dict);

    godot::register_method("get_dict", &GodotBrainTree::get_dict);

    godot::register_method("setup", &GodotBrainTree::setup);

    godot::register_method("update", &GodotBrainTree::update);

    
}

void GodotBrainTree::is_brain_tree()
{
    
}

void GodotBrainTree::set_dict(godot::Dictionary in_dict)
{
    dict = in_dict;
}

godot::Dictionary GodotBrainTree::get_dict() const 
{
    return dict;
}

void GodotBrainTree::setup()
{
    
    if(!dict.empty()){
        auto node = getFromDict(dict);
        tree.setRoot(node);
    }

    
    
}



void GodotBrainTree::update()
{
    tree.update();
}

BrainTree::Node::Ptr GodotBrainTree::getFromDict(godot::Dictionary in_dict)
{
    int type = in_dict["type"];

    switch(type){
        case 0:
            {
                auto node = new BrainTree::Selector();
                godot::Array nodes = in_dict["children"];
                for(int i = 0; i < nodes.size(); ++i){
                    node->addChild(getFromDict(nodes[i]));
                }

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 1:
            {
                auto node = new BrainTree::Sequence();
                godot::Array nodes = in_dict["children"];
                for(int i = 0; i < nodes.size(); ++i){
                    node->addChild(getFromDict(nodes[i]));
                }

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 2:
            {
                auto node = new BrainTree::StatefulSelector();
                godot::Array nodes = in_dict["children"];
                for(int i = 0; i < nodes.size(); ++i){
                    node->addChild(getFromDict(nodes[i]));
                }

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 3:
            {
                auto node = new BrainTree::MemSequence();
                godot::Array nodes = in_dict["children"];
                for(int i = 0; i < nodes.size(); ++i){
                    node->addChild(getFromDict(nodes[i]));
                }

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 4:
            {
                auto node = new BrainTree::ParallelSequence();
                godot::Array nodes = in_dict["children"];
                for(int i = 0; i < nodes.size(); ++i){
                    node->addChild(getFromDict(nodes[i]));
                }

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 5:
            {
                auto node = new BrainTree::Succeeder();
                godot::Array nodes = in_dict["children"];
                node->setChild(getFromDict(nodes[0]));

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 6:
            {
                auto node = new BrainTree::Failer();
                godot::Array nodes = in_dict["children"];
                node->setChild(getFromDict(nodes[0]));

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 7:
            {
                auto node = new BrainTree::Inverter();
                godot::Array nodes = in_dict["children"];
                node->setChild(getFromDict(nodes[0]));

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 8:
            {
                auto node = new BrainTree::Repeater();
                godot::Array nodes = in_dict["children"];
                node->setChild(getFromDict(nodes[0]));

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 9:
            {
                auto node = new BrainTree::UntilSuccess();
                godot::Array nodes = in_dict["children"];
                node->setChild(getFromDict(nodes[0]));

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 10:
            {
                auto node = new BrainTree::UntilFailure();
                godot::Array nodes = in_dict["children"];
                node->setChild(getFromDict(nodes[0]));

                return BrainTree::Node::Ptr(node);
            }
            break;
        case 11:
            {
                auto node = new GodotBrainTreeAction();
                node->owner = this;
                node->func_name = in_dict["function_name"];

                return BrainTree::Node::Ptr(node);
            }
            break;
    }
}
