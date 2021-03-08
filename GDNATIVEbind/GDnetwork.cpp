#include "GDNATIVEbind/GDnetwork.h"
#include "GDNATIVEbind/function.h"

using namespace godot;


void GDNetwork::_register_methods()
{
    register_method("get_layer", &GDNetwork::get_layer);
    register_method("train", &GDNetwork::train);

    register_property<GDNetwork, double>("wlr" , &GDNetwork::set_wlr, &GDNetwork::get_wlr, 0.0);
    register_property<GDNetwork, double>("blr" , &GDNetwork::set_blr, &GDNetwork::get_blr, 0.0);
}

GDNetwork::GDNetwork()
{
    GDnetwork = new NN::GDNetwork();
    network = GDnetwork;
}

void GDNetwork::_init()
{

}
void GDNetwork::add_layer(int size)
{
    GDnetwork->add_layer(size);
}


void GDNetwork::init()
{
    GDnetwork->init();
    for(int i = 0 ; i < GDnetwork->size(); i++)
    {
        godot::GDLayer* l = godot::GDLayer::_new();
        l->GDlayer = GDnetwork->GDlayers.at(i);
        l->layer = GDnetwork->GDlayers.at(i);
        l->destroy_layer = false;
        layers.append(l);
    } 
}

GDLayer* GDNetwork::get_layer(int index)
{
    return layers[index];
}


double GDNetwork::get_wlr()
{
    return GDnetwork->wlr;
}
void GDNetwork::set_wlr(double input)
{
    GDnetwork->wlr = input;
}

double GDNetwork::get_blr()
{
    return GDnetwork->blr;
}
void GDNetwork::set_blr(double input)
{
    GDnetwork->blr = input;
}

Array GDNetwork::train(Array input, Array target)
{
    Col out = GDnetwork->train( func::array2col(input) , func::array2col(target) );
    return func::col2array(out);
}


void GDNetwork::scan(String s)
{
    if(network->size() == 0)
    {
        std::stringstream in(s.alloc_c_string());
        GDnetwork->scan(in);
        network = GDnetwork;
        for(int i = 0 ; i < GDnetwork->size(); i++)
        {
            godot::GDLayer* l = godot::GDLayer::_new();
            l->GDlayer = GDnetwork->GDlayers.at(i);
            l->layer = GDnetwork->GDlayers.at(i);
            l->destroy_layer = false;
            layers.append(l);
        } 
    } else
    {
        PRINT_ERR("Network should be empty to scan new network")
    }
}