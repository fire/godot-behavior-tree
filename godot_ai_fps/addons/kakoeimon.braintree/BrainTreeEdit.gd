tool
extends Control

# class member variables go here, for example:
# var a = 2
# var b = "textvar"
var dict = {}

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

onready var graph = $GraphEdit
onready var menu = $PopupMenu

enum node_types {composite, decorator, leaf}

var _from
var _from_slot

var selected_braintree = null

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	_setup_menu()
	if dict.empty():
		var c = sequencer_pck.instance()
		graph.add_child(c)
	pass

#func _process(delta):
#	# Called every frame. Delta is time since last frame.
#	# Update game logic here.
#	pass

func _setup_menu():
	menu.clear()
	menu.add_check_item("Selector", 0)
	menu.add_check_item("Sequence", 1)
	menu.add_check_item("StatefulSelector", 2)
	menu.add_check_item("MemSequence", 3)
	menu.add_check_item("ParallelSequence", 4)
	menu.add_check_item("Succeeder", 5)
	menu.add_check_item("Failer", 6)
	menu.add_check_item("Inverter", 7)
	menu.add_check_item("Repeater", 8)
	menu.add_check_item("UntilSuccess", 9)
	menu.add_check_item("UntilFailure", 10)
	menu.add_check_item("Action", 11)

func _on_GraphEdit_connection_to_empty(from, from_slot, release_position):
	menu.popup()
	menu.rect_position = release_position + get_global_rect().position
	_from = from
	_from_slot = from_slot
	pass # replace with function body


func _on_PopupMenu_id_pressed(ID):
	var n
	if(ID == 0):
		n = selector_pck.instance()
	elif(ID == 1):
		n = sequencer_pck.instance()
	elif(ID == 2):
		n = statefulSelector_pck.instance()
	elif(ID == 3):
		n = memSequence_pck.instance()
	elif(ID == 4):
		n = parallelSequence_pck.instance()
	elif(ID == 5):
		n = succeeder_pck.instance()
	elif(ID == 6):
		n = failer_pck.instance()
	elif(ID == 7):
		n = inverter_pck.instance()
	elif(ID == 8):
		n = repeater_pck.instance()
	elif(ID == 9):
		n = untilSuccess_pck.instance()
	elif(ID == 10):
		n = untilFailure_pck.instance()
	elif(ID == 11):
		n = action_pck.instance()
		
	graph.add_child(n)
	n.offset = menu.rect_position - get_global_rect().position + graph.scroll_offset
	graph.connect_node(_from, _from_slot, n.name, 0)
	pass # replace with function body

func build_from_selected():
	for child in graph.get_children():
		if child is GraphNode:
			child.free()
	dict = selected_braintree.get_dict()
	
	if not dict.empty():
		build_node(dict)
	else:
		graph.add_child(sequencer_pck.instance())
	
	pass
	
func build_node(in_dict):
	var type = int(in_dict["type"])
	var child
	if type == 0:
		child = selector_pck.instance()
		graph.add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			graph.connect_node(child.name, 0, con.name, 0)
	elif type == 1:
		child = sequencer_pck.instance()
		graph.add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			graph.connect_node(child.name, 0, con.name, 0)
	elif type == 2:
		child = statefulSelector_pck.instance()
		graph.add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			graph.connect_node(child.name, 0, con.name, 0)
	elif type == 3:
		child = memSequence_pck.instance()
		graph.add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			graph.connect_node(child.name, 0, con.name, 0)
	elif type == 4:
		child = parallelSequence_pck.instance()
		graph.add_child(child)
		for c in in_dict["children"]:
			var con = build_node(c)
			graph.connect_node(child.name, 0, con.name, 0)
	elif type == 5:
		child = succeeder_pck.instance()
		graph.add_child(child)
		var con = build_node(in_dict["children"][0])
		graph.connect_node(child.name, 0, con.name, 0)
	elif type == 6:
		child = failer_pck.instance()
		graph.add_child(child)
		var con = build_node(in_dict["children"][0])
		graph.connect_node(child.name, 0, con.name, 0)
	elif type == 7:
		child = inverter_pck.instance()
		graph.add_child(child)
		var con = build_node(in_dict["children"][0])
		graph.connect_node(child.name, 0, con.name, 0)
	elif type == 8:
		child = repeater_pck.instance()
		graph.add_child(child)
		var con = build_node(in_dict["children"][0])
		graph.connect_node(child.name, 0, con.name, 0)
	elif type == 9:
		child = untilSuccess_pck.instance()
		graph.add_child(child)
		var con = build_node(in_dict["children"][0])
		graph.connect_node(child.name, 0, con.name, 0)
	elif type == 10:
		child = untilFailure_pck.instance()
		graph.add_child(child)
		var con = build_node(in_dict["children"][0])
		graph.connect_node(child.name, 0, con.name, 0)
	elif type == 11:
		child = action_pck.instance()
		child.text = in_dict["function_name"]
		child.get_node("LineEdit").text = in_dict["function_name"]
		graph.add_child(child)
	
	child.offset.x = in_dict["x"]
	child.offset.y = in_dict["y"]
	
	return child
	
func get_dict():
	dict = {}
	var first
	for c in graph.get_children():
		if c is GraphNode:
			if first:
				if c.offset.x < first.offset.x:
					first = c
			else:
				first = c
				
	dict = first.get_dict(graph)
	return dict
	
func get_node_type(node):
	
	if node is preload("nodes/Selector.gd"):
		return 0
	elif node is preload("nodes/Sequence.gd"):
		return 1
	elif node is preload("nodes/StatefulSelector.gd"):
		return 2
	elif node is preload("nodes/MemSequence.gd"):
		return 3
	elif node is preload("nodes/ParallelSequence.gd"):
		return 4
	elif node is preload("nodes/Succeeder.gd"):
		return 5
	elif node is preload("nodes/Failer.gd"):
		return 6
	elif node is preload("nodes/Inverter.gd"):
		return 7
	elif node is preload("nodes/Repeater.gd"):
		return 8
	elif node is preload("nodes/UntilSuccess.gd"):
		return 9
	elif node is preload("nodes/UntilFailure.gd"):
		return 10
	elif node is preload("nodes/Action.gd"):
		return 11

func _on_GraphEdit_delete_nodes_request():
	for n in graph.get_children():
		if n is GraphNode and n.selected:
			var list = graph.get_connection_list()
			for c in list:
				if c.from == n.name or c.to == n.name:
					graph.disconnect_node(c.from, c.from_port, c.to, c.to_port)
					
	for n in graph.get_children():
		if n is GraphNode and n.selected:
			n.free()
	pass # replace with function body


func _on_GraphEdit_disconnection_request(from, from_slot, to, to_slot):
	graph.disconnect_node(from, from_slot, to, to_slot)
	pass # replace with function body


func _on_GraphEdit_connection_request(from, from_slot, to, to_slot):
	graph.connect_node(from, from_slot, to, to_slot)
	pass # replace with function body
