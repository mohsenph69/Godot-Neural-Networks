#ifndef _LAYER
#define _LAYER

#include "core/header.h"
#include "functions.h"
#include <vector>

namespace NN{

class Layer
{
    public:
    Func activation_functions;
    Layer(int size);
    Layer();
    virtual void init_size(int size);
    virtual ~Layer();
    Layer* prev_layer;
    Matrix weights;
    Col values;
    Col biases;
    //methods
    void init(); // Should be called after Network is set and prev_layer is set to resize weights matrix
    void init_no_random(); 
    void randomize_weights(); // Obviouse from its name
    void randomize_biases(); // Obviouse from its name
    int size(); // Return Size
    void run(); // Run and calculates values
    void print(std::stringstream &st);
    void scan(std::stringstream &st);
    void scan_weights(std::stringstream &st, std::vector<std::vector<double>> &v);
    void scan_biases(std::stringstream &st, std::vector<double> &v);

}; // end of class
} // end of namespace


#endif