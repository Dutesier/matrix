#include <iostream>
#include <vector>
#include "matrix.hpp"


int main()
{
    Matrix<int> mat(2, 2);
    mat[1][1] = 42;
    std::cout << mat << std::endl; 

    Matrix<int> badMat(3, 2);
    badMat = mat;
    std::cout << badMat << std::endl;
    std::cout << mat << std::endl;
    Matrix<int> goodMat(mat);
    std::cout << goodMat << std::endl;

    Matrix<int> oneMat(2, 2);
    oneMat[0][0] = 1;
    oneMat[0][1] = 1;
    oneMat[1][0] = 1;
    oneMat[1][1] = 1;

    std::cout << mat + oneMat << std::endl;


    Matrix<int> hor(2, 3);
    hor[0][0] = 1;
    hor[0][1] = 2;
    hor[0][2] = 3;
    hor[1][0] = 4;
    hor[1][1] = 5;
    hor[1][2] = 6;

    Matrix<int> ver(3, 2);
    ver[0][0] = 10;
    ver[0][1] = 11;
    ver[1][0] = 20;
    ver[1][1] = 21;
    ver[2][0] = 30;
    ver[2][1] = 31;

    std::cout << hor * ver << std::endl;
    std::cout << ver * hor << std::endl;

    std::vector<std::vector<int>> Vec = {
        {2, 2},
        {4, 2},
        {6, 2}
    };

    Matrix<int> vec(Vec);

    std::cout << (vec * 2) * hor << std::endl;
    return 0;
}
