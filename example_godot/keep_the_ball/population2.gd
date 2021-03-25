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
	print("continue train")
	var nets = []
	for i in range(0,10):
		var net = GANetwork.new()
		net.load("res://current_best_nn/nn_" + str(i) + ".nn")
		nets.push_back(net)
	
	pop.size = 400
	pop.mutation_rate = 0.2
	pop.mutation_power = 0.5
	pop.crossover_rate = 0.1
	pop.keep_best_rate = 0.01
	pop.kill_worse_rate = 0.4
	pop.arr_init(nets)
	# pop.randomize() # Remember you should not randomize when you contineue to learn
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
	
	var init_impulse = Vector3(sign(rand_range(-1,1))*rand_range(20,30), 0 , sign(rand_range(-1,1))*rand_range(20,30))
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

var show_index = -1
func _on_watch_the_best_button_up():
	if show_index >= get_child_count() - 1:
		show_index = -1
	while(show_index < get_child_count()):
		show_index += 1
		var best = get_child(show_index)
		if best != null:
			if not best.is_die:
				var offset = Vector3(0, 2.5, 3)
				best_camera.global_transform.origin = best.global_transform.origin + offset
				best_camera.current = true
				break
		


func best_fitness(a, b):
	return a.net.fitness > b.net.fitness

func _on_all_button_up():
	all_camera.current = true
