CC=gcc -std=c++17
CFLAGS=-Wall -Werror -Wextra -lstdc++
SOURCES=matrix_oop.cc
TEST_SOURSE = tests_matrix.cc
LIBO=matrix_oop.o
LIBA=matrix_oop.a
EXE=tests.out

OS = $(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lgtest_main -lstdc++
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs -lgtest -lgtest_main`
endif

all: matrix_oop.a

rebuild: clean all

matrix_oop.a: clean
	$(CC) $(CFLAGS) -c $(SOURCES) -o ./$(LIBO)
	ar rcs $(LIBA) $(LIBO)
	ranlib $(LIBA)

test: matrix_oop.a
	@$(CC) $(CFLAGS) $(TEST_SOURSE) $(LIBA) $(LIBFLAGS) -o ./tests.out
	./tests.out

gcov_report: matrix_oop.a
	$(CC) $(CFLAGS) --coverage $(TEST_SOURSE) $(SOURCES) $(LIBA) -L. $(LIBA)  $(LIBFLAGS) -o ./$(EXE)
	./$(EXE)
	lcov --ignore-errors mismatch -t "test" -c -d  ./  --no-external --output-file ./coverage.info
	genhtml $(BUILD_PATH)coverage.info --output-directory ./report/
	open ./report/index.html

leaks:
	# CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt 	$(BUILD_PATH)$(EXE)
	leaks -atExit -- ./$(EXE) 

style:
	@echo
	@echo ===STYLE TEST===
	cp ../materials/linters/.clang-format ./
	clang-format -n *.cc *.h
	rm .clang-format

clean:
	rm -rf matrix && rm -rf *.a && rm -rf *.o *.out
	rm -rf *.info && rm -rf *.gcda && rm -rf *.gcno &&  rm -rf *.gcov rm -rf *.gch