# GodotBrainTree
Plugin Behavior Trees for Godot 3+

This plugin uses : https://github.com/arvidsson/BrainTree

Work in Progress. Not ready for production.

# Install
Copy the addons directory to your project and enable the plugin though the editor.

# How To Use
Add a GodotBrainTree (from now on GBT) as a child node to the Node that you want to use it. (see Note_2)
When you select the GBT node you will get a bottom panel button named BrainTree.
Pushing this button will bring up the editor.
An empty GBT will create a sequence node as a starting point.
Move this at a suitable position.
Drag the right output to create a connection, releasing the output at an empty space will bring up the a popup panel with all the selections.
Choose a selection and you will have automatically a new node and a connection.
All the selections are native to GBT, only the last one named Action is going to use the parent node.
When you put an Action node, fill the EditLine with the name of the function of the parent node that you want to use.
What the function returns determines the status of the Action node that it called the function.
The return values must be one of those:

# Values Returned by the function called by Action node
0 is Invalid
1 is Success
2 is Failure
3 is Running

# Running the GBT
When you are running the GBT in realtime, you can select the GBT in the remote inspector and click the BrainTree/inspect to set it to true.
This will bring up the in the game window a GraphEdit node with the Tree (identical to the one you were editing)
The color of the connections are changed according to the status of the nodes.

White is Invalid
Blue is Success
Red is Failure
Green is Running

# Note_1:
IMPORTANT
The first node of the GBT must be left most node. If for some reason you make it to be to the right of another node the GBT will not run correctly.
The order of the child nodes is determined by the height of the objects in the GraphEdit. This means that the higher nodes will run first.

# Note_2 : 
Cause there is a bug in Godot 3.0.3 we have to add a BrainTree by instance scene and not by add node.
