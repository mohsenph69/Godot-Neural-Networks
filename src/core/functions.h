#ifndef _FUNCTIONS
#define _FUNCTIONS

#include "header.h"

namespace NN
{
    namespace func 
    {
        Col sigmoid(Col);
        Col dsigmoid(Col);
        Matrix vector2matrix(const std::vector<std::vector<double>> &v);
        Col vector2matrix(const std::vector<double> &v);
        double random(double min , double max);
        double random();
        int randomi(int min , int max);
    }
}




#endif