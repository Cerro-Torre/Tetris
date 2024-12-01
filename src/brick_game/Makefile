CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
SRC_DIRS = gui/cli tetris
OBJS_FSMTABLE = out/tetris.o out/backend.o out/tetris_frontend_v2.o
LIBNAME = s21_tetris.a
LIB_BACKEND = backend_lib.a
GAMENAME = game
VG_LOG_FILE = valgrind-$(GAMENAME).log
VALGRIND = valgrind --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all -s 
TESTS_C = $(wildcard tests/*.c)
TESTS_O = $(patsubst tests/%.c, tests/%.o, $(TESTS_C))

LCOV = lcov --capture --directory . --output-file buf_coverage.info && sed '/tests\//d' buf_coverage.info > coverage.info && rm buf_coverage.info
GENHTML = genhtml coverage.info --output-directory report
XDG = xdg-open report/index.html

$(LIBNAME): $(OBJS_FSMTABLE)
	if [ ! -d "libs" ]; then \
	  mkdir libs; \
	fi
	ar rcs libs/$(LIBNAME) $^

$(GAMENAME): $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: tetris/%.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

out/%.o: ../gui/cli/%.c
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $< -o $@

tests: $(LIBNAME) $(TESTS_O)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TESTS_O) -L:./libs/$(LIBNAME) -o test_res -lcheck -lsubunit -lm
	./test_res

vg: tests
	$(VALGRIND) ./test_res  

gcov_report: $(LIBNAME) $(TESTS_C)
	mkdir -p report
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TESTS_C) -Llibs -l:$(LIBNAME) -o test_res -lcheck -lsubunit -lm
	./test_res
	$(LCOV)
	$(GENHTML)
	$(XDG)

clean:
	rm -f out/*.o tests/*.o $(GAMENAME) test_res *.a libs/* *.out $(VG_LOG_FILE) *.info *.gc* coverage.info
	rm -rf libs report gcov

rebuild:
	make clean && make $(GAMENAME)