#include "GodotBrainTreeAction.h"
#include "CanvasLayer.hpp"
#include "GraphEdit.hpp"
#include "Engine.hpp"

void GodotBrainTree::_register_methods()
{
    godot::register_property((char *)"BrainTree/dict", &GodotBrainTree::dict, godot::Dictionary());

    godot::register_property((char *)"BrainTree/inspect", &GodotBrainTree::set_inspect, &GodotBrainTree::get_inspect, false);
   
    godot::register_method("is_brain_tree", &GodotBrainTree::is_brain_tree);

    godot::register_method("set_dict", &GodotBrainTree::set_dict);

    godot::register_method("get_dict", &GodotBrainTree::get_dict);

    godot::register_method("setup", &GodotBrainTree::setup);

    godot::register_method("update", &GodotBrainTree::update);

    godot::register_method("get_status", &GodotBrainTree::get_status);
    
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

godot::Array GodotBrainTree::get_status() const 
{
    godot::Array z = tree.getStatus();
    return z;
}

bool GodotBrainTree::get_inspect() const
{
    if(godot::Engine::is_editor_hint()) return false;
    return inspect;
}

void GodotBrainTree::set_inspect(bool value)
{
    if(godot::Engine::is_editor_hint()) return;
    inspect = value;
    if(inspect){
        auto canvas = new godot::CanvasLayer();
        canvas->set_name("BrainTreeInspector");
        auto script = godot::ResourceLoader::load("res://addons/kakoeimon.braintree/Inspector.gd");
        auto graph = new godot::GraphEdit();
        graph->set_script(script.ptr());
        canvas->add_child(graph);
        owner->add_child(canvas);
    } else {
        if(owner->has_node("BrainTreeInspector")){
            owner->get_node("BrainTreeInspector")->queue_free();
        }
    }
}
