extends Node2D

var car_res = preload("res://car_root/car.tscn")
onready var gen_label = get_parent().get_node("gen")

var pop = Population.new()
var num_cars = 0
var num_die = 0

func _ready():
	var net = GANetwork.new()
	net.add_layer(3)
	net.add_layer(6)
	net.add_layer(1)
	net.init()
	
	pop.size = 50
	pop.mutation_rate = 0.5
	pop.mutation_power = 10
	pop.crossover_rate = 0.1
	pop.keep_best_rate = 0.1
	pop.kill_worse_rate = 0.5
	pop.init(net)
	create_cars()


func die_car():
	num_die += 1
	if num_die == num_cars:
		for car in get_children():
			car.queue_free()
		pop.call_deferred("epoch")
		call_deferred("create_cars")
		num_die = 0


func create_cars():
	gen_label.text = str(pop.generation)
	var networks = pop.get_networks()
	num_cars = networks.size()
	for net in networks:
		var car = car_res.instance()
		car.net = net
		car.connect("die" , self, "die_car" )
		add_child(car)
	





