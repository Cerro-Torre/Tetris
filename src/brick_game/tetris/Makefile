CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
OBJ = out/tetris.o out/backend.o out/fsm.o out/tetris_frontend.o
LIBNAME = s21_tetris.a
GAMENAME = game
TESTS_C = $(wildcard tests/*.c)
TESTS_O = $(patsubst tests/%.c, tests/%.o, $(TESTS_C))
VALGRIND = valgrind --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all -s
DOXY_DIR = doxygen_dir
GAME_DIR = game_dir
DIST_DIR = dist


all: install

install: $(OBJ) $(LIBNAME)
	mkdir -p $(GAME_DIR)
	$(CC) $(CFLAGS) -o $(GAMENAME) -Llibs -l:s21_tetris.a -lncurses
	mv $(GAMENAME) $(GAME_DIR)

uninstall:
	rm -rf $(GAME_DIR)

dist: clean
	mkdir -p $(DIST_DIR)
	cp -rf src $(DIST_DIR)
	cp -rf inc $(DIST_DIR)
	cp -rf tests $(DIST_DIR)
	cp Doxyfile $(DIST_DIR)
	cp high_score.txt $(DIST_DIR)
	cp Makefile $(DIST_DIR)
	tar -cf $(DIST_DIR)/Tetris.tar.gz inc src tests Makefile Doxyfile high_score.txt

dvi:
	mkdir -p $(DOXY_DIR)
	doxygen

$(LIBNAME): $(OBJ)
	@mkdir -p $(dir libs/$@)
	ar rcs libs/$@ $^

$(GAMENAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses
	echo "0" > high_score.txt

out/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: ../../gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(LIBNAME) $(TESTS_O) 
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TESTS_O)  -Llibs -l:s21_tetris.a -o test_res -lcheck -lsubunit -lm
	./test_res

gcov_report: $(LIBNAME)
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c src/backend.c -o out/backend.o
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c src/fsm.c -o out/fsm.o

	$(CC) $(CFLAGS) $(GCOV_FLAGS) tests/*.c out/backend.o out/fsm.o -o test_res -lcheck -lsubunit -lm
	./test_res

	@mkdir -p report
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '*/tests/*' --output-file coverage_filtered.info
	genhtml coverage_filtered.info --output-directory report
	xdg-open report/index.html

clean:
	rm -f out/*.o tests/*.o $(GAMENAME) test_res *.a libs/* *.out 
	rm -f *.info *.gc* coverage.info ./out/*
	rm -rf libs report gcov
	rm -rf out
	rm -rf $(DIST_DIR)
	rm -rf $(DOXY_DIR)
	rm -rf $(GAME_DIR)
	echo "0" > high_score.txt


rebuild: clean all

vg_game: install
	$(VALGRIND) ./$(GAME_DIR)/$(GAMENAME)

vg: tests
	$(VALGRIND) ./test_res

clang:
	clang-format -i $(wildcard src/*.c)
	clang-format -i $(wildcard gui/cli/*.c)
	clang-format -i $(wildcard tests/*.c)
	clang-format -i $(wildcard inc/*.h)


