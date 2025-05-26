WWW_FLAGS=-Wall -Werror -Wextra
GTEST_LIBS_FLAGS=-lgtest -lgtest_main -pthread
# FLAGS=-lstdc++ -static-libgcc -static-libstdc++
# CPP_FLAGS=-std=c++17
# флаг для отладки
# G_FLAG=-g

# убрал test после clean
all: clean run

TEST_SRC = $(wildcard tests/*.cpp)
test:
	g++ $(WWW_FLAGS) -g $(TEST_SRC) -std=c++20 -o test $(GTEST_LIBS_FLAGS)
	
# добавил test
run: test
	./test

TEST_O = $(wildcard tests/*.o)
clean:
	rm -f test

# добавил test
vg: clean test
	valgrind --tool=memcheck -s --leak-check=yes ./test

leaks: clean test
	leaks -atExit -- ./test































# .PHONY : all clean test clang valgrind gcov_report rebuild

# CC=gcc
# CFLAGS=-Wall -Werror -Wextra
# CPPFLAGS=-lstdc++ -std=c++17
# TEST_FLAGS:=$(CFLAGS) -g #-fsanitize=address -O1 -fno-omit-frame-pointer
# LINUX_FLAGS =-lrt -lpthread -lm -lsubunit
# GCOV_FLAGS?=--coverage#-fprofile-arcs -ftest-coverage
# LIBS=-lgtest
# VALGRIND_FLAGS=--trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose
# HEADER=s21_containers.h
# TEST_SRC=tests/tests.cpp

# OS := $(shell uname -s)
# USERNAME=$(shell whoami)

# ifeq ($(OS),Linux)
#   OPEN_CMD = xdg-open
# endif
# ifeq ($(OS),Darwin)
#	OPEN_CMD = open
# endif

# all: test gcov_report

# rebuild:
#	make clean
#	make all

# test:
# ifeq ($(OS), Darwin)
#	$(CC) $(TEST_FLAGS) $(LIBS) $(CPPFLAGS) $(TEST_SRC) -o test
# else
#	${CC} $(TEST_FLAGS) ${TEST_SRC} $(CPPFLAGS) -o test $(LIBS) $(LINUX_FLAGS)
# endif
#	./test

# ifeq ($(OS), Darwin)
#	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(LIBS) $(CPPFLAGS) $(TEST_SRC) -o gcov_report 
# else
#	$(CC) $(TEST_FLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o gcov_report $(LIBS) $(CPPFLAGS) $(LINUX_FLAGS)
# endif

# gcov_report:
#	./gcov_report
#	lcov -t "stest" -o s21_test.info -c -d ./ --no-external
#	genhtml -o report s21_test.info
#	$(OPEN_CMD) ./report/index.html

# clang:
#	cp ../materials/linters/.clang-format ../src/.clang-format
#	clang-format -style=Google -i tests/tests.cpp s21_containers.h \
	array/* AVLTree/* list/* map/* set/* stack/* tests/* vector/*
#	rm .clang-format

# leaks: test
#	leaks -atExit -- ./test

# valgrind: clean 
#	${CC} $(TEST_FLAGS) ${TEST_SRC}  $(CPPFLAGS) -o valgrind_test $(LIBS) $(LINUX_FLAGS)
#	CK_FORK=no valgrind $(VALGRIND_FLAGS) --log-file=RESULT_VALGRIND.txt ./valgrind_test
#	$(OPEN_CMD) ./RESULT_VALGRIND.txt

# clean:
#	rm -rf test *.dSYM valgrind_test gcov_report report test *.info *.gcno *.gcda *.a *.o RESULT_VALGRIND.txt