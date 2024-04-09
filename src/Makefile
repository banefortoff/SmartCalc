GCC = gcc
STD = -std=c11
FLAGS = -Wall -Werror -Wextra
CHECK_LIBS = -lcheck
COVERAGE = --coverage
SRCS = calculate.c parcer.c stack.c
TEST = test.c

ifeq ($(OS), Linux)
    CHECK_LIBS += -lm -lsubunit 
endif


all: clean install test

build:
	mkdir build
	cd ./build/ && qmake ../SmartCalc_v_1_0 && make && mv SmartCalc_v_1_0.app s21_calculator.app

install: build
	mkdir $(HOME)/Desktop/SmartCalc_v_1_0/
	cp -rf build/s21_calculator.app $(HOME)/Desktop/SmartCalc_v_1_0/

uninstall:
	rm -rf $(HOME)/Desktop/SmartCalc_v_1_0/

dvi:
	open dvi.md

dist:
	tar -cvzf SmartCalc_v_1_0.tar.gz SmartCalc_v_1_0 calculate.c calculator.h parcer.c dvi.md Makefile stack.c test.c 

compile:
	$(GCC) $(STD) $(FLAGS) $(SRCS) $(TEST) -o test $(CHECK_LIBS) $(COVERAGE)

test: clean compile
	./test
	rm -rf *.gcda *.gcno
	
lint: 
	clang-format -n *.c *.h

leak:
	CK_FORK=no leaks --atExit -- ./test

valgrind: test
	valgrind ./test --track-origins=yes --leak-check=full

gcov_report: clean compile
	./test
	lcov -t "gcov" -o gcov.info -c -d .
	genhtml -o report gcov.info 
	open ./report/index.html
	
clean:
	rm -rf *.gcda *.gcno *.out *.info *.tar.gz
	rm -rf *.o *.a test 
	rm -rf report build


