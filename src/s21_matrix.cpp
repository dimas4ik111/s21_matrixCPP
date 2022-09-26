#include "s21_matrix.h"

S21Matrix::S21Matrix() {
    cols_ = 1;
    rows_ = 1;
    *matrix_ = new double(cols_);
}

S21Matrix::~S21Matrix() {
    delete[] matrix_;
}

S21Matrix::S21Matrix(int rows, int cols) {
    rows_ = rows;
    cols_ = cols;
    matrix_ = new double *[rows];
    for (int i = 0; i < rows; i++) {
        matrix_[i] = new double [cols];
    }
}

S21Matrix::S21Matrix(const S21Matrix& other) {
    // other.rows_ = rows_;
    // other.cols_ = cols_;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            other.matrix_[i][j] = matrix_[i][j];
        }
    }
}

int S21Matrix::get_row() {
    return rows_;
}

int S21Matrix::get_col() {
    return cols_;
}

void S21Matrix::set_val_matrix(int i, int j, double num) {
    if (i < 0 || j < 0 || i > rows_ || j > cols_) {
        return;
    }
    matrix_[i][j] = num;
}

double S21Matrix::get_val_matrix(int i, int j) {
    return matrix_[i][j];
}

// bool S21Matrix::EqMatrix(const S21Matrix& other) {
//     int result = false;
//     if (rows_ == other.rows_ && cols_ == other.cols_) {
//         result = true;
//         for (int i = 0; i < rows_; i++) {
//             for (int j = cols_; j < cols_; j++) {
//                 if (std::fabs((*this)[i][j] - other[i][j]) > 1e-7) {
//                     result = false;
//                     break;
//                 }
//             }
//             if (!result) {
//                 break;
//             }
//         }
//     }
//     return result;
// }
