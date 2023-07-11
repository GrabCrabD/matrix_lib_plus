CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -fprofile-arcs -ftest-coverage
LIBS = -lgtest -lgtest_main -pthread

all: s21_matrix_oop.a test

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs s21_matrix_oop.a s21_matrix_oop.o

s21_matrix_oop.o: s21_matrix_oop.cpp s21_matrix_oop.h
	$(CXX) $(CXXFLAGS) -c s21_matrix_oop.cpp -o s21_matrix_oop.o

test: s21_matrix_test.o s21_matrix_oop.o
	$(CXX) $(CXXFLAGS) s21_matrix_test.o s21_matrix_oop.o $(LIBS) -o test
	./test

check_leaks: s21_matrix_test.o s21_matrix_oop.o
	$(CXX) $(CXXFLAGS) s21_matrix_test.o s21_matrix_oop.o $(LIBS) -o test
	leaks -atExit -- ./test

gcov_report: test
	mkdir -p report
	./test
	gcovr -r . -e s21_matrix_test.cpp --html --html-details -o report/report.html
	open report/report.html

s21_matrix_test.o: s21_matrix_test.cpp s21_matrix_oop.h
	$(CXX) $(CXXFLAGS) -c s21_matrix_test.cpp -o s21_matrix_test.o

clean:
	rm -rf *.o *.gcov *.gcno *.gcda test s21_matrix_oop s21_matrix_oop.a report
