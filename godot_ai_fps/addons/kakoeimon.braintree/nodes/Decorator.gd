tool
extends GraphNode

# class member variables go here, for example:
# var a = 2
# var b = "textvar"

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	pass

#func _process(delta):
#	# Called every frame. Delta is time since last frame.
#	# Update game logic here.
#	pass

func get_dict(graph):
	var dict = {"type":0, "x": offset.x, "y": offset.y, "children": []}
	var list = graph.get_connection_list()
	#print(list)
	for con in list:
		if con["from"] == name:
			dict.children.append(graph.get_node(con["to"]).get_dict(graph))
	return dict