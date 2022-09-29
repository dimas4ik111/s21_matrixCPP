#include <iostream>
#include "s21_matrix.h"

int main() {
    S21Matrix m1(1, 1);
    S21Matrix m2(1, 1);
    m1.set_val_matrix(0, 0, 123.456);
    m2.set_val_matrix(0, 0, 123.456);
    PRINT m1.get_val_matrix(0, 0) << LLL;
    PRINT m1.get_val_matrix(0, 0) << LLL;
    PRINT m1.EqMatrix(m2) << LLL;
}
