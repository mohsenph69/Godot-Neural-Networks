extends Node2D

onready var base = $base

onready var front_sensor = $base/sensor/front
onready var left_sensor = $base/sensor/left
onready var right_sensor = $base/sensor/right


var rot_speed = 0.03
var speed = 200

var is_die = false

var net = null # network that control the car

signal die

var input = Vector2.ZERO # for now just use input.x mayble later add input.y

var time_alive = 0
var score = 0




func _physics_process(delta):
	#set_input_by_keyboard()
	set_net_input()
	base.rotation += rot_speed*input.x
	position -= base.global_transform.y*speed*delta
	time_alive += delta





func set_net_input():
	if net == null or is_die:
		print("Net is null")
		return
	# ##########[Roation of base , left_collid , front_collid, right_collide]
	var net_input = [5, 5, 5]
	if left_sensor.is_colliding():
		net_input[0] = get_distance(left_sensor.get_collision_point())
	if front_sensor.is_colliding():
		net_input[1] = get_distance(front_sensor.get_collision_point())
	if right_sensor.is_colliding():
		net_input[2] = get_distance(right_sensor.get_collision_point())
	
	var out = net.feedforward(net_input)
	input.x = out[0]*2.0 - 1


func get_distance(pos:Vector2): # max distance is 10
	var dis = (global_position - pos).length()
	if dis > 100:
		dis = 100
	dis/=20
	return dis


func set_input_by_keyboard():
	input.x = float(Input.is_action_pressed("ui_right")) - float(Input.is_action_pressed("ui_left"))


func _on_base_body_entered(body):
	if body.is_in_group("tile") and not is_die:
		is_die = true
		emit_signal("die")
		set_process(false)
		set_physics_process(false)
		visible = false
		left_sensor.enabled = false
		front_sensor.enabled = false
		right_sensor.enabled = false
		net.fitness = time_alive*0.5 + score





