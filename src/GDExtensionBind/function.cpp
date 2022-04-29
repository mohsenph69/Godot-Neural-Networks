#include "GDExtensionBind/function.h"

namespace godot
{
    namespace func
    {
        Array matrix2array(Matrix m)
        {
            Array arr;
            for(int i = 0 ; i < m.rows() ; i++)
            {
                Array row;
                for(int j =0 ; j < m.cols() ; j++)
                {
                    row.append(m(i,j));
                }
                arr.push_back(row);
            }
            return arr;
        }
        Matrix array2matrix(Array a)
        {
            int rows = 0;
            int cols = 0;
            rows = a.size();
            Array first = a[0];
            cols = first.size();
            Matrix m(rows, cols);
            // Checking the array
            for(int i = 0 ; i < rows ; i++)
            {
                Array ar = a[i];
                for(int j = 0 ; j < cols ; j++)
                {
                    m(i,j) = ar[j];
                }
            }
            return m;
        }
        Col array2col(Array a)
        {
            if(a.size() == 0)
            {
                PRINT_ERR("Not valid array");
                return Col();
            }
            Col c(a.size() , 1);
            for(int i=0; i < a.size() ; i++)
            {
                c(i, 0) = a[i];
            }
            return c;
        }
        Array col2array(Col c)
        {
            Array a;
            for(int i=0; i < c.rows() ; i++)
            {
                a.append(c(i,0));
            }
            return a;
        }
    }
}