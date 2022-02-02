#pragma once
#include "common.h"




void init_snake(Snake *snake);
void free_snake(Snake *snake);
void render_snake(sf::RenderWindow *window, Snake *snake);
void move_snake(Snake *snake);
void _move_snake(Snake *snake, sf::Vector2f dir);
bool check_snake_collision_with_borders(sf::Vector2u window_size, Snake *snake);
void keyboard_snake_control(Snake *snake);
bool check_snake_collision_with_apple(Apple *apple, Snake *snake);
bool check_snake_collision_with_itself(Snake *snake);
void snake_game_over(Snake *snake);
void grow_snake(Snake *snake, sf::Vector2f prev_last_tail_pos);
bool block_snake_movement();