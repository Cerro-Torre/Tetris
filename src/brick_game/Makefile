CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra
SRC_DIRS = gui/cli tetris
OBJS_FSMTABLE = out/tetris.o out/backend.o out/tetris_frontend_v2.o
LIBNAME = s21_tetris.a
GAMENAME = game
VG_LOG_FILE = valgrind-$(GAMENAME).log
VALGRIND = valgrind --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all -s --log-file=$(VG_LOG_FILE)
# out/fsm_matrix.o out/backend.o out/frontend.o

lib: $(OBJS_FSMTABLE)
	ar rcs $(LIBNAME) $^
#	rm -f $(OBJS_FSMTABLE)

$(GAMENAME): $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: ../gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f out/*.o $(GAMENAME) $(LIBNAME) *.out $(VG_LOG_FILE)

rebuild:
	make clean && make $(GAMENAME)

front:
	gcc ../gui/cli/tetris_frontend_v2.c -lncurses  -o front.out && ./front.out
