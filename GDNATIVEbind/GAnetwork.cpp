#include "GDNATIVEbind/GAnetwork.h"

using namespace godot;


void GANetwork::_register_methods()
{
    register_property<GANetwork, double>("fitness" , &GANetwork::set_fitness, &GANetwork::get_fitness, 0);
    register_property<GANetwork, double>("normalized_fitness" , &GANetwork::set_normalized_fitness, &GANetwork::get_normalized_fitness, 0);
    register_property<GANetwork, int>("age" , &GANetwork::set_age, &GANetwork::get_age, 0);
    register_property<GANetwork, bool>("mark_for_kill" , &GANetwork::set_mark_for_kill, &GANetwork::get_mark_for_kill, 0);

    register_method("mutate", &GANetwork::mutate);
    register_method("crossover", &GANetwork::crossover);
}

void GANetwork::_init()
{

}



GANetwork::GANetwork()
{
    GAnetwork = new NN::GANetwork();
    network = GAnetwork;
}

double GANetwork::get_fitness()
{
    return GAnetwork->fitness;
}
void GANetwork::set_fitness(double d)
{
    if (d < 0)
    {
        d = 0;
    }
    GAnetwork->fitness = d;
}

double GANetwork::get_normalized_fitness()
{
    return GAnetwork->normalized_fitness;
}
void GANetwork::set_normalized_fitness(double d)
{
    if (d < 0)
    {
        d = 0;
    }
    GAnetwork->normalized_fitness = d;
}

int GANetwork::get_age()
{
    return GAnetwork->age;
}

void GANetwork::set_age(int i)
{
    GAnetwork->age = i;
}

bool GANetwork::get_mark_for_kill()
{
    return GAnetwork->mark_for_kill;
}

void GANetwork::set_mark_for_kill(bool b)
{
    GAnetwork->mark_for_kill = b;
}


void GANetwork::mutate(double rate, double power)
{
    GAnetwork->mutate(rate, power);
}

GANetwork* GANetwork::crossover(GANetwork* other)
{
    NN::GANetwork* new_nn_net = GAnetwork->crossover(other->GAnetwork);
    godot::GANetwork *g = godot::GANetwork::_new();
    g->GAnetwork = new_nn_net;
    g->network = new_nn_net;
    g->init_godot_layer();
    return g;
}