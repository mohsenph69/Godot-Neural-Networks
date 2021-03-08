#include "GD/GDnetwork.h"

using namespace NN;

int main()
{
    int num_run = 100000;
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
    GDNetwork net;
    net.add_layer(2); // first layers is input which is two
    net.add_layer(2); //hidden layer
    net.add_layer(1); // last layer output layer
    net.init(); // initilize network very important
    net.blr = 0.06;
    net.wlr = 0.1;

    // Running the network
    int counter = 1;
    for(int i = 0 ; i < num_run; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            Col out = net.train(input[j] , target[j]);
            std::cout << counter <<" target=" << target[j](0, 0) << ", output=" << out(0,0) << std::endl;
            counter++;

        }
    }
    return 0;
}