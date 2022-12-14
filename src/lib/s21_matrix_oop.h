#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#include <cmath>
#include <iostream>

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);
  S21Matrix(S21Matrix &&other);
  ~S21Matrix();

  int get_row();
  int get_col();
  void set_row(int new_row);
  void set_col(int new_col);

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  double &operator()(int row, int col);

  bool operator==(const S21Matrix &other);

  S21Matrix &operator=(S21Matrix &&other);
  S21Matrix &operator=(const S21Matrix &other);

  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix operator+(const S21Matrix &other);

  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);

  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(double num);
  friend S21Matrix operator*(double num, const S21Matrix &other);

 private:
  int rows_, cols_;
  double **matrix_;

  S21Matrix help_calculator(const S21Matrix &a);
  double determ(double **m, int size);
  void cofactor_matrix(double **src, double **dst, int jump_r, int jump_col,
                       int size);
  void create_matrix(S21Matrix &m);
  void copy_cicle(S21Matrix &m, const S21Matrix &other);
  void free_matrix(S21Matrix &m);
};

#endif
