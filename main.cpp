#include <iostream>
#include <vector>
#include "matrix.hpp"


int main()
{
    Matrix<int, 2, 2> mat;
    mat[1][1] = 42;
    std::cout << mat << std::endl; 

    Matrix<int, 3, 2> badMat;
    // YAY this gives an error because they are of different types
    //badMat = mat; 
    std::cout << badMat << std::endl;
    std::cout << mat << std::endl;
    Matrix<int, 2, 2> goodMat(mat);
    std::cout << goodMat << std::endl;

    Matrix<int, 2, 2> oneMat;
    oneMat[0][0] = 1;
    oneMat[0][1] = 1;
    oneMat[1][0] = 1;
    oneMat[1][1] = 1;

    std::cout << mat + oneMat << std::endl;


    Matrix<int, 2, 3> hor;
    hor[0][0] = 1;
    hor[0][1] = 2;
    hor[0][2] = 3;
    hor[1][0] = 4;
    hor[1][1] = 5;
    hor[1][2] = 6;

    Matrix<int, 3, 2> ver;
    ver[0][0] = 10;
    ver[0][1] = 11;
    ver[1][0] = 20;
    ver[1][1] = 21;
    ver[2][0] = 30;
    ver[2][1] = 31;

    std::cout << hor * ver << std::endl;
    std::cout << ver * hor << std::endl;

    // std::vector<std::vector<int>> Vec = {
    //     {2, 2},
    //     {4, 2},
    //     {6, 2}
    // };

    // Matrix<int, 2, 3> vec(Vec);

    std::cout << (ver * 2) * hor << std::endl;
    return 0;
}
