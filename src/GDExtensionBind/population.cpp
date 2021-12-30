#include "population.h"


using namespace godot;

void Population::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("init", "g"), &Population::init);
    ClassDB::bind_method(D_METHOD("arr_init","in_arr"), &Population::arr_init);
    ClassDB::bind_method(D_METHOD("get_networks"), &Population::get_networks);
    ClassDB::bind_method(D_METHOD("randomize"), &Population::randomize);
    ClassDB::bind_method(D_METHOD("epoch"), &Population::epoch);
    ClassDB::bind_method(D_METHOD("get_bests"), &Population::get_bests);

    ClassDB::bind_method(D_METHOD("get_crossover_rate"), &Population::get_crossover_rate);
	ClassDB::bind_method(D_METHOD("set_crossover_rate", "d"), &Population::set_crossover_rate);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"crossover_rate"), "set_crossover_rate", "get_crossover_rate");

    ClassDB::bind_method(D_METHOD("get_mutation_rate"), &Population::get_mutation_rate);
	ClassDB::bind_method(D_METHOD("set_mutation_rate", "d"), &Population::set_mutation_rate);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"mutation_rate"), "set_mutation_rate", "get_mutation_rate");

    ClassDB::bind_method(D_METHOD("get_mutation_power"), &Population::get_mutation_power);
	ClassDB::bind_method(D_METHOD("set_mutation_power", "d"), &Population::set_mutation_power);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"mutation_power"), "set_mutation_power", "get_mutation_power");

    ClassDB::bind_method(D_METHOD("get_keep_best_rate"), &Population::get_keep_best_rate);
	ClassDB::bind_method(D_METHOD("set_keep_best_rate", "d"), &Population::set_keep_best_rate);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"keep_best_rate"), "set_keep_best_rate", "get_keep_best_rate");

    ClassDB::bind_method(D_METHOD("get_kill_worse_rate"), &Population::get_kill_worse_rate);
	ClassDB::bind_method(D_METHOD("set_kill_worse_rate", "d"), &Population::set_kill_worse_rate);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"kill_worse_rate"), "set_kill_worse_rate", "get_kill_worse_rate");

    ClassDB::bind_method(D_METHOD("get_max_fitness"), &Population::get_max_fitness);
	ClassDB::bind_method(D_METHOD("set_max_fitness", "d"), &Population::set_max_fitness);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"max_fitness"), "set_max_fitness", "get_max_fitness");

    ClassDB::bind_method(D_METHOD("get_mean_fitness"), &Population::get_mean_fitness);
	ClassDB::bind_method(D_METHOD("set_mean_fitness", "d"), &Population::set_mean_fitness);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"mean_fitness"), "set_mean_fitness", "get_mean_fitness");

    ClassDB::bind_method(D_METHOD("get_size"), &Population::get_size);
	ClassDB::bind_method(D_METHOD("set_size", "i"), &Population::set_size);
	ADD_PROPERTY(PropertyInfo(Variant::INT,"size"), "set_size", "get_size");

    ClassDB::bind_method(D_METHOD("get_generation"), &Population::get_generation);
	ClassDB::bind_method(D_METHOD("set_generation", "i"), &Population::set_generation);
	ADD_PROPERTY(PropertyInfo(Variant::INT,"generation"), "set_generation", "get_generation");
}

void Population::_init()
{

}

Population::Population()
{
    population = new NN::Population();
}

Population::~Population()
{
    delete population;
}

void Population::init(Variant g)
{
    GANetwork* gn = Object::cast_to<GANetwork>(g);
    population->init(gn->GAnetwork);
    recreate_networks();
}

void Population::arr_init(Array in_arr)
{
    std::vector<NN::GANetwork*> in_net;
    for(int i = 0 ; i < in_arr.size() ; i++)
    {
        GANetwork* g = Object::cast_to<GANetwork>(in_arr[i]);
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
        GANetwork *g = Object::cast_to<GANetwork>(GAnetworks[i]);
        g->delete_network_on_destroy = false;
        g->queue_free();
    }

    GAnetworks = Array();

    // creating
    for(int i = 0; i < population->networks->size() ; i++)
    {
        GANetwork* GAnet = memnew(GANetwork);
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
        GANetwork* net = Object::cast_to<GANetwork>(GAnetworks[i]);
        ntop.insert( std::pair<double, GANetwork*>(net->get_fitness(), net ) );
    }

    for(auto net : ntop)
    {
        atop.append(net.second);
    }
    return atop;
}