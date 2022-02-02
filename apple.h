#pragma once
#include "common.h"



void init_apple(Apple *apple);
void free_apple(Apple *apple);
void render_apple(sf::RenderWindow *window, Apple *apple);
void set_apple_pos(Apple *apple, Snake *snake);