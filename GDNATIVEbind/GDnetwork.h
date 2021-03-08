#ifndef _G_GDNETWORK
#define _G_GDNETWORK

#include "Godot.hpp"
#include "GDNATIVEbind/network.h"
#include "GD/GDnetwork.h"
#include "GDNATIVEbind/GDLayer.h"


namespace godot
{

class GDNetwork : public Network
{
    GODOT_CLASS(GDNetwork , Network)

    public:
    NN::GDNetwork * GDnetwork;
    GDNetwork();
    static void _register_methods();
    void _init();
    void add_layer(int);
    void init();
    GDLayer* get_layer(int);

    double get_wlr();
    void set_wlr(double);

    double get_blr();
    void set_blr(double);

    Array train(Array input, Array target);

    void scan(String);
};


}

#endif