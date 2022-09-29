CC = g++
FLAGS = 
SRC =
RM = rm -rf 

main: 
	$(CC) main.cpp s21_matrix.cpp -o minitest
	./minitest

s21_matrix_oop.a:
	ar rcs s21_matrix.cpp s21_matrix.o
	ranlib s21_matrix_oop.a

test:
	cd tests; g++ matrix_tests.cpp -o testerFile; ./testerFile

clean:
	$(RM) tests/testerFile
	$(RM) minitest
	$(RM) ss21_matrix_oop.a
