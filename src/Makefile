CC = g++
CFLAGS = -Wall -Werror -Wextra
SRC = lib/s21_matrix_oop.cc
OBJ = $(SRC:.cc=.o)
HEADER = lib/s21_matrix_oop.h
RM = rm -rf

all: s21_matrix_oop.a test

s21_matrix_oop.a: $(OBJ)
	ar rcs s21_matrix_oop.a $(OBJ)

test: s21_matrix_oop.a $(HEADER)
	cd tests; $(CC) $(CFLAGS) matrix_tests.cc ../s21_matrix_oop.a -o testerFile -lgtest; ./testerFile

lib/%.o:lib/%.cc $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) tests/testerFile
	$(RM) testerFile
	$(RM) s21_matrix_oop.a
	$(RM) lib/*.o

.PHONY: all clean test