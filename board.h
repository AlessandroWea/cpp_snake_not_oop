#pragma once
#include "common.h"



void init_board(Board *board);
void free_board(Board *board);
void render_board(sf::RenderWindow *window, Board *board);