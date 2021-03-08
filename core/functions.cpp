#include <cmath>
#include "functions.h"

namespace NN
{
    namespace func 
    {
        Col sigmoid(Col input)
        {
            Col o(input.rows() , 1);
            for(unsigned i = 0 ; i < input.rows() ; i++)
            {
                o(i, 0) = 1/(1+exp( -input(i, 0) ) );
            }
            return o;
        }

        Col dsigmoid(Col input)
        {
            Col o(input.rows() , 1);
            o = 1 - input.array();
            o = o.cwiseProduct(input);
            return o;
        }
        
        Matrix vector2matrix(const std::vector<std::vector<double>> &v)
        {
            int row;
            int col;
            row = v.size();
            Matrix m;
            for(int i=0 ; i < row ; i++)
            {
                std::vector<double> row_vec = v.at(i);
                if(i==0)
                {
                    col = row_vec.size();
                    m.resize(row, col);
                }
                for(int j=0 ; j < col ; j++)
                {
                    m(i, j) = row_vec[j];
                }

            }
            return m;
        }

        Col vector2matrix(const std::vector<double> &v)
        {
            Col m(v.size() , 1);
            for(int i =0 ; i < v.size() ; i++)
            {
                m(i, 0) = v[i];
            }
            return m;
        }

        double random(double min, double max)
        {
            double r = ((double) rand() / (RAND_MAX));
            return min + r * (max - min);
        }

        double random()
        {
            return ((double) rand() / (RAND_MAX));
        }
        int randomi(int min , int max)
        {
            int r = rand()%(max - min + 1);
            r += min;
            return r;
        }
    }
}