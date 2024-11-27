CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
TEMPCFLAGS = -fsanitize=address -fsanitize=undefined
SOURCE = $(wildcard s21*.c)
OBJ = $(SOURCE:.c=.o)
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = -lcheck `pkg-config --cflags --libs check`
endif

all: s21_matrix.a

$(OBJ): %.o: %.c

s21_matrix.a: $(OBJ)
	ar rc s21_matrix.a $(OBJ)
	ranlib s21_matrix.a

test: s21_matrix.a
	$(CC) $(CFLAGS) ./tests/s21_matrix_tests.c s21_matrix.a $(CHECK_FLAGS) -o test
	./test

gcov_report: $(SOURCE)
	$(CC) $(CFLAGS) --coverage ./tests/s21_matrix_tests.c $(SOURCE) $(CHECK_FLAGS) -o test
	./test
	lcov -o coverage.info -c -d .
	genhtml -o report coverage.info
	open report/index.html

valgrind: test
	valgrind --leak-check=full --undef-value-errors=yes --track-origins=yes --show-reachable=yes -s --log-file=valgrind.log ./test
	grep 'ERROR SUMMARY' valgrind.log

clean:
	rm -f *.o s21_matrix.a test *.info *.gcda *.gcno valgrind.log
	rm -rf report

rebuild: clean all