#include "s21_matrix_oop.h"

S21Matrix::S21Matrix(): cols_(2), rows_(2) {
    matrix_ = new double*[rows_]{};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]{};
  }
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw "rows or cols < 1";
  }
  matrix_ = new double *[rows]{};
  for (int i = 0; i < rows; i++) {
    matrix_[i] = new double[cols]{0};
  }
}

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_]{};
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double [cols_]{};
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) : cols_(other.cols_), rows_(other.rows_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

int S21Matrix::get_row() { return rows_; }

int S21Matrix::get_col() { return cols_; }

void S21Matrix::set_val_matrix(int i, int j, double num) {
  if (i < 0 || j < 0 || i > rows_ || j > cols_) {
    return;
  }
  matrix_[i][j] = num;
}

double S21Matrix::get_val_matrix(int i, int j) { return matrix_[i][j]; }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::logic_error("cols1 != cols2 || rows1 != rows2");
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

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw "Can't sum matrix with defferents row and col";
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
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

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw "Can't mul this matrixes";
  }

  S21Matrix result(this->rows_, other.cols_);

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int n = 0; n < this->cols_; n++) {
        result.matrix_[i][j] = this->matrix_[i][n] * other.matrix_[n][j];
      }
    }
  }

  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      res.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return res;
}

void S21Matrix::cofactor_matrix(double **src, double **dst, int jump_r,
                                int jump_col, int size) {
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

  S21Matrix tmp(size, size);

  int sing = 1;
  for (int i = 0; i < size; i++) {
    cofactor_matrix(m, tmp.matrix_, 0, i, size);
    res += sing * m[0][i] * determ(tmp.matrix_, size - 1);
    sing = -sing;
  }

  return res;
}

S21Matrix S21Matrix::help_calculator(const S21Matrix &a) {
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
    throw std::out_of_range("rows != cols");
  }

  double det = this->Determinant();
  if (std::fabs(det) < 1e-06) {
    throw "Error determinant";
  }

  S21Matrix help1 = this->CalcComplements();
  S21Matrix help2 = help1.Transpose();
  help2.MulNumber(1.0 / det);
  return help2;
}

double &S21Matrix::operator()(int row, int col) { 
  if (row >= rows_ || col >= cols_)
    throw std::out_of_range("Incorrect input, index is out of range");

  return matrix_[row][col];
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this == &other)
    return *this;

  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }
  delete[] this->matrix_;

  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;

  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;

  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) {
    return *this;
  } 

  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;

  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double [cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }

  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw "cols != rows";
  }

  this->SumMatrix(other);

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw "cols != rows";
  }

  S21Matrix result(*this);

  result.SumMatrix(other);

  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw "cols != rows";
  }

  this->SubMatrix(other);

  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw "cols != rows";
  }

  S21Matrix result(*this);

  result.SubMatrix(other);

  return result;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw "cols first matrix != rows second matrix";
  }

  this->MulMatrix(other);

  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  this->MulNumber(num);

  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  if (this->cols_ != other.rows_) {
    throw "cols first matrix != rows second matrix";
  }

  S21Matrix result(*this);

  result.MulMatrix(other);

  return result;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix result(*this);

  result.MulNumber(num);

  return result;
}

void S21Matrix::set_row(int new_row) {
  if (new_row < 1) {
    throw "row can't be smaller that 1";
  } else if (new_row == this->rows_) {
    return;
  }

  if (new_row > this->rows_) {
    double **tmp;
    tmp = new double *[new_row];
    for (int i = 0; i < new_row; i++) {
      tmp[i] = new double[this->cols_];
    }

    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp[i][j] = this->matrix_[i][j];
      }
    }

    this->~S21Matrix();
    this->matrix_ = tmp;
  } else if (new_row < this->rows_) {
    for (int i = new_row; i < this->rows_; i++) {
      delete[] this->matrix_[i];
    }
  }
  
  this->rows_ = new_row;
}

void S21Matrix::set_col(int new_col) {
  if (new_col < 1) {
    throw std::out_of_range("col can't be smaller that 1");
  } else if (new_col == this->cols_) {
    return;
  }

  for (int i = 0; i < this->rows_; i++) {
    if (new_col > this->cols_) {
      double *tmp = new double[new_col];
      for (int j = 0; j < this->cols_; j++) {
        tmp[j] = this->matrix_[i][j];
      }
      delete[] matrix_[i];
      this->matrix_[i] = tmp;
    } else if (new_col < this->cols_) {
      double *tmp = new double[new_col];
      for (int j = 0; j < new_col; j++) {
        tmp[j] = this->matrix_[i][j];
      }
      delete[] this->matrix_[i];
      this->matrix_[i] = tmp;
    }
  }
  this->cols_ = new_col;
}

S21Matrix operator*(double num, const S21Matrix &other) {
  S21Matrix result(other);
  result.MulNumber( num);
  return result;
}

