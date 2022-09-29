#include "s21_matrix.h"

S21Matrix::S21Matrix() {
    cols_ = 1;
    rows_ = 1;
    *matrix_ = new double(cols_);
}

S21Matrix::~S21Matrix() {
    for (int i = 0; i < rows_; i++) {
        delete[] matrix_[i];
    }
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
    cols_ = other.cols_;
    rows_ = other.rows_;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            other.matrix_[i][j] = matrix_[i][j];
        }
    }
}

S21Matrix::S21Matrix(S21Matrix&& other) {
    cols_ = other.cols_;
    rows_ = other.rows_;
    matrix_ = other.matrix_;
    other.matrix_ = nullptr;
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

bool S21Matrix::EqMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ && cols_ != other.cols_) {
        return false;
    }
    int result = true;
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            if (std::fabs(this->matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
                result = false;
                break;
            }
        }
        if (!result) {
            break;
        }
    }
    return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ && cols_ != other.cols_) {
        throw "Can't sum matrix with defferents row and col";
    }

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            this->matrix_[i][j] += other.matrix_[i][j];
        }
    }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
    if (rows_ != other.rows_ && cols_ != other.cols_) {
        throw "Can't sub matrix with defferents row and col";
    }

    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            this->matrix_[i][j] -= other.matrix_[i][j];
        }
    }
}

void S21Matrix::MulNumber(const double num) {
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            this->matrix_[i][j] *= num;
        }
    }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
    if (this->cols_ != other.rows_) {
        throw "Can't mul this matrixes";
    }
    for (int i = 0; i < this->rows_; i++) {
        for (int j = 0; j < other.cols_; j++) {
            this->matrix_[i][j] *= other.matrix_[i][j];
        }
    }
}

S21Matrix S21Matrix::Transpose() {
    S21Matrix res(this->rows_, this->cols_);
    for (int i = 0; i < this->rows_; i ++) {
        for (int j = 0; j < this->cols_; j++) {
            res.matrix_[i][j] = this->matrix_[i][j];
        }
    }
    return res;
}

void S21Matrix::cofactor_matrix(double **src, double **dst, int jump_r, int jump_col, int size) {
    for (int i = 0, row = 0; row < size; row++) {
        for (int j = 0, col = 0; col < size; col++) {
            if (row != jump_r && col != jump_col) {
                dst[i][j] = src[row][col];
                j++;
                if (j == size - 1) {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

double S21Matrix::determ(double **m, int size) {
    if (size == 1)
        return m[0][0];

    double res = 0;

    // matrix_t tmp;
    S21Matrix tmp(size, size);
    // int rrr = s21_create_matrix(size, size, &tmp);

    int sing = 1;
    for (int i = 0; i < size; i++) {
        cofactor_matrix(m, tmp.matrix_, 0, i, size);
        res += sing * m[0][i] * determ(tmp.matrix_, size - 1);
        sing = -sing;
    }

    return res;
}

S21Matrix S21Matrix::help_calculator(const S21Matrix& a) {
    int row = this->rows_;
    int col = this->cols_;
    
    S21Matrix res(row, col);

    if (row == 1) {
        res(0, 0) = 1;
        return res;
    }

    S21Matrix help_struct(row, col);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cofactor_matrix(a.matrix_, help_struct.matrix_, i, j, row);
            int sign = ((i + j) % 2 == 0) ? 1 : -1;
            res(i, j) = sign * determ(help_struct.matrix_, row - 1);
        }
    }

    return res;
}

S21Matrix S21Matrix::CalcComplements() {
    if (this->rows_ != this->cols_) {
        throw "rows != cols";
    }
    return help_calculator(*this);
}

double S21Matrix::Determinant() {
    if (this->rows_ <= 0 || this->cols_ <= 0 || this->rows_ != this->cols_) {
        throw "Error size matrix";
    }

    double res = 0;

    if (this->rows_ == 1) {
        res = this->matrix_[0][0];
    } else {
        res = determ(this->matrix_, this->rows_);
    }
    return res;
}

S21Matrix S21Matrix::InverseMatrix() {
    if (this->cols_ != this->rows_) {
        throw "rows != cols";
    }

    double det = this->Determinant();
    if (det <= 1e-7) {
        throw "Error determinant";
    }
    
    S21Matrix help1 = this->CalcComplements();
    S21Matrix help2 = help1.Transpose();
    help2.MulNumber(1.0 / det);
    return ;
}

//         if (fabs(det) > 1e-7) {
//             matrix_t help1, help2;
//             s21_calc_complements(a, &help1);
//             s21_transpose(&help1, &help2);

//             s21_mult_number(&help2, 1.0 / det, c);

//             s21_remove_matrix(&help1);
//             s21_remove_matrix(&help2);
//             res = SUCCESS;
//         } else {
//             res = ERRR;
//         }
//     }
//     return res;
// }

double &S21Matrix::operator()(int row, int col) {
    if (row >= rows_ || col >= cols_)
        throw std::out_of_range("Incorrect input, index is out of range");

    return matrix_[row][col];
}
