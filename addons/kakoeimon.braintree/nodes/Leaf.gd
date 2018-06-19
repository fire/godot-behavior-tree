tool
extends GraphNode

# class member variables go here, for example:
# var a = 2
# var b = "textvar"
var text = ""


func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	pass

#func _process(delta):
#	# Called every frame. Delta is time since last frame.
#	# Update game logic here.
#	pass
func get_dict(graph):
	return {"type":2, "function_name": text, "x": offset.x, "y":offset.y}

func _on_LineEdit_text_changed(new_text):
	text = new_text
	var f = get_font("")
	var size = f.get_string_size(text)
	print(size)
	rect_size.x = size.x + 50
	update()
	$LineEdit.update()
	title = new_text
	pass # replace with function body




