#include "GDExtensionBind/layer.h"

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

Layer::Layer()
{
}

Layer::~Layer()
{
    if(destroy_layer)
    {
        if(layer)
            delete layer;
    }
}

void Layer::_bind_methods()
{   

    ClassDB::bind_method(D_METHOD("_init"), &Layer::_init);

    ClassDB::bind_method(D_METHOD("randomize_weights"), &Layer::randomize_weights);
    ClassDB::bind_method(D_METHOD("randomize_biases"), &Layer::randomize_biases);
    ClassDB::bind_method(D_METHOD("size"), &Layer::size);

    ClassDB::bind_method(D_METHOD("get_weights"), &Layer::get_weights);
	ClassDB::bind_method(D_METHOD("set_weights", "weights_array"), &Layer::set_weights);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY,"weights"), "set_weights", "get_weights");

    ClassDB::bind_method(D_METHOD("get_values"), &Layer::get_values);
	ClassDB::bind_method(D_METHOD("set_values", "values_array"), &Layer::set_values);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY,"values"), "set_values", "get_values");

    ClassDB::bind_method(D_METHOD("get_biases"), &Layer::get_biases);
	ClassDB::bind_method(D_METHOD("set_biases", "biases_array"), &Layer::set_biases);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY,"biases"), "set_biases", "get_biases");


}

void Layer::_init()
{
    layer = new NN::Layer(4);
}

Array Layer::get_weights()
{

    Array arr;
    if(layer){   
        arr = func::matrix2array(layer->weights);
    }
    return arr;
}

void Layer::set_weights(Array weights_array)
{
    if(layer)
        layer->weights = func::array2matrix(weights_array);
}

Array Layer::get_values()
{   
    if(layer){
        return func::col2array(layer->values);
    }
    else{
        Array arr;
        return arr;
    }
}

void Layer::set_values(Array values_array)
{
    if(layer)
        layer->values = func::array2col(values_array);
}

Array Layer::get_biases()
{
    if(layer){
        return func::col2array(layer->biases);
    }
    else{
        Array arr;
        return arr;
    }
}
void Layer::set_biases(Array biases_array)
{
    if(layer)
        layer->biases = func::array2col(biases_array);
}

void Layer::randomize_weights()
{
    if(layer)
        layer->randomize_weights();
}

void Layer::randomize_biases()
{
    if(layer)
        layer->randomize_biases();
}

int Layer::size()
{
    if(layer){
        return layer->size();
    }
    return 0;
}