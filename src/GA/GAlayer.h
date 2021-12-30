#ifndef _GALAYER
#define _GALAYER

#include "core/layer.h"

namespace NN
{

class GALayer : public Layer
{
    public:
    GALayer(int);
    GALayer();
    GALayer* clone();
    void mutate(double rate, double power);
    GALayer * uniform_crossover(double win, GALayer *other);
    GALayer * crossover(double first_section, GALayer *other);
};




}
#endif