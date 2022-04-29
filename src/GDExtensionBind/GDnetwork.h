#ifndef _G_GDNETWORK
#define _G_GDNETWORK

#include <godot_cpp/godot.hpp>

#include "../GD/GDnetwork.h"
#include "GDLayer.h"
#include "network.h"



namespace godot
{

class GDNetwork : public Network
{
    GDCLASS(GDNetwork , Network)

protected:
	static void _bind_methods();

public:
    NN::GDNetwork *gdnetwork = nullptr;
    GDNetwork();
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