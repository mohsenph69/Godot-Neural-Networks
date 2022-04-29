#include "GDnetwork.h"
#include "function.h"

using namespace godot;


void GDNetwork::_bind_methods()
{

    ClassDB::bind_method(D_METHOD("get_layer","size"), &GDNetwork::get_layer);
    ClassDB::bind_method(D_METHOD("train","input","target"), &GDNetwork::train);
    
    ClassDB::bind_method(D_METHOD("set_wlr", "input"), &GDNetwork::set_wlr);
	ClassDB::bind_method(D_METHOD("get_wlr"), &GDNetwork::get_wlr);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"wrl"), "set_wlr", "get_wlr");


    ClassDB::bind_method(D_METHOD("set_blr", "input"), &GDNetwork::set_blr);
	ClassDB::bind_method(D_METHOD("get_blr"), &GDNetwork::get_blr);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"blr"), "set_blr", "get_blr");
}

GDNetwork::GDNetwork()
{
    gdnetwork = new NN::GDNetwork();
    network = gdnetwork;
}

void GDNetwork::_init()
{

}

void GDNetwork::add_layer(int size)
{
    gdnetwork->add_layer(size);
}


void GDNetwork::init()
{
    gdnetwork->init();
    for(int i = 0 ; i < gdnetwork->size(); i++)
    {
        godot::GDLayer* l = memnew(godot::GDLayer());
        l->GDlayer = gdnetwork->GDlayers.at(i);
        l->layer = gdnetwork->GDlayers.at(i);
        l->destroy_layer = false;
        layers.append(l);
    } 
}

GDLayer* GDNetwork::get_layer(int index)
{
    return Object::cast_to<GDLayer>(layers[index]);

}


double GDNetwork::get_wlr()
{
    return gdnetwork->wlr;
}
void GDNetwork::set_wlr(double input)
{
    gdnetwork->wlr = input;
}

double GDNetwork::get_blr()
{
    return gdnetwork->blr;
}
void GDNetwork::set_blr(double input)
{
    gdnetwork->blr = input;
}

Array GDNetwork::train(Array input, Array target)
{
    Col out = gdnetwork->train( func::array2col(input) , func::array2col(target) );
    return func::col2array(out);
}


void GDNetwork::scan(String s)
{
    if(network->size() == 0)
    {
        std::stringstream in(s.ascii().get_data());
        gdnetwork->scan(in);
        network = gdnetwork;
        for(int i = 0 ; i < gdnetwork->size(); i++)
        {
            godot::GDLayer* l = memnew(godot::GDLayer());
            l->GDlayer = gdnetwork->GDlayers.at(i);
            l->layer = gdnetwork->GDlayers.at(i);
            l->destroy_layer = false;
            layers.append(l);
        } 
    } else
    {
        PRINT_ERR("Network should be empty to scan new network")
    }
}