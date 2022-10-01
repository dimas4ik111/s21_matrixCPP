#include "../lib/s21_matrix.h"
#include <gtest/gtest.h>

// #define LLL std::endl
// #define PRINT std::cout <<

TEST(whatTest, test1) {
    EXPECT_EQ(2, 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
