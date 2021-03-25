extends Spatial


onready var best_camera = get_parent().get_node("best_camera")
onready var all_camera = get_parent().get_node("all_camera")
onready var gen_label = get_parent().get_node("V/Label")

var machine_res = preload("res://machine/machine.tscn")
var machine_dis = 6
var num_col = 14

var pop = Population.new()

var num_machine = 0
var num_die = 0

func _ready():
	print("Start train")
	var net = GANetwork.new()
	net.add_layer(4) #input
	net.add_layer(10)
	net.add_layer(10)
	net.add_layer(3) # output
	net.init()
	
	pop.size = 300
	pop.mutation_rate = 0.7
	pop.mutation_power = 20
	pop.crossover_rate = 0.2
	pop.keep_best_rate = 0.01
	pop.kill_worse_rate = 0
	pop.init(net)
	pop.randomize()
	create_machines()



func create_machines():
	print("gen: " + str(pop.generation) + " max_fitness: " + str(pop.max_fitness))
	gen_label.text = "Generation: " + str(pop.generation) 
	var networks = pop.get_networks()
	num_die = 0
	num_machine = networks.size()
	var machine_pos_x = - machine_dis*num_col/2
	var machine_pos_z = 0
	var add_in_row = 0
	# init impulse
	var impulse_dir = Vector3(rand_range(-1,1), 0 ,rand_range(-1,1))
	impulse_dir = impulse_dir.normalized()
	var init_impulse = impulse_dir*rand_range(30,45)
	for net in networks:
		var machine = machine_res.instance()
		machine.net = net
		machine.init_impulse = init_impulse
		machine.connect("die", self, "die_machine")
		machine.transform.origin = Vector3(machine_pos_x,0,machine_pos_z)
		machine_pos_x += machine_dis
		add_in_row += 1
		if add_in_row > num_col:
			add_in_row = 0
			machine_pos_z -= machine_dis
			machine_pos_x = - machine_dis*num_col/2
		add_child(machine)


	


func die_machine():
	num_die += 1
	if num_die >= num_machine:
		var bests = pop.get_bests()
		for i in range(0,10):
			bests[i].save("res://current_best_nn/nn_" + str(i) + ".nn")
		for m in get_children():
			m.queue_free()
		pop.call_deferred("epoch")
		call_deferred("create_machines")



func next_generation():
	num_die = num_machine - 1
	die_machine()


func _on_watch_the_best_button_up():
	var children = get_children()
	children.sort_custom(self, "best_fitness")
	var best = children[0]
	var offset = Vector3(0, 2.5, 3)
	best_camera.global_transform.origin = best.global_transform.origin + offset
	best_camera.current = true


func best_fitness(a, b):
	return a.net.fitness > b.net.fitness

func _on_all_button_up():
	all_camera.current = true
