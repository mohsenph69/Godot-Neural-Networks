#include "GDNATIVEbind/GDLayer.h"
#include "GDNATIVEbind/function.h"

using namespace godot;

void GDLayer::_register_methods()
{
    register_property<GDLayer, Array>("errors" , &GDLayer::set_errors, &GDLayer::get_errors, Array());
    register_property<GDLayer, Array>("dw" , &GDLayer::set_dw, &GDLayer::get_dw, Array());
}
void GDLayer::_init(){}

Array GDLayer::get_errors()
{
    return func::col2array(GDlayer->errors);
}
void GDLayer::set_errors(Array a)
{
    GDlayer->errors = func::array2col(a);
}

Array GDLayer::get_dw()
{
    if(GDlayer->dw.size() != 0)
    {
        return func::matrix2array(GDlayer->dw);
    } else
    {
        Matrix m(GDlayer->weights.rows(), GDlayer->weights.cols());
        return func::matrix2array(m);
    }
}

void GDLayer::set_dw(Array a)
{
    GDlayer->dw = func::array2matrix(a);
}