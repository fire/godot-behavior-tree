extends GraphEdit

class CustomYSorter:
	static func sortY(a, b):
		if a.y < b.y:
			return true
		return false

var brain
var first = null
var hierarchy = []

var action_pck = preload("nodes/Action.tscn")
var selector_pck = preload("nodes/Selector.tscn")
var sequencer_pck = preload("nodes/Sequence.tscn")
var statefulSelector_pck = preload("nodes/StatefulSelector.tscn")
var memSequence_pck = preload("nodes/MemSequence.tscn")
var parallelSequence_pck = preload("nodes/ParallelSequence.tscn")
var succeeder_pck = preload("nodes/Succeeder.tscn")
var failer_pck = preload("nodes/Failer.tscn")
var inverter_pck = preload("nodes/Inverter.tscn")
var repeater_pck = preload("nodes/Repeater.tscn")
var untilSuccess_pck = preload("nodes/UntilSuccess.tscn")
var untilFailure_pck = preload("nodes/UntilFailure.tscn")

func _ready():
	# Called when the node is added to the scene for the first time.
	# Initialization here
	brain = get_parent()
	rect_min_size = Vector2(800,600)
	build_from_dict()
	get_first()
	create_hierarchy()
	pass

func _process(delta):
	var status = brain.get_status()
	set_colors(status[0], hierarchy[0])
	update()

func update():
	.update()
	for c in get_children():
		c.update()

func set_colors(_s, _h):
	var c = _s[0]
	var h = _h[0]
	#set_slot( int idx, bool enable_left, int type_left, Color color_left, bool enable_right, int type_right, Color color_right, Texture custom_left=null, Texture custom_right=null )
	var color = Color(1,1,1)
	if c == 1:
		color = Color(0,0,1)
	elif c == 2:
		color = Color(1,0,0)
	elif c == 3:
		color = Color(0,1,0)
	
	h.set_slot(0, true, 0, color, true, 0, color)
	
	if _s.size() > 1:
		for i in range(1, _s.size()):
			set_colors(_s[i], _h[i])
		pass
	pass

func get_first():
	for c in get_children():
		if c is GraphNode:
			if first:
				if c.offset.x < first.offset.x:
					first = c
			else:
				first = c

func create_hierarchy():
	var arr = [add_hierarchy(first)]
	hierarchy = arr

func add_hierarchy(node):
	var arr = []
	arr.append(node)
	var list = get_connection_list()
	for c in list:
		if c.from == node.name:
			arr.append(add_hierarchy(get_node(c.to)))
	return arr

func build_from_dict():
	var dict = brain.get_dict()

	for child in get_children():
		if child is GraphNode:
			child.free()
	
	if not dict.empty():
		build_node(dict)
	
	pass
	
func build_node(in_dict):
	var type = int(in_dict["type"])
	var child
	if type == 0:
		child = selector_pck.instance()
		add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			connect_node(child.name, 0, con.name, 0)
	elif type == 1:
		child = sequencer_pck.instance()
		add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			connect_node(child.name, 0, con.name, 0)
	elif type == 2:
		child = statefulSelector_pck.instance()
		add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			connect_node(child.name, 0, con.name, 0)
	elif type == 3:
		child = memSequence_pck.instance()
		add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			connect_node(child.name, 0, con.name, 0)
	elif type == 4:
		child = parallelSequence_pck.instance()
		add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			connect_node(child.name, 0, con.name, 0)
	elif type == 5:
		child = succeeder_pck.instance()
		add_child(child)
		var con = build_node(in_dict["children"][0])
		connect_node(child.name, 0, con.name, 0)
	elif type == 6:
		child = failer_pck.instance()
		add_child(child)
		var con = build_node(in_dict["children"][0])
		connect_node(child.name, 0, con.name, 0)
	elif type == 7:
		child = inverter_pck.instance()
		add_child(child)
		var con = build_node(in_dict["children"][0])
		connect_node(child.name, 0, con.name, 0)
	elif type == 8:
		child = repeater_pck.instance()
		add_child(child)
		var con = build_node(in_dict["children"][0])
		connect_node(child.name, 0, con.name, 0)
	elif type == 9:
		child = untilSuccess_pck.instance()
		add_child(child)
		var con = build_node(in_dict["children"][0])
		connect_node(child.name, 0, con.name, 0)
	elif type == 10:
		child = untilFailure_pck.instance()
		add_child(child)
		var con = build_node(in_dict["children"][0])
		connect_node(child.name, 0, con.name, 0)
	elif type == 11:
		child = action_pck.instance()
		child.text = in_dict["function_name"]
		child.get_node("LineEdit").text = in_dict["function_name"]
		add_child(child)
	
	child.offset.x = in_dict["x"]
	child.offset.y = in_dict["y"]
	
	return child