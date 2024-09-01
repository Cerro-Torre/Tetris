CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wextra
SRC_DIRS = gui/cli tetris
OBJS_FSMTABLE := out/tetris.o out/tetris_frontend.o
# out/fsm_matrix.o out/backend.o out/frontend.o

tetris_fsmtable: $(OBJS_FSMTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

out/%.o: tetris/%.c
	$(CC) $(CFLAGS) -c $< -o $@

out/%.o: ../gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) out/*.o tetris_fsmtable

rebuild:
	make clean && make tetris_fsmtable