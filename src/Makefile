CC = gcc -Wall -Werror -Wextra
GCOV = -fprofile-arcs -ftest-coverage
INC_CHECK = $(shell pkg-config --cflags --libs check)
LFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)
QMAKE = qmake
INSTALL_DIR = bin
ifeq ($(OS), Linux)
	BUILD_DIR = build-3dviewer-Desktop_Qt_5_15_2_GCC_64bit-Debug/
	APP_DIR=
	LIBS = -lcheck -lm -lpthread -lsubunit -lrt
else ifeq ($(OS), Darwin)
	BUILD_DIR = build-3dviewer-Desktop_Qt_5_15_2_GCC_64bit-Debug/
	APP_DIR=3dviewer.app/Contents/MacOS
	LIBS = -lcheck
endif

all: clean build install

build:
	$(QMAKE) -o $(BUILD_DIR)/Makefile ./3dviewer/3dviewer.pro
	make -C $(BUILD_DIR)/

rebuild: clean all

install: build
	mkdir $(INSTALL_DIR)
	install $(BUILD_DIR)$(APP_DIR)/3dviewer $(INSTALL_DIR)/3dviewer

uninstall:
	rm -rf $(INSTALL_DIR)

dvi:
	doxygen Doxyfile
	cd latex && sed -i '/\\usepackage{ifthen}/a \\\DeclareUnicodeCharacter{200B}{}' refman.tex
	cd latex && make && latex refman.tex && cd ..	
	mv latex/refman.pdf ./
	mv latex/refman.dvi ./
	rm -rf latex

dist:
	tar -cf 3DViewer.tar 3dviewer Makefile

tests.a: ./3dviewer/parser.c ./3dviewer/affine_transform.c
	$(CC) -c --coverage $?
	ar -rcs $@ *.o
	ranlib $@
	rm -f *.o

tests: tests.a tests_/tests.c
	$(CC) tests_/tests.c $(INC_CHECK) $(LFLAGS) -lcheck tests.a -o $@
	./$@

gcov_report: tests
	gcovr -r . --html --html-details -o coverage_report.html

linter:
	clang-format -i --style=Google ./3dviewer/*.c ./3dviewer/*.h ./3dviewer/*.cpp
	clang-format -n --style=Google ./3dviewer/*.c ./3dviewer/*.h ./3dviewer/*.cpp

clean:
	rm -rf build* $(INSTALL_DIR) latex html
	rm -f *.info  *.tar *.gcno *.gcda gcov_report *.o *.a *.html tests *.pdf *.dvi *.html
	cd 3dviewer && rm -f *.gcno *.gcda gcov_report *.o *.a
	cd ..
