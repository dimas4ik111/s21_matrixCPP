#include <iostream>
#include "s21_matrix.h"

int main() {
    S21Matrix m(2, 2);
    
    // std::cout << m.get_row() << m.get_col() << std::endl;
    m.set_val_matrix(0, 0, 123.456);
    m.set_val_matrix(1, 1, 333.333);
    std::cout << m.get_val_matrix(0, 0) << LLL;
    std::cout << m.get_val_matrix(1, 1) << LLL;
}
