CC = g++
# CFLAGS = -Wall -Werror -Wextra
SRC = lib/s21_matrix_oop.cc \
		lib/s21_matrix_oop.h
OBJ = $(SRC:.cc=.o)
RM = rm -rf

all:
	s21_matrix_oop.a
	test

s21_matrix_oop.a: $(OBJ)
	ar rcs s21_matrix_oop.a $(OBJ)

test: s21_matrix_oop.a
	cd tests; $(CC) $(CFLAGS) matrix_tests.cc ../s21_matrix_oop.a -o testerFile -lgtest; ./testerFile

clean:
	$(RM) tests/testerFile
	$(RM) testerFile
	$(RM) s21_matrix_oop.a
	$(RM) lib/*.o
