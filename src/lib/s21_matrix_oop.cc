#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  cols_ = 2;
  rows_ = 2;
  create_matrix(*this);
}

S21Matrix::~S21Matrix() { free_matrix(*this); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows < 1 || cols < 1) {
    throw "rows or cols < 1";
  }
  create_matrix(*this);
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  copy_cicle(*this, other);
}

S21Matrix::S21Matrix(S21Matrix &&other) : matrix_(other.matrix_) {
  cols_ = other.cols_;
  rows_ = other.rows_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::create_matrix(S21Matrix &m) {
  m.matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    m.matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::free_matrix(S21Matrix &m) {
  for (int i = 0; i < m.rows_; i++) {
    delete[] m.matrix_[i];
  }
  delete[] m.matrix_;
}

void S21Matrix::copy_cicle(S21Matrix &m, const S21Matrix &other) {
  create_matrix(m);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      m.matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

int S21Matrix::get_row() { return rows_; }

int S21Matrix::get_col() { return cols_; }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (std::fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
        return false;
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::logic_error("Can't sum matrix with defferents row and col");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ && cols_ != other.cols_) {
    throw std::logic_error("Can't sub matrix with defferents row and col");
  }

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::logic_error("Can't mul this matrixes");
  }

  S21Matrix result(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int n = 0; n < cols_; n++) {
        result.matrix_[i][j] += matrix_[i][n] * other.matrix_[n][j];
      }
    }
  }

  *this = std::move(result);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[j][i] = matrix_[i][j];
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
  if (size == 1) return m[0][0];

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
  int row = rows_;
  int col = cols_;

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
  if (rows_ != cols_) {
    throw std::logic_error("rows != cols");
  }
  return help_calculator(*this);
}

double S21Matrix::Determinant() {
  if (rows_ <= 0 || cols_ <= 0 || rows_ != cols_) {
    throw std::logic_error("Error size matrix");
  }

  double res = 0;

  if (rows_ == 1) {
    res = matrix_[0][0];
  } else {
    res = determ(matrix_, rows_);
  }
  return res;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (cols_ != rows_) {
    throw std::logic_error("rows != cols");
  }

  double det = this->Determinant();
  if (std::fabs(det) < 1e-06) {
    throw std::logic_error("Error determinant");
  }

  S21Matrix help1 = this->CalcComplements();
  S21Matrix help2 = help1.Transpose();
  help2.MulNumber(1.0 / det);
  return help2;
}

double &S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0)
    throw std::logic_error("Incorrect input, index is out of range");

  return matrix_[row][col];
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) {
  if (this == &other) return *this;

  free_matrix(*this);

  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;

  return *this;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this == &other) return *this;

  free_matrix(*this);

  rows_ = other.rows_;
  cols_ = other.cols_;
  copy_cicle(*this, other);

  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);

  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);

  result.SumMatrix(other);

  return result;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);

  return *this;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);

  result.SubMatrix(other);

  return result;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);

  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  this->MulNumber(num);

  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
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
    throw std::logic_error("row can't be smaller that 1");
  } else if (new_row == rows_) {
    return;
  }

  int val = (new_row > rows_ ? rows_ : new_row);

  double **tmp = new double *[new_row]();
  for (int i = 0; i < new_row; i++) {
    tmp[i] = new double[cols_]();
  }

  for (int i = 0; i < val; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp[i][j] = matrix_[i][j];
    }
  }

  free_matrix(*this);

  matrix_ = tmp;

  rows_ = new_row;
}

void S21Matrix::set_col(int new_col) {
  if (new_col < 1) {
    throw std::logic_error("col can't be smaller that 1");
  } else if (new_col == cols_) {
    return;
  }

  int val = (new_col < cols_ ? new_col : cols_);
  for (int i = 0; i < rows_; i++) {
    double *tmp = new double[new_col]();
    for (int j = 0; j < val; j++) {
      tmp[j] = matrix_[i][j];
    }
    delete[] matrix_[i];
    matrix_[i] = tmp;
  }

  cols_ = new_col;
}

S21Matrix operator*(double num, const S21Matrix &other) {
  S21Matrix result(other);
  result.MulNumber(num);
  return result;
}
