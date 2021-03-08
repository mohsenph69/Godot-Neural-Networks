#include "GD/GDlayer.h"


using namespace NN;


GDLayer::GDLayer(int size) : Layer(size){ init_size(size); }

GDLayer::GDLayer() : Layer(){ }

void GDLayer::init_size(int size)
{
    errors.resize(size, 1);
}


void GDLayer::output_error(Col target)
{
    Col value_errors = target - values;
    Col d_out = d_activation_pointer(values);
    errors = value_errors.cwiseProduct(d_out);
}

void GDLayer::prev_error()
{
    Matrix wT = weights.transpose();
    Col values_error = wT * errors;
    Col d_pre = d_activation_pointer(prev_GDlayer->values);
    prev_GDlayer->errors = values_error.cwiseProduct(d_pre);
}


void GDLayer::calc_dw()
{
    Row pre_val = prev_GDlayer->values.transpose();
    dw = errors * pre_val;
}