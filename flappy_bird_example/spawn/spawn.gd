extends Node2D


var spawn_time = 3

const TUB_RES = preload("res://tube/tube.tscn")

signal pass_tube


var tubes = []

func _ready():
	$Timer.wait_time = spawn_time
	_on_Timer_timeout()

func stop():
	for t in get_children():
		if t.is_in_group("tube_root"):
			t.queue_free()
	$Timer.stop()
	tubes = []

func start():
	$Timer.start()
	_on_Timer_timeout()

func _on_Timer_timeout():
	var tube = TUB_RES.instantiate()
	tube.global_position.x = get_viewport_rect().size.x + 50
	add_child(tube)
	tubes.append(tube)
	tube.connect("deactive", Callable(self, "tube_deactive"))

func get_pos_info():
	return tubes[0].get_pos_info()

func tube_deactive():
	tubes.pop_front()
	emit_signal("pass_tube")




