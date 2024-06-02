PROJECT := s21_smartcalc
.PHONY: all tests gcov_report stylefix check rebuild clean leak install uninstall dist dvi

CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -std=c++17 
#-fsanitize=address
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
TEST =  -lgtest_main -lgtest -lpthread
OS=$(shell uname -s)
SOURCES = model/calc.cc unit_test.cc

all : clean tests
clean : 
	rm -rf model/*.o *.gc* *.info test.out
	rm -rf *.dSYM
	rm -rf build
	rm -rf *tgz
	rm -rf gcovr

rebuild : clean all

tests: clean 
ifeq ($(OS), Darwin)
	$(CXX) $(CXXFLAGS) $(SOURCES)  -o test.out  $(TEST)
else
	$(CXX) $(CXXFLAGS) $(SOURCES)  -o test.out  $(TEST)
endif
	rm -rf *.o
	./test.out

gcov_report: clean
	$(CXX) $(CXXFLAGS) $(SOURCES) -o test.out $(TEST) $(GCOVFLAGS)
	./test.out
	mkdir gcovr/
	gcovr --html-details gcovr/report.details.html
	rm -rf ./*.gc*
	open gcovr/report.details.html


stylefix:
	@clang-format -i --style=Google $(SOURCES)
	
check:
	@clang-format -n --style=Google $(SOURCES)
	
install: uninstall
	@mkdir build
	-cd build && qmake ../SmartCalc2.pro -o makefile_f
	-cd build && make install -f makefile_f
	@cd build && rm -rf *.o *.cpp *.h makefile_f .qmake.stash

uninstall: clean
	rm -rf build
	@echo ------------------------------------Done--------------------------------------

dist:
	rm -rf Archive_s21_SmartCalc_v2/
	mkdir Archive_s21_SmartCalc_v2/
	mkdir Archive_s21_SmartCalc_v2/src
	mv build/Smart* Archive_s21_SmartCalc_v2/src/ 
	tar cvzf Archive_s21_SmartCalc_v2.tgz Archive_s21_SmartCalc_v2/
	rm -rf Archive_s21_SmartCalc_v2/
	@echo -----------------------------------Archivated-----------------------------------

dvi:
	open README.md

