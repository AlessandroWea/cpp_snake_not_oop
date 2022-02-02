#pragma once
#include <SFML/Graphics.hpp>

enum class Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT
};

#define PLAYING_STATE 1
#define GAME_OVER_STATE 2
#define PAUSE_STATE 3

#define BOARD_COLS 20
#define BOARD_ROWS 20
#define BOARD_WIDTH 40
#define BOARD_HEIGHT 40

typedef struct _Apple {
    sf::CircleShape *shape;
} Apple;

typedef struct _Snake {
    sf::RectangleShape *head;
    sf::RectangleShape *tail;
    int tail_count;
    bool needs_to_grow;
    Direction current_direction;
    Direction tail_zero_direction;
} Snake;

typedef struct _Board {
    sf::RectangleShape *cells;
} Board;

#include "snake.h"
#include "board.h"
#include "apple.h"