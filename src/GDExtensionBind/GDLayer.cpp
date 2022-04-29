#include "GDExtensionBind/GDLayer.h"
#include "GDExtensionBind/function.h"

using namespace godot;

void GDLayer::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_errors"), &GDLayer::set_errors);
	ClassDB::bind_method(D_METHOD("set_errors", "error_array"), &GDLayer::set_errors);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY,"errors"), "set_errors", "get_errors");


    ClassDB::bind_method(D_METHOD("get_dw"), &GDLayer::get_dw);
	ClassDB::bind_method(D_METHOD("set_dw", "dw_array"), &GDLayer::set_dw);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY,"dw"), "set_dw", "get_dw");
}



Array GDLayer::get_errors()
{
    if(!GDlayer){
        Array arr;
        return arr;
    }

    return func::col2array(GDlayer->errors);
}
void GDLayer::set_errors(Array a)
{   
    if(GDlayer)
        GDlayer->errors = func::array2col(a);
}

Array GDLayer::get_dw()
{   
    if(!GDlayer){
        Array arr;
        return arr;
    }

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
    if(GDlayer)
        GDlayer->dw = func::array2matrix(a);
}