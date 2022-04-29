#ifndef _NETWORK
#define _NETWORK

#include <vector>
#include "core/layer.h"

namespace NN{


enum activation {sigmoid = 1 };

class Network
{
    public:
    std::vector<Layer*> layers;
    static unsigned int last_id;

    public:
    unsigned int id;
    activation activation_function = activation::sigmoid;
    Network();
    virtual ~Network();
    void set_activation_function(activation);

    virtual void add_layer(int size);
    virtual void add_layer();
    std::vector<Layer*> * get_layers();
    void init();
    virtual void set_prev_layers();
    int size();
    void randomize_weights();
    void randomize_biases();
    Layer* input_layer();
    Layer* output_layer();
    Col input();
    Col output();
    Col feedforward(Col input);
    void print(std::stringstream &st);
    bool scan(std::stringstream &st);

}; // end of class
} // end of namespace


#endif