extends Node2D



func _physics_process(delta):
	for bird in $birds.get_children():
		if bird.is_in_group("bird"):
			bird.tube_pos_info = $spawn.get_pos_info()




func _on_spawn_pass_tube():
	for bird in $birds.get_children():
		if bird.is_in_group("bird"):
			if not bird.is_die:
				bird.score += 1
