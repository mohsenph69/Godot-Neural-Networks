#ifndef _G_POPULATION
#define _G_POPULATION

#include "GA/population.h"
#include "Godot.hpp"
#include "GDNATIVEbind/GAnetwork.h"

namespace godot
{

typedef std::multimap<double, godot::GANetwork*, std::greater<double> > Nmap;


class Population : public Object
{
    GODOT_CLASS(Population , Object)

    public:
    NN::Population *population;
    Array GAnetworks; // contain godot GANetworks objects
    static void _register_methods();
    void _init();
    Population();
    ~Population();
    void init(GANetwork*);
    void arr_init(Array);
    void recreate_networks();

    Array get_networks();
    
    void randomize();

    void epoch();

    double get_crossover_rate();
    void set_crossover_rate(double);

    double get_mutation_rate();
    void set_mutation_rate(double);

    double get_mutation_power();
    void set_mutation_power(double);

    double get_keep_best_rate();
    void set_keep_best_rate(double);

    double get_kill_worse_rate();
    void set_kill_worse_rate(double);

    double get_max_fitness();
    void set_max_fitness(double);

    double get_mean_fitness();
    void set_mean_fitness(double);

    int get_size();
    void set_size(int);

    int get_generation();
    void set_generation(int);

    Array get_bests();
};


}

#endif