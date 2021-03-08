#include "population.h"


using namespace godot;

void Population::_register_methods()
{
    register_method("init", &Population::init);
    register_method("arr_init", &Population::arr_init);
    register_method("get_networks", &Population::get_networks);
    register_method("randomize", &Population::randomize);
    register_method("epoch", &Population::epoch);
    register_method("get_bests", &Population::get_bests);

    register_property<Population, double>("crossover_rate" , &Population::set_crossover_rate, &Population::get_crossover_rate, 0);
    register_property<Population, double>("mutation_rate" , &Population::set_mutation_rate, &Population::get_mutation_rate, 0);
    register_property<Population, double>("mutation_power" , &Population::set_mutation_power, &Population::get_mutation_power, 0);
    register_property<Population, double>("keep_best_rate" , &Population::set_keep_best_rate, &Population::get_keep_best_rate, 0);
    register_property<Population, double>("kill_worse_rate" , &Population::set_kill_worse_rate, &Population::get_kill_worse_rate, 0);
    register_property<Population, double>("max_fitness" , &Population::set_max_fitness, &Population::get_max_fitness, 0);
    register_property<Population, double>("mean_fitness" , &Population::set_mean_fitness, &Population::get_mean_fitness, 0);
    register_property<Population, int>("size" , &Population::set_size, &Population::get_size, 0);
    register_property<Population, int>("generation" , &Population::set_generation, &Population::get_generation, 0);

}

void Population::_init()
{

}

Population::Population()
{
    population = new  NN::Population();
}

Population::~Population()
{
    delete population;
}

void Population::init(GANetwork* g)
{
    population->init(g->GAnetwork);
    recreate_networks();
}

void Population::arr_init(Array in_arr)
{
    std::vector<NN::GANetwork*> in_net;
    for(int i = 0 ; i < in_arr.size() ; i++)
    {
        GANetwork* g = in_arr[i];
        in_net.push_back(g->GAnetwork);
    }
    population->init(in_net);
    recreate_networks();
}

void Population::recreate_networks()
{
    // empty 
    for(int i = 0; i < GAnetworks.size() ; i++)
    {
        GANetwork *g = GAnetworks[i];
        g->delete_network_on_destroy = false;
        g->free();
    }

    GAnetworks = Array();

    // creating
    for(int i = 0; i < population->networks->size() ; i++)
    {
        GANetwork* GAnet = GANetwork::_new();
        GAnet->GAnetwork = population->networks->at(i);
        GAnet->network = population->networks->at(i);
        GAnet->init_godot_layer();
        GAnetworks.append(GAnet);
    }
}


Array Population::get_networks()
{
    return GAnetworks;
}

void Population::randomize()
{
    population->randomize();
}

void Population::epoch()
{
    population->epoch();
    recreate_networks();
}

double Population::get_crossover_rate()
{
    return population->cross_over_rate;
}
void Population::set_crossover_rate(double d)
{
    population->cross_over_rate = d;
}

double Population::get_mutation_rate()
{
    return population->mutation_rate;
}
void Population::set_mutation_rate(double d)
{
    population->mutation_rate = d;
}

double Population::get_mutation_power()
{
    return population->mutation_power;
}
void Population::set_mutation_power(double d)
{
    population->mutation_power = d;
}

double Population::get_keep_best_rate()
{
    return population->keep_best_rate;
}
void Population::set_keep_best_rate(double d)
{
    population->keep_best_rate = d;
}

double Population::get_kill_worse_rate()
{
    return population->kill_worse_rate;
}
void Population::set_kill_worse_rate(double d)
{
    population->kill_worse_rate = d;
}

double Population::get_max_fitness()
{
    return population->max_fitness;
}
void Population::set_max_fitness(double d)
{
    // Do nothing, Cant change this
}

double Population::get_mean_fitness()
{
    return population->mean_fitness;
}
void Population::set_mean_fitness(double)
{
    // Do nothing, Cant change this
}

int Population::get_size()
{
    return population->size;
}
void Population::set_size(int i)
{
    population->size = i;
}

int Population::get_generation()
{
    return population->generation;
}

void Population::set_generation(int i)
{
    population->generation = i;
}

Array Population::get_bests()
{
    Nmap ntop;
    Array atop;
    for(int i=0 ; i < GAnetworks.size() ; i++)
    {
        GANetwork* net = GAnetworks[i];
        ntop.insert( std::pair<double, GANetwork*>(net->get_fitness(), net ) );
    }

    for(auto net : ntop)
    {
        atop.append(net.second);
    }
    return atop;
}