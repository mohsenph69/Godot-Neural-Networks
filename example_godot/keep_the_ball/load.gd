extends Spatial

var net = GANetwork.new()
func _ready():
	net.load("res://best_nn/3.nn")
	$machine.net = net
	$machine.aplly_impulse(Vector3(rand_range(-40,40),0,rand_range(-30,30)))


func _on_Button_pressed():
	get_tree().reload_current_scene()
