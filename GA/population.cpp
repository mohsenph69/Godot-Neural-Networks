#include "GA/population.h"
#include "unordered_set"
#include <cmath>

using namespace NN;


Population::Population()
{
    networks = new std::vector<GANetwork*>();
}


void Population::init(GANetwork* n)
{

    networks->push_back(n->clone());
    for(int i=1 ; i < size ; i++)
    {
        GANetwork *new_net = n->clone();
        new_net->mutate(mutation_rate, mutation_power);
        networks->push_back(new_net);
    }
}

void Population::init(std::vector<GANetwork*> in_networks)
{
    for(int i=0 ; i < in_networks.size() ; i++)
    {
        networks->push_back(in_networks.at(i)->clone());
    }
    double original_keep_best_rate = keep_best_rate;
    double original_kill_worse_rate = kill_worse_rate;
    keep_best_rate = 1.0;
    kill_worse_rate = 0.0;
    epoch();
    keep_best_rate = original_keep_best_rate;
    kill_worse_rate = original_kill_worse_rate;
}


void Population::randomize()
{
    for(int i=0; i < networks->size() ; i++)
    {
        networks->at(i)->randomize_weights();
        networks->at(i)->randomize_biases();
    }
}

Nmap Population::get_bests()
{
    Nmap best;
    for(int i=0; i< networks->size() ; i++)
    {
        best.insert( std::pair<double, GANetwork*>(networks->at(i)->fitness, networks->at(i)) );
    }
    return best;
}

rNmap Population::get_worse()
{
    rNmap worse;
    for(int i=0; i< networks->size() ; i++)
    {
        worse.insert( std::pair<double, GANetwork*>(networks->at(i)->fitness, networks->at(i)) );
    }
    return worse;
}


void Population::set_mark_for_kill()
{
    int kill_num = 0;
    int remain_num;
    if(networks->size() > 2)
    {
        kill_num = networks->size()*kill_worse_rate;
        remain_num = networks->size() - kill_num;
        if(remain_num < 2)
        {
            kill_num = networks->size() - 2;
        }
    }

    rNmap worses = get_worse();
    int kill_index = 0;
    for(auto w : worses)
    {
        if(kill_index < kill_num)
        {
            w.second->mark_for_kill = true;
            kill_index++;
        }else
        {
            break;
        }
    }
}

void Population::set_mean_sum_fitness()
{
    double sum = 0;
    for(int i =0 ; i < networks->size() ; i++)
    {
        if(!networks->at(i)->mark_for_kill)
        {
            sum += networks->at(i)->fitness;
        }
    }
    sum_fitness = sum;
    mean_fitness = sum/networks->size();
}

void Population::set_max_fitness()
{
    double m;
    m = networks->at(0)->fitness;

    for(int i = 1 ; i < networks->size() ; i++)
    {
        if(m < networks->at(i)->fitness)
        {
            m = networks->at(i)->fitness;
        }
    }
    max_fitness = m;
}

void Population::set_normalized_fitness()
{
    if(sum_fitness != 0) {
        for(int i =0 ; i < networks->size() ; i++)
        {
            if(!networks->at(i)->mark_for_kill)
            {
                networks->at(i)->normalized_fitness = networks->at(i)->fitness / sum_fitness;
            } else
            {
                networks->at(i)->normalized_fitness = 0;
            }
        }
    } else
    {
        for(int i =0 ; i < networks->size() ; i++)
        {
            if(!networks->at(i)->mark_for_kill)
            {
                networks->at(i)->normalized_fitness = 1.0/double(networks->size());
            } else 
            {
                networks->at(i)->normalized_fitness = 0;
            }
        }  
    }
}

void Population::epoch_init()
{
    if(!is_epoch_init_set && networks->size() >= 1)
    {
        set_mark_for_kill();
        set_mean_sum_fitness();
        set_max_fitness();
        set_normalized_fitness();
        is_epoch_init_set = true;
    }
}

GANetwork* Population::pick_random()
{
    int index = func::randomi(0, networks->size() - 1);
    return networks->at(index);
}

GANetwork* Population::pick_one()
{
    double top = func::random();
    double r = func::random();
    GANetwork * select;
    int index;
    if(top < 0.5)
    {
        index = 0;
        while (index != networks->size())
        {
            r -= networks->at(index)->normalized_fitness;
            if(r<0)
            {
                select = networks->at(index);
                break;
            }
            index++;
        }
    } else
    {
        index = networks->size() - 1;
        while (index >= 0)
        {
            r -= networks->at(index)->normalized_fitness;
            if(r<0)
            {
                select = networks->at(index);
                break;
            }
            index--;
        }
    }
    return select;
}




void Population::epoch()
{
    epoch_init();
    if(networks->size() == 0)
    {
        PRINT_ERR("Non network is inside in population")
        return;
    }

    // creating next generation networks
    std::vector<GANetwork*> *new_networks = new std::vector<GANetwork*>();


    // keeping the best networks
    int number_of_bests = networks->size() * keep_best_rate;
    // Keep track of the best that we added for next generation because we don't want to delete them
    std::unordered_set<unsigned int> added_bests; 

    //std::cout << "number of bests " << number_of_bests << std::endl;
    Nmap bests = get_bests();
    int best_index = 0;
    for (auto top : bests)
    {
        if(best_index < number_of_bests)
        {
            if(!top.second->mark_for_kill)
            {
                top.second->age++;
                new_networks->push_back(top.second);
                added_bests.insert(top.second->id);
                best_index++;
            }
        } else
        {
            break;
        }
    }

    // we need at least two network for next steps
    if(networks->size() == 1)
    {
        GANetwork *nn = networks->at(0)->clone();
        nn->mutate(mutation_rate , mutation_power);
        networks->push_back(nn);
    }

    // Crossover and creating new babies and mutating them
    GANetwork* parentA;
    GANetwork* parentB;
    GANetwork* baybe;
    int pick_index=0;
    int nullptr_index=0;
    while (new_networks->size() < size)
    {
        parentA = pick_one();
        parentB = pick_one();
        if(parentA == nullptr || parentB == nullptr)
        {
            if(nullptr_index > 100)
            {
                PRINT_ERR("Can not pick from networks pool");
                return;
            }
            continue;
        }
        // Check if parentA or parentB are same
        while (parentA->id == parentB->id)
        {
            if(pick_index < 20)
            {
                parentB = pick_one();
                pick_index++;
            } else if(pick_index < 50)
            {
                parentB = pick_random();
                pick_index++;
                break;
            }
        }
        // now time to create new baybe
        double parentA_win;
        if(parentB->fitness == 0) parentA_win = 0.99;
        else if(parentA->fitness == 0) parentA_win = 0.01;
        else parentA_win = parentA->fitness / parentB->fitness;

        if(func::random() < cross_over_rate)
        {
            baybe = parentA->crossover(parentB);
        } else
        {
            baybe = parentA->clone();
        }

        // mutation
        baybe->mutate(mutation_rate , mutation_power);

        new_networks->push_back(baybe);

        pick_index = 0;
    }
    // baybe creation completed

    // Deleting all network that we are not going to use
    for(auto n : *networks)
    {
        unsigned int id = n->id;
        if(added_bests.find(id) == added_bests.end() ) // except those added to remain for next generation
        {
            //std::cout << "deleting network " << n->id <<std::endl;
            GANetwork *nd = n;
            delete nd;
        } else
        {
            n->fitness = 0;
            n->normalized_fitness = 0;
        }
    }
    delete networks;
    networks = new_networks;
    generation++;
    is_epoch_init_set = false;
}