#include "../lib/s21_matrix_oop.h"
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
    EXPECT_DOUBLE_EQ(m2(1, 1), 123.456);

    S21Matrix m3(m2);
    EXPECT_EQ(m2.EqMatrix(m3), true);

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

TEST(func8, det) {
    S21Matrix m(5, 5);

    for (uint32_t i = 0; i < 5; i++)
        for (uint32_t j = 0; j < 5; j++)
            m(i, j) = j;

    ASSERT_NEAR(0, m.Determinant(), 1e-06);
}

TEST(func8, det1) {
    int size = 5;
    S21Matrix m(size, size);

    m(0, 1) = 6;
    m(0, 2) = -2;
    m(0, 3) = -1;
    m(0, 4) = 5;
    m(1, 3) = -9;
    m(1, 4) = -7;
    m(2, 1) = 15;
    m(2, 2) = 35;
    m(3, 1) = -1;
    m(3, 2) = -11;
    m(3, 3) = -2;
    m(3, 4) = 1;
    m(4, 0) = -2;
    m(4, 1) = -2;
    m(4, 2) = 3;
    m(4, 4) = -2;

    double res = m.Determinant();
    ASSERT_NEAR(res, 2480, 1e-6);
}

TEST(func8, det2) {
    int size = 3;
    S21Matrix m(size, size);

    m(0, 0) = 2;
    m(0, 1) = 3;
    m(0, 2) = 1;
    m(1, 0) = 7;
    m(1, 1) = 4;
    m(1, 2) = 1;
    m(2, 0) = 9;
    m(2, 1) = -2;
    m(2, 2) = 1;

    double res = m.Determinant();
    ASSERT_NEAR(res, -32, 1e-6);
}

TEST(func9, inverse) {
    int size = 3;
    S21Matrix given(size, size);
    S21Matrix expected(size, size);

    expected(0, 0) = 44300.0 / 367429.0;
    expected(0, 1) = -236300.0 / 367429.0;
    expected(0, 2) = 200360.0 / 367429.0;
    expected(1, 0) = 20600.0 / 367429.0;
    expected(1, 1) = 56000.0 / 367429.0;
    expected(1, 2) = -156483.0 / 367429.0;
    expected(2, 0) = 30900.0 / 367429.0;
    expected(2, 1) = 84000.0 / 367429.0;
    expected(2, 2) = -51010.0 / 367429.0;

    given(0, 0) = 2.8;
    given(0, 1) = 1.3;
    given(0, 2) = 7.01;
    given(1, 0) = -1.03;
    given(1, 1) = -2.3;
    given(1, 2) = 3.01;
    given(2, 0) = 0;
    given(2, 1) = -3;
    given(2, 2) = 2;

    ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(func9, iverse1) {
    int size = 3;
    S21Matrix given(size, size);
    S21Matrix expected(size, size);
    expected(0, 0) = 1.0;
    expected(0, 1) = -1.0;
    expected(0, 2) = 1.0;
    expected(1, 0) = -38.0;
    expected(1, 1) = 41.0;
    expected(1, 2) = -34.0;
    expected(2, 0) = 27.0;
    expected(2, 1) = -29.0;
    expected(2, 2) = 24.0;

    given(0, 0) = 2.0;
    given(0, 1) = 5.0;
    given(0, 2) = 7.0;
    given(1, 0) = 6.0;
    given(1, 1) = 3.0;
    given(1, 2) = 4.0;
    given(2, 0) = 5.0;
    given(2, 1) = -2.0;
    given(2, 2) = -3.0;

    ASSERT_TRUE(given.InverseMatrix() == expected);
}

TEST(method1, first) {
    S21Matrix m;
    EXPECT_EQ(m.get_col(), 2);
    EXPECT_EQ(m.get_row(), 2);
}

TEST(method2, second) {
    S21Matrix m(11, 11);
    EXPECT_EQ(m.get_col(), 11);
    EXPECT_EQ(m.get_row(), 11);
    EXPECT_EQ(m(10, 10), 0);
}

TEST(method3, third) {
    S21Matrix m1(123, 123);

    S21Matrix m2(m1);

    EXPECT_EQ(m1.get_col(), m2.get_col());
    EXPECT_EQ(m1.get_row(), m2.get_row());
}

TEST(method4, fourth) {
    S21Matrix m1(123, 123);

    S21Matrix m2(std::move(m1));

    EXPECT_EQ(m1.get_col(), 0);
    EXPECT_EQ(m1.get_row(), 0);
    EXPECT_EQ(m2.get_col(), 123);
    EXPECT_EQ(m2.get_row(), 123);
}

int main() {
    testing::InitGoogleTest();
    if (RUN_ALL_TESTS()) {
        std::cout << "ERRORS" << std::endl;
    }
    return RUN_ALL_TESTS();
}