CC = g++
CFLAGS = -Wall -Werror -Wextra
SRC = lib/s21_matrix.cc \
		lib/s21_matrix.h
OBJ = $(SRC:.cc=.o)
RM = rm -rf

all:
	s21_matrix_oop.a
	test

s21_matrix_oop.a: $(OBJ)
	ar rcs s21_matrix_oop.a $(OBJ)

test:
	cd tests; g++ matrix_tests.cpp -o testerFile; ./testerFile

clean:
	$(RM) tests/testerFile
	$(RM) testerFile
	$(RM) s21_matrix_oop.a
	$(RM) lib/*.o
