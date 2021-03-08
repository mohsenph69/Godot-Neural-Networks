#ifndef _G_NETWORK
#define _G_NETWORK

#include "core/network.h"
#include "Godot.hpp"
#include "Object.hpp"

#include "GDNATIVEbind/layer.h"


namespace godot
{

class Network : public Object 
{
    GODOT_CLASS(Network , Object)

    public:
    bool delete_network_on_destroy = true;
    NN::Network* network;
    Array layers;
    static void _register_methods();
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