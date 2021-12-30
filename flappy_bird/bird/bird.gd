extends Area2D


const GRAVITY = 1000
const JUMP_SPEED = 400


var jump = 0 # if greater than 0.5 jump else not jump
var vel = 0 # only in y direction

var net = null

var is_die = false
signal die

var score = 0
var time_alive = 0


var tube_pos_info = [0,0,0]

func _physics_process(delta):
	#get_input_from_key()
	get_input_from_net()
	vel += GRAVITY*delta
	time_alive += delta
	net.fitness = time_alive + 2*score
	if jump > 0.5:
		jump = 0 
		vel = - JUMP_SPEED
	position.y += vel*delta
	
	if global_position.y < 0 or global_position.y > get_viewport_rect().size.y:
		kill()



func get_input_from_net():
	var input = tube_pos_info.duplicate()
	input.append(global_position.y)
	input[0] /= get_viewport_rect().size.x/2
	input[1] /= get_viewport_rect().size.y/2
	input[2] /= get_viewport_rect().size.y/2
	input[3] /= get_viewport_rect().size.y/2
	var out = net.feedforward(input)
	jump = out[0]


func get_input_from_key():
	if Input.is_action_pressed("jump"):
		jump = 1.0
	else:
		jump = 0

func kill():
	if !is_die:
		is_die = true
		visible = false
		emit_signal("die")
		set_physics_process(false)


func _on_bird_area_entered(area):
	if area.is_in_group("tube"):
		kill()
