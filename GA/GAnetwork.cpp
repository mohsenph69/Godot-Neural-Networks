#include "GA/GAnetwork.h"

using namespace NN;


void GANetwork::add_layer(int size)
{
    GALayer * layer = new GALayer(size);
    GAlayers.push_back(layer);
    layers.push_back(layer);
}

void GANetwork::add_layer()
{
    GALayer * layer = new GALayer();
    GAlayers.push_back(layer);
    layers.push_back(layer);
}

void  GANetwork::add_layer(GALayer* layer)
{
    GAlayers.push_back(layer);
    layers.push_back(layer);
}


GANetwork *GANetwork::clone_all()
{
    GANetwork* new_net = new GANetwork();
    for(int i=0; i < size() ; i++)
    {
        GALayer * new_layer = GAlayers.at(i)->clone();
        new_net->add_layer(new_layer);
    }
    new_net->fitness = fitness;
    new_net->age = age;
    new_net->normalized_fitness = normalized_fitness;
    new_net->set_activation_function(activation_function);
    new_net->set_prev_layers();
    return new_net;
}

GANetwork *GANetwork::clone()
{
    GANetwork* new_net = new GANetwork();
    for(int i=0; i < size() ; i++)
    {
        GALayer * new_layer = GAlayers.at(i)->clone();
        new_net->add_layer(new_layer);
    }
    new_net->set_activation_function(activation_function);
    new_net->set_prev_layers();
    return new_net;
}

std::vector<GALayer* > *GANetwork::get_layers()
{
    return &GAlayers;
}


void GANetwork::mutate(double rate, double power)
{
    for(int i = 1 ; i < size() ; i++)
    {
        GAlayers.at(i)->mutate(rate, power);
    }
}

GANetwork * GANetwork::crossover(GANetwork *other)
{
    GANetwork * new_net = new GANetwork();
    // Adding the first layer with no weights and biases
    GALayer* first_layer = GAlayers.at(0)->clone();
    new_net->add_layer(first_layer);

    double fist_section = func::random();

    for(int i = 1 ; i < size() ; i++)
    {
        GALayer* new_layer = GAlayers.at(i)->crossover(fist_section, other->get_layers()->at(i) );
        new_net->add_layer(new_layer);
    }
    GALayer* new_layer = new_net->GAlayers.at(1);
    new_net->set_activation_function(activation_function);
    new_net->set_prev_layers();
    return new_net;
}