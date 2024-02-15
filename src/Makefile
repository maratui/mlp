CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -Werror -Wuninitialized
CLIBS  = -lgtest -lgtest_main
FILES = controller/* facade/* model/* view/* tests/*.h tests/*.cc

all: uninstall install

install: clean
	mkdir -p build
	mkdir -p bin
	cd build && cp ../mlp.pro ./mlp.pro && \
	qmake && make && rm -f *.o *.pro && mv mlp* ../bin/ && cd ../

uninstall: clean
	rm -rf bin

clean:
	rm -f *.gcda *.gcno
	rm -rf build

dvi:
	open dvi.html

dist: uninstall install
	tar  -cvzf ./bin/dist.tar ./bin/mlp*
	rm -f ./bin/mlp*

tests: clean
	mkdir -p build
	$(CC) $(CFLAGS) \
	facade/file* model/* tests/*.cc -o ./build/tests $(CLIBS)
	./build/tests

gcov-report: CFLAGS+= --coverage
gcov-report: tests
	lcov -t "tests" -o ./build/gcov-report.info -c -d . --no-external
	genhtml -o ./build/report ./build/gcov-report.info

googlestyle:
	cp ../materials/linters/.clang-format ./
	clang-format -i $(FILES)
	rm -f ./.clang-format

clang-format:
	cp ../materials/linters/.clang-format ./
	clang-format -n $(FILES)
	rm -f ./.clang-format

valgrind: CFLAGS+= -g
valgrind: tests
	valgrind --tool=memcheck --leak-check=yes -s -q ./build/tests

leaks: tests
	CK_FORK=no leaks -atExit -- ./build/tests

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++17 --language=c++ $(FILES)
