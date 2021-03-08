#include <Godot.hpp>
#include "GDNATIVEbind/layer.h"
#include "GDNATIVEbind/network.h"
#include "GDNATIVEbind/GDnetwork.h"
#include "GDNATIVEbind/GDLayer.h"
#include "GDNATIVEbind/GAnetwork.h"
#include "GDNATIVEbind/population.h"

extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);

	godot::register_tool_class<godot::Layer>();
	godot::register_tool_class<godot::Network>();
	godot::register_tool_class<godot::GDNetwork>();
	godot::register_tool_class<godot::GDLayer>();
	godot::register_tool_class<godot::GANetwork>();
	godot::register_tool_class<godot::Population>();
}
