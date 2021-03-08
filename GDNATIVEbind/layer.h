#ifndef _G_LAYER
#define _G_LAYER


#include "core/layer.h"
#include "Godot.hpp"

namespace godot
{

class Layer : public Object
{
    GODOT_CLASS(Layer , Object)

    public:
    NN::Layer* layer;
    bool destroy_layer = true;
    ~Layer();
    static void _register_methods();
    void _init();

    Array get_weights();
    void set_weights(Array);

    Array get_values();
    void set_values(Array);

    Array get_biases();
    void set_biases(Array);
    
    void randomize_weights();
    void randomize_biases();
    
    int size();



}; // end of class

} // end of namespace
#endif