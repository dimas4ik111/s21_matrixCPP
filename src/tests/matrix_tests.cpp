#include "../lib/s21_matrix.h"
#include <gtest/gtest.h>

TEST(get_set, test1) {
    S21Matrix m1(2, 2);
    m1(1, 1) = 123.456;
    EXPECT_EQ(m1.get_col(), 2);
    EXPECT_EQ(m1.get_row(), 2);
    EXPECT_DOUBLE_EQ(m1(1, 1), 123.456);
}

int main() {
    testing::InitGoogleTest();
    if (RUN_ALL_TESTS()) {
        std::cout << "ERRORS" << std::endl;
    }
    return RUN_ALL_TESTS();
}