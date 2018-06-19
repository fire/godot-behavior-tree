extends Node

# class member variables go here, for example:
# var a = 2
# var b = "textvar"
onready var brain = $GodotBrainTree

func _ready():
	# Called every time the node is added to the scene.
	# Initialization here
	brain.setup()
	var time = OS.get_ticks_msec()
	for i in range(100000):
		brain.update()
	
	print(OS.get_ticks_msec() - time)
	get_node("GodotBrainTree").queue_free()

func test():
	#print("test")
	return 2

