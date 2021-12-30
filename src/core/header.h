#ifndef _TOPHEAD
#define _TOPHEAD

#include<Eigen/Core>
#include <sstream>
#include <vector>

typedef Eigen::Matrix<double, Eigen::Dynamic, 1> Col;
typedef Eigen::Matrix<double, 1, Eigen::Dynamic> Row;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> Matrix;
typedef Eigen::Index Index;


typedef Col(*Func)(Col);

#define DEBUG

#ifdef DEBUG
#include<iostream>
#define PRINT_ERR(x) std::cout << x << std::endl;
#else
#define PRINT(x)
#endif

 


#endif