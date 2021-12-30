extends Node2D



var speed = 120
var gap = 200
var is_deactive = false


signal deactive

func _ready():
	randomize()
	$root/top.position.y =  - gap/2
	$root/bottom.position.y = gap/2
	$root.position.y = randf_range(gap/2, get_viewport_rect().size.y - gap/2)


func get_pos_info():
	var info = []
	info.append($root/bottom/pos.global_position.x)
	info.append($root/top/pos.global_position.y)
	info.append($root/bottom/pos.global_position.y)
	return info


func _physics_process(delta):
	position.x -= speed*delta
	if global_position.x < 150 and not is_deactive:
		is_deactive = true
		$root/bottom/CollisionShape2D2.disabled = true
		$root/top/CollisionShape2D.disabled = true
		emit_signal("deactive")
	if global_position.x < -50:
		queue_free()


