#ifndef _G_NETWORK
#define _G_NETWORK

#include "core/network.h"

#include <godot_cpp/core/class_db.hpp>

#include <sstream>
#include <godot_cpp/classes/file.hpp>
#include "GDExtensionBind/function.h"

#include "GDExtensionBind/layer.h"


namespace godot
{

class Network : public Node 
{
    GDCLASS(Network , Node)

protected:
	static void _bind_methods();
public:
    bool delete_network_on_destroy = true;
    NN::Network* network = nullptr;
    Array layers;
    void _init();
    Network();
    ~Network();
    virtual void add_layer(int);
    void init_godot_layer();
    
    Array get_layers();
    godot::Layer* get_layer(int);


    virtual void init();

    int get_id();

    int size();

    void randomize_weights();
    void randomize_biases();

    String print();
    virtual void scan(String);
 
    void save(String);
    void load(String);

    Array feedforward(Array);
};

}

#endif