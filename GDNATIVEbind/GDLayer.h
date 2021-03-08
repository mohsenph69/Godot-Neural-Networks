#ifndef _G_GDLAYER
#define _G_GDLAYER

#include "GDNATIVEbind/layer.h"
#include "GD/GDlayer.h"


namespace godot
{

class GDLayer : public Layer
{
    GODOT_CLASS(GDLayer , Layer)
    public:
    NN::GDLayer* GDlayer;
    static void _register_methods();
    void _init();

    Array get_errors();
    void set_errors(Array);

    Array get_dw();
    void set_dw(Array);
};

}


#endif