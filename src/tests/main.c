#include "../lib/s21_matrix.h"

int main() {
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
    // m = res;
    // S21Matrix m2 = m.Transpose();
    // res = res.Transpose();
    // m = m.Transpose();
}
