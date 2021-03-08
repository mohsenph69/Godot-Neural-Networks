#include "GD/GDnetwork.h"

using namespace NN;



void GDNetwork::add_layer(int size)
{
    GDLayer * layer = new GDLayer(size);
    GDlayers.push_back(layer);
    layers.push_back(layer);
}

void GDNetwork::add_layer()
{
    GDLayer * layer = new GDLayer();
    GDlayers.push_back(layer);
    layers.push_back(layer);
}


std::vector<GDLayer* > *GDNetwork::get_layers()
{
    return &GDlayers;
}

void GDNetwork::init()
{
    Network::init();
    set_prev_layers();
}

void GDNetwork::set_prev_layers()
{
    set_d_activation_function(activation_function);
    Network::set_prev_layers();
    for(unsigned i = 1 ; i < size() ; i++)
    {
        GDlayers.at(i)->prev_GDlayer = GDlayers.at(i -1);
    }
}


void GDNetwork::set_d_activation_function(activation a)
{
    Func f;
    switch (a)
    {
    case activation::sigmoid:
        f = func::dsigmoid;
        break;
    }

    for(unsigned i = 0 ; i < GDlayers.size() ; i++)
    {
        GDlayers.at(i)->d_activation_pointer = f;
    }   
}


void GDNetwork::backprop_error(Col target)
{
    // Calculate last output with target
    GDlayers.back()->output_error(target);
    // backprop error to the rest of neuron
    for(unsigned i = size() - 1; i > 1 ; i--)
    {
        GDlayers.at(i)->prev_error();
    }
}

void GDNetwork::backprop_dw()
{
    for(unsigned i = size() - 1; i >= 1 ; i--)
    {
        GDlayers.at(i)->calc_dw();
    }
}


Col GDNetwork::train(Col input, Col target)
{
    if(target.rows() != GDlayers.back()->values.rows() )
    {
        PRINT_ERR("target values are not in correct size")
        exit(1);
    }
    feedforward(input);
    backprop_error(target);
    backprop_dw();
    for(unsigned i = 1; i < size() ; i++)
    {
        GDLayer *l = GDlayers.at(i);
        l->weights  += l->dw * wlr;
        l->biases  += l->errors * blr;
    }
    return GDlayers.back()->values;
}