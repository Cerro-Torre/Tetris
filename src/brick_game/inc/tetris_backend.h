#ifndef TETRIS_BACKEND_H
#define TETRIS_BACKEND_H

#include <ncurses.h>

#include "defines.h"
#include "objects.h"
#include "string.h"

void init_game(GameInfo_t *game);
// void free_field(GameInfo_t *game);
// void free_next(GameInfo_t *game);
// void free_objects(GameInfo_t *game);
void free_game(GameInfo_t *game);
// void draw_field(GameInfo_t *game);
// void draw_next(GameInfo_t *game);
// void draw_objects(GameInfo_t *game);
// void draw_game(GameInfo_t *game);
// void draw_stats(GameInfo_t *game);
// void draw_game_over(GameInfo_t *game);
// void draw_help(GameInfo_t *game);
// void draw_pause(GameInfo_t *game);

#endif