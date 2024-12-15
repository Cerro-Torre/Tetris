CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
SRC_DIRS = gui/cli tetris
OBJS_FSMTABLE = out/tetris.o out/backend.o out/fsm.o out/tetris_frontend_v2.o
LIBNAME = s21_tetris.a
GAMENAME = game
TESTS_C = $(wildcard tests/*.c)
TESTS_O = $(patsubst tests/%.c, tests/%.o, $(TESTS_C))
VALGRIND = valgrind --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all -s



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
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TESTS_O)  -Llibs -l:s21_tetris.a -o test_res -lcheck -lsubunit -lm
	./test_res

gcov_report: $(LIBNAME)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tetris/backend.c -o out/backend.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c tetris/fsm.c -o out/fsm.o

	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/*.c out/backend.o out/fsm.o -o test_res -lcheck -lsubunit -lm
	./test_res

	mkdir -p report
	# Собираем все данные покрытия
	lcov --capture --directory . --output-file coverage.info
	# Убираем файлы из директории tests
	lcov --remove coverage.info '*/tests/*' --output-file coverage_filtered.info
	# Генерируем HTML-отчет
	genhtml coverage_filtered.info --output-directory report
	xdg-open report/index.html


clean:
	rm -f out/*.o tests/*.o $(GAMENAME) test_res *.a libs/* *.out 
	rm -f $(VG_LOG_FILE) *.info *.gc* coverage.info
	rm -rf libs report gcov
	
rebuild:
	make clean && make $(GAMENAME)

vg: tests
	$(VALGRIND) ./test_res
