#ifndef _G_GDLAYER
#define _G_GDLAYER



// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include "layer.h"
#include "../GD/GDlayer.h"


#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/binder_common.hpp>


namespace godot
{

class GDLayer : public Layer
{
    GDCLASS(GDLayer , Layer)

protected:
	static void _bind_methods();

public:
    NN::GDLayer* GDlayer = nullptr;


    Array get_errors();
    void set_errors(Array);

    Array get_dw();
    void set_dw(Array);
};

}


#endif