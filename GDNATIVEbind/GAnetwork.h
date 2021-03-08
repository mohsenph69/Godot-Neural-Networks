#ifndef _G_GANETWORK
#define _G_GANETWORK

#include "Godot.hpp"
#include "GDNATIVEbind/network.h"
#include "GA/GAnetwork.h"


namespace godot
{

class GANetwork : public Network
{
    GODOT_CLASS(GANetwork , Network)

    public:
    NN::GANetwork* GAnetwork;
    static void _register_methods();
    void _init();
    GANetwork();

    double get_fitness();
    void set_fitness(double);

    double get_normalized_fitness();
    void set_normalized_fitness(double);

    int get_age();
    void set_age(int);

    bool get_mark_for_kill();
    void set_mark_for_kill(bool);


    void mutate(double rate, double power);
    GANetwork* crossover(GANetwork* other);

};

}


#endif