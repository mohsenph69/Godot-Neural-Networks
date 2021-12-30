#ifndef _GANETWORK
#define _GANETWORK

#include "GA/GAlayer.h"
#include "core/network.h"


namespace NN
{

class GANetwork : public Network
{
    protected:
    std::vector<GALayer*> GAlayers;

    public:
    // charachters
    double fitness = 0;
    double normalized_fitness = 0;
    int age = 0;
    bool mark_for_kill = false;
    // overloaded methods
    void add_layer(int size);
    void add_layer();
    void add_layer(GALayer*);
    GANetwork *clone_all();
    GANetwork *clone();
    std::vector<GALayer* > *get_layers();
    // Genitc algortim stuff
    void mutate(double rate, double power);
    GANetwork * crossover(GANetwork *other);
};

}

#endif