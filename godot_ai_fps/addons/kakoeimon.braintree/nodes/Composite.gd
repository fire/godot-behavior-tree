tool
extends GraphNode


class CustomYSorter:
	static func sortY(a, b):
		if a.y < b.y:
			return true
		return false

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
	var childs_to_add = []
	for con in list:
		if con["from"] == name:
			childs_to_add.append(graph.get_node(con["to"]).get_dict(graph))
			#dict.children.append(graph.get_node(con["to"]).get_dict(graph))
	childs_to_add.sort_custom(CustomYSorter, "sortY")
	for c in childs_to_add:
		dict.children.append(c)
	
	return dict