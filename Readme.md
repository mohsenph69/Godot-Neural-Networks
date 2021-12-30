# Godot 4.0 Neural Networks GDExtension library

Orginal [Author](https://github.com/mohsenph69)'s video about using this library (should still be pretty much the same)
**Video Tutorial**<br>
[https://www.youtube.com/playlist?list=PLhixpuPeRv9ZUP2EbfHot8eHRhUIaneMg](https://www.youtube.com/playlist?list=PLhixpuPeRv9ZUP2EbfHot8eHRhUIaneMg)

Simply create a Neural Networks for your game in Godot which is able to learn how to play. This Neural Networks library uses two methods for learning one of the is **backpropagation** and the other is **Genetic algorithm**, in-game because we don't have training data we usually use Genetic algorithm to teach the Neural Network.

**You also will be able to use this library only in c++ without Godot if you want.**

---
## How to Build

Building GDExtnsions is not properly documented by godot at this time, but this page as is somewhat useful [page](https://godotengine.org/article/introducing-gd-extensions)

use scons to build the GDExtension library for godot
``` bash
scons platform=[Your platform] target=[release or debug]
```

---
## Classes
There are four main classes which you should use to create and train Neural Networks

* **Network:** This class only create a network and is able to process the inputs and obtain outputs. But it is not able to train the Neural Networks, You can use this class when you already trained your Neural Networks and you need only to run it.
* **Layer:** Each network contain multiple layers which contain values, weights and biases, you should never create a Layer by yourself instead you should network method add_layer().
* **GDNetwork (inherit from Network):** This class use Backpropagation (Gradient descent) algorithm to teach the network. This method needs a set of data with answers.
* **GDLayer(inherit from Layer):** Each GDNetwork contain multiple layers which contain values, weights, biases and errors, you should never create a GDLayer by yourself instead you should GDnetwork method add_layer().
* **GANetwork (inherit from Network):** Use this for Genetic algorithm to teach the networks.
* **GALayer(inherit from Layer):** Each GANetwork contain multiple GALayers which contain valuers, weights and biases, you should never create a GAlayer by yourself instead you should GANetwork method add_layer().
* **Population:** Manage many GANetworks and create new GANetworks for next generation.

## Network Class

### methods
* **add_layer()**
* **init()**
* **feedforward(input)**
* **get_layers()**
* **get_layer(Layer_index)**
* **randomize_weights()**
* **randomize_biases()**
* **get_id()**
* **size()**
* **print()**
* **scan()**
* **load()**
* **save()**

## GDNetwork Class (inherit from Network)
This class has all methods of Network class, with this additional methods:
### methods
* **train(input, target)**
### properties
* **wlr** weights learning rate
* **blr** biases learning rate

## GANetwork Class (inherit from Network)
This class has all methods of Network class, with this additional methods:
### methods
* **mutate()**
* **crossover(another GALayer)**
### properties
* **fitness** 
* **normalized_fitness**
* **age**
* **mark_for_kill**

## Population Class
### methods
* **init(GANetwork)**
* **arr_init(Array of GANetwork)**
* **get_networks()**
* **randomize()**
* **epoch()**
* **get_bests()**

### peropeties
* **size** 
* **crossover_rate**
* **mutation_rate**
* **mutation_power** 
* **keep_best_rate** 
* **kill_worse_rate**
* **max_fitness**
* **mean_fitness**
* **generation**

