CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
SRC_DIRS = gui/cli tetris
OBJS_FSMTABLE = out/tetris.o out/backend.o out/tetris_frontend_v2.o
LIBNAME = s21_tetris.a
GAMENAME = game
VG_LOG_FILE = valgrind-$(GAMENAME).log
TESTS_C = $(wildcard tests/*.c)
TESTS_O = $(patsubst tests/%.c, tests/%.o, $(TESTS_C))

$(LIBNAME): $(OBJS_FSMTABLE)
	if [ ! -d "libs" ]; then \
		mkdir libs; \
	fi
	ar rcs libs/$(LIBNAME) $^

$(GAMENAME): $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: ../gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(LIBNAME) $(TESTS_O)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TESTS_O) -Llibs -l:s21_tetris.a -o test_res -lcheck -lsubunit -lm
	./test_res

gcov_report: $(LIBNAME)
	mkdir -p report
	lcov --capture --directory . --output-file coverage.info --exclude tests/
	genhtml coverage.info --output-directory report
	xdg-open report/index.html

clean:
	rm -f out/*.o tests/*.o $(GAMENAME) test_res *.a libs/* *.out 
	rm -f $(VG_LOG_FILE) *.info *.gc* coverage.info
	rm -rf libs report gcov
	

rebuild:
	make clean && make $(GAMENAME)

