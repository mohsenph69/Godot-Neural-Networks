#include <godot_cpp/core/method_ptrcall.hpp>
#include "core/header.h"




namespace godot
{
    namespace func
    {
        Array matrix2array(Matrix);
        Matrix array2matrix(Array);

        Col array2col(Array);
        Array col2array(Col);
    }
}