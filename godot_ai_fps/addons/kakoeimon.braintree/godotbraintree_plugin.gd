tool
extends EditorPlugin

const godotbraintree_edit_pck = preload("res://addons/kakoeimon.braintree/BrainTreeEdit.tscn")

var braintree_edit = null
var brainttree_button = null


func _enter_tree():
	#add_custom_type("BrainTree", "Node", preload("res://addons/kakoeimon.braintree/GodotBrainTree.gdns"), preload("res://addons/kakoeimon.braintree/braintree.png"))
	braintree_edit = godotbraintree_edit_pck.instance()
	brainttree_button = add_control_to_bottom_panel(braintree_edit, "BrainTree")
	brainttree_button.hide()
	get_editor_interface().get_selection().connect("selection_changed", self, "on_selection_changed")

func _exit_tree():
	#apply_changes()
	remove_custom_type("BrainTree")
	remove_control_from_bottom_panel(braintree_edit)
	#braintree_edit.selected_braintree = null
	braintree_edit.free()
	brainttree_button = null
	print("brain tree exit tree")
	
	
func on_selection_changed():
	
	apply_changes()
	var selected_nodes = get_editor_interface().get_selection().get_selected_nodes()
	if(selected_nodes.size()!=1):
		braintree_edit.hide()
		brainttree_button.hide()
		braintree_edit.selected_braintree = null
		return
	var selected_node = selected_nodes[0]
	
	if(selected_node and not selected_node.is_queued_for_deletion() and selected_node.has_method("is_brain_tree")):
		braintree_edit.selected_braintree = selected_node
		braintree_edit.build_from_selected()
		if brainttree_button.pressed:
			braintree_edit.show()
		brainttree_button.show()
	else:
		braintree_edit.hide()
		brainttree_button.hide()
		braintree_edit.selected_braintree = null
		
	
func apply_changes():
	if braintree_edit and braintree_edit.selected_braintree:
		var braintree = braintree_edit.selected_braintree
		var dict = braintree_edit.get_dict()
		braintree.set_dict(dict)
	