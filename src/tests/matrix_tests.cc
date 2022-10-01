#include "../lib/s21_matrix.h"
#include <gtest/gtest.h>

#define DEBUGER std::cout << std::endl << "DEBUG" << std::endl << std::endl;
#define PR std::cout <<
#define EN std::endl << std::endl;

TEST(get_set, t1) {
    S21Matrix m1(2, 2);
    m1(1, 1) = 123.456;
    EXPECT_EQ(m1.get_col(), 2);
    EXPECT_EQ(m1.get_row(), 2);
    EXPECT_DOUBLE_EQ(m1(1, 1), 123.456);
}

TEST(set_col, t1) {
    S21Matrix m(2, 2);
    m(1, 1) = 123.456;
    m.set_col(3);
    m(1, 2) = 999.999;
    EXPECT_EQ(m.get_col(), 3);
    EXPECT_DOUBLE_EQ(m(1, 1), 123.456);
    EXPECT_DOUBLE_EQ(m(1, 2), 999.999);
}

TEST(set_row, t1) {
    S21Matrix m1(2, 2);
    m1(1, 0) = 123.456;
    m1.set_row(3);
    m1(2, 0) = m1(1, 0);
    EXPECT_EQ(m1.get_row(), 3);
    EXPECT_EQ(m1.get_col(), 2);
    EXPECT_DOUBLE_EQ(m1(1, 0), m1(2, 0));
}

TEST(constructors, t1) {
    S21Matrix m1;
    EXPECT_EQ(m1.get_col(), 2);
    EXPECT_EQ(m1.get_row(), 2);
    
    S21Matrix m2(2, 2);
    m2(1, 1) = 123.456;
    EXPECT_EQ(m2.get_col(), 2);
    EXPECT_EQ(m2.get_row(), 2);

    S21Matrix m3(m2);
    EXPECT_EQ(m2 == m3, true);

    S21Matrix m4(std::move(m3));
    EXPECT_EQ(m3.get_col(), 0);
    EXPECT_EQ(m3.get_row(), 0);
    EXPECT_EQ(m4.get_row(), 2);
    EXPECT_EQ(m4.get_col(), 2);
    EXPECT_EQ(m4(1, 1), m2(1, 1));
}

TEST(func1, eq) {
    S21Matrix m1(123, 123);
    S21Matrix m2(m1);

    EXPECT_EQ(m1.EqMatrix(m2), true);
}

TEST(func2, summat) {
    S21Matrix m1(3, 3);
    S21Matrix m2(3, 3);

    m1(0, 0) = 1;
    m1(0, 2) = 2;
    m1(2, 0) = 3;

    m2.SumMatrix(m1);

    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 2), 2);
    EXPECT_EQ(m2(2, 0), 3);
}

TEST(func3, submat) {
    S21Matrix m1(3, 3);
    S21Matrix m2(3, 3);

    m1(0, 0) = 1;
    m1(0, 2) = 2;
    m1(2, 0) = 3;

    m2.SubMatrix(m1);

    EXPECT_EQ(m2(0, 0), -1);
    EXPECT_EQ(m2(0, 2), -2);
    EXPECT_EQ(m2(2, 0), -3);
}

TEST(func4, mulnum) {
    S21Matrix m2(3, 3);

    m2(0, 0) = 1.3;
    m2(0, 2) = 2.1;
    m2(2, 0) = 3.3;

    m2.MulNumber(0.412);

    EXPECT_EQ(m2(0, 0), 1.3 * 0.412);
    EXPECT_EQ(m2(0, 2), 2.1 * 0.412);
    EXPECT_EQ(m2(2, 0), 3.3 * 0.412);
}

TEST(func5, mulmat) {
    S21Matrix m1(2, 1);
    S21Matrix m2(1, 2);

    m1(0, 0) = 32;
    m1(1, 0) = 12;

    m2(0, 0) = 2;
    m2(0, 1) = 3;

    m1.MulMatrix(m2);

    EXPECT_DOUBLE_EQ(m1(0, 0), 32 * 2);
    EXPECT_DOUBLE_EQ(m1(1, 1), 12 * 3);
}

TEST(func6, transpose) {
    int rows = 2;
    int cols = 3;

    S21Matrix m(rows, cols);
    S21Matrix res(cols, rows);

    for (int i = 0, c = 1; i < rows; i++) {
        for (int j = 0; j < cols; j++, c++) {
            m(i, j) = c;
            res(j, i) = c;
        }
    }

    m = m.Transpose();

    ASSERT_TRUE(m == res);
}

TEST(func7, calccal) {
    S21Matrix m(3, 12);
    EXPECT_ANY_THROW(m.CalcComplements());
}

TEST(func7, calcalc) {
    int rows = 3;
    int cols = 3;

    S21Matrix given(rows, cols);
    S21Matrix expected(rows, cols);

    given(0, 0) = 1.0;
    given(0, 1) = 2.0;
    given(0, 2) = 3.0;
    given(1, 0) = 0.0;
    given(1, 1) = 4.0;
    given(1, 2) = 2.0;
    given(2, 0) = 5.0;
    given(2, 1) = 2.0;
    given(2, 2) = 1.0;

    expected(0, 0) = 0.0;
    expected(0, 1) = 10.0;
    expected(0, 2) = -20.0;
    expected(1, 0) = 4.0;
    expected(1, 1) = -14.0;
    expected(1, 2) = 8.0;
    expected(2, 0) = -8.0;
    expected(2, 1) = -2.0;
    expected(2, 2) = 4.0;

    S21Matrix res = given.CalcComplements();

    ASSERT_TRUE(res == expected);
}

int main() {
    testing::InitGoogleTest();
    if (RUN_ALL_TESTS()) {
        std::cout << "ERRORS" << std::endl;
    }
    return RUN_ALL_TESTS();
}