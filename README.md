# Behavior Trees for Godot Engine

This module uses: https://github.com/arvidsson/BrainTree

Work in Progress. Not ready for production.

## Install

Copy this git repository into the Godot Engine modules folder.

## How To Use

Add a behavior tree as a child node to the Node that you want to use it. 

When you select the behavior tree node, you will get a bottom panel button named behavior tree.

Pushing this button will bring up the editor.

An empty behavior tree will create a sequence node as a starting point. Move this at a suitable position. Drag the right output to establish a connection, releasing the link at a space will bring up the popup panel with all the selections. Add a selection, and you will have a new node and a connection automatically. All the nodes are internal to GodotBrainTree, and only the last one named Task is going to use the parent node.

When you put a Task node, fill the box with the name of the function of the parent node that you want to use. What the function returns determines the status of the Task node that called it.

The return values must be one of these constants:

* Invalid
* Success
* Failure
* Running

## Running the GodotBrainTree

When you are running the GodotBrainTree in realtime, you can select the Behavior Tree in the remote inspector and click the Braintree/inspect to set it to true.

Selecting the Behavior Tree will bring up the in the game window a GraphEdit node with the Tree (identical to the one you were editing)

The color of the connection is changed according to the status of the nodes.

* White is Invalid
* Blue is Success
* Red is Failure
* Green is Running
