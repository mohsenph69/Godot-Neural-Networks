#ifndef _POPULATION
#define _POPULATION

#include "GA/GAnetwork.h"
#include <map>



namespace NN
{

typedef std::multimap<double, NN::GANetwork*, std::greater<double> > Nmap;
typedef std::multimap<double, NN::GANetwork* , std::greater<double> >::iterator Nmapit;
typedef std::multimap<double, NN::GANetwork*> rNmap;
typedef std::multimap<double, NN::GANetwork* >::iterator rNmapit;


class Population
{
    private:
    bool is_epoch_init_set = false;
    void set_mark_for_kill();
    void set_mean_sum_fitness();
    void set_max_fitness();
    void set_normalized_fitness();

    public:
    int generation = 0;
    GANetwork* orginal_network;
    std::vector<GANetwork*> *networks;
    double cross_over_rate = 0.2;
    double mutation_rate = 0.2;
    double mutation_power = 20.0;
    double keep_best_rate = 0.01;
    double kill_worse_rate = 0.9;
    double max_fitness = 0;
    double mean_fitness = 0;
    double sum_fitness=0;
    int size = 10;
    Population();
    void init(GANetwork*);
    void init(std::vector<GANetwork*>);
    void randomize();
    Nmap get_bests();
    rNmap get_worse();
    void epoch_init();
    GANetwork* pick_random(); // return a random network
    GANetwork* pick_one(); // return a random network which networks with heigher fitness are more likely to be picked
    void epoch();


};

}


#endif