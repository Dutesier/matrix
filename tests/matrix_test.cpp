#include <gtest/gtest.h>
#include "matrix.hpp"

TEST(MatrixTests, TestProductSizeCorrect) {
    EXPECT_EQ(MatrixProductSize(2, 4, 4, 3), "2 by 3");
}

TEST(MatrixTests, TestProductSizeImpossible) {
    EXPECT_EQ(MatrixProductSize(2, 4, 3, 3), "No product possible");
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}