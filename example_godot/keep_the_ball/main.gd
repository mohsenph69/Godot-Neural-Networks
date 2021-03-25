extends Control


func _on_train_button_up():
	get_tree().change_scene("res://train.tscn")


func _on_load_button_up():
	get_tree().change_scene("res://load.tscn")


func _on_continue_train_button_up():
	get_tree().change_scene("res://train2.tscn")
