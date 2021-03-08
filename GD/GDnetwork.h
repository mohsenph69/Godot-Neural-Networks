#ifndef _GDNETWORK
#define _GDNETWORK

#include "core/network.h"
#include "GD/GDlayer.h"

namespace NN
{


class GDNetwork : public Network
{


    public:
    std::vector<GDLayer* > GDlayers;
    double wlr = 0.1; // Learning rate for weights
    double blr = 0.05; // Learning rate for biases
    void add_layer(int size);
    void add_layer();
    void set_prev_layers();
    std::vector<GDLayer* > *get_layers();
    void init();
    void set_d_activation_function(activation); // derivitive of activation function
    // Errors 
    void backprop_error(Col target);
    void backprop_dw();
    Col train(Col input, Col target);

};


}



#endif