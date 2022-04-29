#include "GDExtensionBind/GAnetwork.h"

using namespace godot;


void GANetwork::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_fitness"), &GANetwork::get_fitness);
	ClassDB::bind_method(D_METHOD("set_fitness", "d"), &GANetwork::set_fitness);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"fitness"), "set_fitness", "get_fitness");

    ClassDB::bind_method(D_METHOD("get_normalized_fitness"), &GANetwork::get_normalized_fitness);
	ClassDB::bind_method(D_METHOD("set_normalized_fitness", "d"), &GANetwork::set_normalized_fitness);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"normalized_fitness"), "set_normalized_fitness", "get_normalized_fitness");

    ClassDB::bind_method(D_METHOD("get_age"), &GANetwork::get_age);
	ClassDB::bind_method(D_METHOD("set_age", "i"), &GANetwork::set_age);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"age"), "set_age", "get_age");


    ClassDB::bind_method(D_METHOD("get_mark_for_kill"), &GANetwork::get_mark_for_kill);
	ClassDB::bind_method(D_METHOD("set_mark_for_kill", "b"), &GANetwork::set_mark_for_kill);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT,"mark_for_kill"), "set_mark_for_kill", "get_mark_for_kill");

    ClassDB::bind_method(D_METHOD("mutate"), &GANetwork::mutate);
	ClassDB::bind_method(D_METHOD("crossover", "GANetwork"), &GANetwork::crossover);
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

GANetwork* GANetwork::crossover(Variant other)
{
    godot::GANetwork* oth = Object::cast_to<GANetwork>(other);
    
    NN::GANetwork* new_nn_net = GAnetwork->crossover(oth->GAnetwork);
    godot::GANetwork *g = memnew(godot::GANetwork);
    g->GAnetwork = new_nn_net;
    g->network = new_nn_net;
    g->init_godot_layer();
    return g;
}