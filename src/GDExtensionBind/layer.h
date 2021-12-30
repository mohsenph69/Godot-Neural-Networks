#ifndef LAYER_CLASS_H
#define LAYER_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include "GDExtensionBind/function.h"
#include "core/layer.h"


#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot
{

class Layer : public Node
{
    GDCLASS(Layer, Node)

protected:
	static void _bind_methods();

public:
    NN::Layer* layer = nullptr;
    bool destroy_layer = true;
    Layer();
    ~Layer();
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