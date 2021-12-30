#ifndef _G_GANETWORK
#define _G_GANETWORK

#include <godot_cpp/godot.hpp>
#include "GDExtensionBind/network.h"
#include "GA/GAnetwork.h"


namespace godot
{

class GANetwork : public Network
{
    GDCLASS(GANetwork , Network)

protected:
    static void _bind_methods();

public:
    NN::GANetwork* GAnetwork = nullptr;
    
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
    GANetwork* crossover(Variant other);

};

}


#endif