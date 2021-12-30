#include "GDExtensionBind/network.h"


using namespace godot;

void Network::_bind_methods()
{   

    ClassDB::bind_method(D_METHOD("add_layer", "size"), &Network::add_layer);
    ClassDB::bind_method(D_METHOD("get_layers"), &Network::get_layers);
    ClassDB::bind_method(D_METHOD("get_layer", "index"), &Network::get_layer);
    ClassDB::bind_method(D_METHOD("init"), &Network::init);
    ClassDB::bind_method(D_METHOD("get_id"), &Network::get_id);
    ClassDB::bind_method(D_METHOD("size"), &Network::size);

    ClassDB::bind_method(D_METHOD("randomize_weights"), &Network::randomize_weights);
    ClassDB::bind_method(D_METHOD("randomize_biases"), &Network::randomize_biases);

    ClassDB::bind_method(D_METHOD("print"), &Network::print);
    ClassDB::bind_method(D_METHOD("scan", "s"), &Network::scan);

    ClassDB::bind_method(D_METHOD("save", "path"), &Network::save);
    ClassDB::bind_method(D_METHOD("load", "path"), &Network::load);

    ClassDB::bind_method(D_METHOD("feedforward", "input"), &Network::feedforward);
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
        godot::Layer* l = Object::cast_to<godot::Layer>(layers[i]);
        memdelete(l);
    }
}

void Network::add_layer(int size)
{
    network->add_layer(size);
}

void Network::init_godot_layer()
{
    for(int i = 0 ; i < network->size(); i++)
    {
        godot::Layer* l = memnew(godot::Layer);
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
    return Object::cast_to<Layer>(layers[index].operator Object*());
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
        std::stringstream in(s.ascii().get_data());
        network->scan(in);
        init_godot_layer();
    } else
    {
        PRINT_ERR("Network should be empty to scan new network")
    }
}

void Network::save(String path)
{
    godot::File *f = memnew(godot::File);
    f->open(path,  godot::File::WRITE);
    f->store_string(this->print());
    f->close();
    memdelete(f);
}
void Network::load(String path)
{   
    godot::File *f = memnew(godot::File);
    f->open(path, godot::File::READ);
    this->scan(f->get_as_text());
    f->close();
    memdelete(f);
}

Array Network::feedforward(Array input)
{
    Col out = network->feedforward(func::array2col(input));
    return func::col2array(out);
}