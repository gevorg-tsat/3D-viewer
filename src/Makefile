CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
C_FILES = file_to_object.c affine.c

all: install run


test:
	$(CC) $(CFLAGS) -lcheck -lm -lpthread ${C_FILES} tests.c -o test
	./test
	rm test

gcov_report:
	$(CC) $(CFLAGS) -fprofile-arcs -ftest-coverage *.c -pthread -lcheck -lm -o test
	./test
	lcov -t "test_html" -o unit_test.info -c -d . --rc lcov_branch_coverage=1
	genhtml -o test_html unit_test.info
	open test_html/index.html

clean:
	rm -rf *.gc* *.o test unit_test.info test_html/ test html/ latex/ build/
#	rm -f ~/Library/Preferences/*.viewer.plist

uninstall: clean
	rm -Rf build

install:
	[ -d build ] || mkdir -p build
	cd build && qmake ../Viewer
	make -C ./build/
	@rm $(addprefix ./build/, *.cpp *.h *.o Makefile)

dist: uninstall
	cd ../ && tar -cf Viewer.tar src

run: install open

open:
	open build/Viewer.app

creator:
	open Viewer/Viewer.pro

beautify:
	clang-format -i *.c *.h --style=Google
style:
	clang-format -n *.c *.h --style=Google
dvi:
	doxygen ./Doxyfile
	open html/index.html
