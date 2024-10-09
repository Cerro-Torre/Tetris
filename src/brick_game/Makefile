CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra
SRC_DIRS = gui/cli tetris
OBJS_FSMTABLE = out/tetris.o out/backend.o out/tetris_frontend_v2.o
LIBNAME = s21_tetris.a
LIB_BACKEND = backend_lib.a
GAMENAME = game
VG_LOG_FILE = valgrind-$(GAMENAME).log
VALGRIND = valgrind --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all -s 
TESTS_C = $(wildcard tests/*.c)
TESTS_O = $(patsubst tests/%.c, tests/%.o, $(TESTS_C))


# --log-file=$(VG_LOG_FILE)
# out/fsm_matrix.o out/backend.o out/frontend.o

$(LIBNAME): $(OBJS_FSMTABLE)
	if [ ! -d "libs" ]; then \
		mkdir libs; \
	fi
	ar rcs libs/$(LIBNAME) $^

back_lib: $(OBJS_FSMTABLE)
	ar rcs backend_lib.a $^

$(GAMENAME): $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: ../gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f out/*.o tests/*.o $(GAMENAME) test_res *.a libs/* *.out $(VG_LOG_FILE)
	rm -rf libs

rebuild:
	make clean && make $(GAMENAME)

front:
	gcc ../gui/cli/tetris_frontend_v2.c -lncurses  -o front.out && ./front.out

$(LIB_BACKEND): $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) tetris/backend.c -o out/backend.out

tests: $(LIBNAME) $(TESTS_O)
	$(CC) $(CFLAGS) $(TESTS_O) -L: ./libs/$(LIBNAME) -lcheck -lsubunit -o test_res -lm

vg: tests
	$(VALGRIND) ./test_res
