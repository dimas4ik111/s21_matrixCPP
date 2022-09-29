#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

#define LLL std::endl
#define PRINT std::cout <<  

#include <cmath>
#include <iostream>

class S21Matrix {
private:
    int rows_, cols_;
    double **matrix_;

public:
    S21Matrix();
    S21Matrix(int rows, int cols);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other);
    ~S21Matrix();

    int get_row();
    int get_col();
    void set_val_matrix(int i, int j, double num);
    double get_val_matrix(int i, int j);

    bool EqMatrix(const S21Matrix& other);
    // void SumMatrix(const S21Matrix& other);
    // void SubMatrix(const S21Matrix& other);
    // void MulNumber(const double num);
    // void MulMatrix(const S21Matrix& other);
    // S21Matrix Transpose();
    // S21Matrix CalcComplements();
    // double Determinant();
    // S21Matrix InverseMatrix();
};

#endif
