extends Spatial


onready var sphere = get_node("base/stand/sphere")
onready var platform = get_node("base/stand/sphere/platform")
onready var platform_mat = get_node("base/stand/sphere/platform/mesh").material_override
onready var ball = get_node("ball")



const ROT_SPEED = 3
#const ROT_SPEED = 200

var input = Vector3.ZERO
var dis = Vector3.ZERO

var net = null

var is_die = false
signal die

var init_impulse = Vector3.ZERO


var time_alive = 0

func _ready():
	ball.apply_impulse(Vector3.ZERO, init_impulse)


func aplly_impulse(im:Vector3):
	ball.apply_impulse(Vector3.ZERO, im)

func _physics_process(delta):
	dis = ball.global_transform.origin - global_transform.origin
	if dis.y < 0.5:
		die()
	time_alive += delta
	net.fitness = time_alive*time_alive
	#get_input_from_key()
	get_input_from_net()
	#sphere.rotation_degrees += Vector3(input[0], 0 , input[1])*ROT_SPEED*delta
	var rot_axis = Vector3(input[0], 0, input[1]).cross(Vector3(0,1,0))
	#rot_axis = sphere.global_transform *rot_axis
	rot_axis = rot_axis.normalized()
	sphere.global_rotate(rot_axis, input[2]*ROT_SPEED*delta)
	#sphere.rotate(Vector3(1,0,0), input[0]*ROT_SPEED*delta)
	#sphere.rotate(Vector3(0,0,1), input[1]*ROT_SPEED*delta)
	
	if abs(sphere.rotation_degrees.x) > 80:
		sphere.rotation_degrees.x = sign(sphere.rotation_degrees.x)*80
	if abs(sphere.rotation_degrees.z) > 80:
		sphere.rotation_degrees.z = sign(sphere.rotation_degrees.z)*80


func die():
	if not is_die:
		is_die = true
		set_physics_process(false)
		platform_mat.albedo_color = Color(1,0,0)
		ball.queue_free()
		get_node("Area").queue_free()
		emit_signal("die")


func get_input_from_net():
	input = []
	var v = ball.linear_velocity
	#var net_input = [dis.x, dis.y, dis.z]
	var net_input = [v.x, v.z, dis.x, dis.z]
	var out = net.feedforward(net_input)
	for i in range(0,2):
		input.append(out[i]*2 - 1)
	input.append(out[2])
func get_input_from_key():
	input[0] = int(Input.is_action_pressed("ui_right")) - int(Input.is_action_pressed("ui_left"))
	input[1] = int(Input.is_action_pressed("ui_up")) - int(Input.is_action_pressed("ui_down"))


func _on_Area_body_entered(body):
	if body == ball:
		die()
