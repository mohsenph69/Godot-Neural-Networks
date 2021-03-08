#include "GDNATIVEbind/network.h"
#include "vector"
#include <sstream>
#include <File.hpp>
#include "GDNATIVEbind/function.h"

using namespace godot;

void Network::_register_methods()
{
    register_method("add_layer", &Network::add_layer);
    register_method("get_layers", &Network::get_layers);
    register_method("get_layer", &Network::get_layer);
    register_method("init", &Network::init);
    register_method("get_id", &Network::get_id);
    register_method("size", &Network::size);

    register_method("randomize_weights", &Network::randomize_weights);
    register_method("randomize_biases", &Network::randomize_biases);

    register_method("print", &Network::print);
    register_method("scan", &Network::scan);

    register_method("save", &Network::save);
    register_method("load", &Network::load);

    register_method("feedforward", &Network::feedforward);
}
void Network::_init()
{

}

Network::Network()
{
    network = new NN::Network();
}

Network::~Network()
{
    if (delete_network_on_destroy)
    {
        delete network;
    }
    for(int i =0; i < layers.size() ; i++)
    {
        godot::Layer *l = layers[i];
        l->free();
    }
}

void Network::add_layer(int s)
{
    network->add_layer(s);
}

void Network::init_godot_layer()
{
    for(int i = 0 ; i < network->size(); i++)
    {
        godot::Layer* l = godot::Layer::_new();
        l->layer = network->layers.at(i);
        l->destroy_layer = false;
        layers.append(l);
    }
}

Array Network::get_layers()
{
    return layers;
}

godot::Layer* Network::get_layer(int index)
{
    return layers[index];
}


void Network::init()
{
    network->init();
    init_godot_layer();
}

int Network::get_id()
{
    return network->id;
}

int Network::size()
{
    return network->size();
}

void Network::randomize_weights()
{
    network->randomize_weights();
}
void Network::randomize_biases()
{
    network->randomize_biases();
}

String Network::print()
{
    std::stringstream st;
    network->print(st);
    String out = st.str().c_str();
    return out;
}

void Network::scan(String s)
{
    if(network->size() == 0)
    {
        std::stringstream in(s.alloc_c_string());
        network->scan(in);
        init_godot_layer();
    } else
    {
        PRINT_ERR("Network should be empty to scan new network")
    }
}

void Network::save(String path)
{
    godot::File *f = godot::File::_new();
    f->open(path,  godot::File::WRITE);
    f->store_string(this->print());
    f->close();
    f->free();
}
void Network::load(String path)
{
    godot::File *f = godot::File::_new();
    f->open(path, godot::File::READ);
    this->scan(f->get_as_text());
    f->close();
    f->free();
}

Array Network::feedforward(Array a)
{
    Col out = network->feedforward(func::array2col(a));
    return func::col2array(out);
}