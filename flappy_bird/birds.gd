extends Node2D


var pop = Population.new()


var bird_res = preload("res://bird/bird.tscn")

var num_bird = 0
var num_die = 0


func _ready():
	var net = GANetwork.new()
	net.add_layer(4) # input layer
	net.add_layer(4) # hidden layer
	net.add_layer(1) # jump or not jump this is a question
	net.init()
	
	pop.mutation_rate = 0.2
	pop.mutation_power = 2
	pop.crossover_rate = 0.3
	pop.kill_worse_rate = 0.2
	pop.keep_best_rate = 0.1
	pop.size = 100
	pop.init(net)
	pop.randomize() # call this for the first time
	
	create_birds()



func create_birds():
	var networks = pop.get_networks()
	num_die = 0
	num_bird = networks.size()
	$Label.text = "Pop Size: "+ str(num_bird-num_die)
	
	for net in networks:
		var bird = bird_res.instantiate()
		bird.net = net
		add_child(bird)
		bird.connect("die" ,Callable(self, "bird_die"))


func bird_die():
	num_die += 1
	$Label.text = "Pop Size: "+ str(num_bird-num_die)
	if num_die == num_bird:
		for bird in get_children():
			if bird.is_in_group("bird"):
				bird.queue_free()
		get_parent().get_node("spawn").stop()
		get_parent().get_node("spawn").start()
		pop.call_deferred("epoch")
		call_deferred("create_birds")







