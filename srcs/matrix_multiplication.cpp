#include "matrix.hpp"

std::string MatrixProductSize(int m1rows, int m1cols, int m2rows, int m2cols){
    if (m1cols != m2rows)
        return "No product possible";
    return std::to_string(m1rows) + " by " + std::to_string(m2cols);
}