#ifndef _GDLAYER
#define _GDLAYER

#include <core/layer.h>

namespace NN
{


class GDLayer : public Layer
{
    public:
    GDLayer* prev_GDlayer;
    GDLayer(int);
    GDLayer();
    Func d_activation_pointer;
    Col errors;
    Matrix dw; // change in weights
    void init_size(int size);
    void output_error(Col target);
    void prev_error();
    void calc_dw();
};

}


#endif