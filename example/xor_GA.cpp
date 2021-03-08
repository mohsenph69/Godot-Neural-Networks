#include "GA/GAnetwork.h"
#include "GA/population.h"

using namespace NN;



double calculate_error(GANetwork* n, Col input[], Col target[])
{  
    double error = 0.1;
    for(int j = 0; j < 4; j++)
    {
        Col out = n->feedforward(input[j]);
        error += abs(out(0,0) - target[j](0,0)  );
    }
    error = pow(error , 10);
    return error;
}



int main()
{
    int num_run = 100;
    int population_size = 50;
    // Setting all input values
    Col input[4];
    input[0].resize(2, 1);
    input[1].resize(2, 1);
    input[2].resize(2, 1);
    input[3].resize(2, 1);
    // There are 4 possible values for XOR problem
    input[0] << 0 ,0;
    input[1] << 0 ,1;
    input[2] << 1 ,1;
    input[3] << 1 ,0;
    // Setting the target
    Col target[4];
    target[0].resize(1, 1);
    target[1].resize(1, 1);
    target[2].resize(1, 1);
    target[3].resize(1, 1);
    // These are solution to the prevouse input
    target[0] << 0;
    target[1] << 1;
    target[2] << 0;
    target[3] << 1;
    // Complete setting the traning data

    // setting up network for traning
    GANetwork net;
    net.add_layer(2); // first layers is input which is two
    net.add_layer(2); //hidden layer
    net.add_layer(1); // last layer output layer
    net.init(); // initilize network very important

    // Creating the population 
    Population pop;
    pop.size = population_size;
    pop.cross_over_rate = 0.5;
    pop.keep_best_rate = 0.01;
    pop.mutation_power = 0.3;
    pop.mutation_power = 30.0;
    pop.kill_worse_rate = 0.0;
    pop.init(&net);
    pop.randomize();
    // Running the network
    for(int i = 0 ; i < num_run; i++)
    {
        // Calculating fitness for each network
        for(int j = 0 ; j < pop.networks->size() ; j++)
        {
            GANetwork* curnet = pop.networks->at(j);
            double error = calculate_error(curnet, input, target);
            double fitness = 1.0/error;
            curnet->fitness = fitness;
        }
        pop.epoch();
        std::cout << "generation " << pop.generation << " mean fitness " << pop.mean_fitness << " max fitness " << pop.max_fitness <<  std::endl;
        for(int i = 0 ; i < pop.networks->size() ; i++)
        {
            //std::stringstream st;
            //pop.networks->at(i)->print(st);
            //std::cout << "network fitness " << pop.networks->at(i)->fitness << std::endl;
        }
    }
    return 0;
}



