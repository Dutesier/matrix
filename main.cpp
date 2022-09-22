#include <iostream>
#include "matrix.hpp"


int main()
{
    Matrix<int> mat(2, 2);
    mat[1][1] = 42;
    std::cout << mat[1][1] << std::endl; 


    return 0;
}
