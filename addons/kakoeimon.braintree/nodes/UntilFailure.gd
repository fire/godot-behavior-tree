tool
extends "Decorator.gd"

func get_dict(graph):
	var dict = .get_dict(graph)
	dict.type = 10
	return dict