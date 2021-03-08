#include "GDNATIVEbind/layer.h"
#include "GDNATIVEbind/function.h"

using namespace godot;

Layer::~Layer()
{
    if(destroy_layer)
    {
        delete layer;
    }
}

void Layer::_register_methods()
{
    register_property<Layer, Array>("weights", &Layer::set_weights, &Layer::get_weights, Array());
    register_property<Layer, Array>("values", &Layer::set_values, &Layer::get_values, Array());
    register_property<Layer, Array>("biases", &Layer::set_biases, &Layer::get_biases, Array());

    register_method("randomize_weights", &Layer::randomize_weights);
    register_method("randomize_biases", &Layer::randomize_biases);
    register_method("size" , &Layer::size);

}

void Layer::_init()
{
    layer = new NN::Layer(4);
}

Array Layer::get_weights()
{
    return func::matrix2array(layer->weights);
}

void Layer::set_weights(Array arr)
{
    layer->weights = func::array2matrix(arr);
}

Array Layer::get_values()
{
    return func::col2array(layer->values);
}

void Layer::set_values(Array arr)
{
    layer->values = func::array2col(arr);
}

Array Layer::get_biases()
{
    return func::col2array(layer->biases);
}
void Layer::set_biases(Array arr)
{
    layer->biases = func::array2col(arr);
}

void Layer::randomize_weights()
{
    layer->randomize_weights();
}

void Layer::randomize_biases()
{
    layer->randomize_biases();
}

int Layer::size()
{
    return layer->size();
}