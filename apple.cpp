#include "common.h"
#include <iostream>
static bool check_apple_new_pos_with_snake_pos(sf::Vector2f apple_new_pos, Snake *snake);

void init_apple(Apple *apple)
{
    apple->shape = new sf::CircleShape;
    apple->shape->setFillColor(sf::Color::Green);
    apple->shape->setRadius(BOARD_WIDTH/2);
}

void free_apple(Apple *apple)
{
    delete apple->shape;
}

void render_apple(sf::RenderWindow *window, Apple *apple)
{
    window->draw(*apple->shape);
}

void set_apple_pos(Apple *apple, Snake *snake)
{   
    int x, y;
    sf::Vector2f new_pos;
    do {

        x = (rand()%BOARD_COLS);
        y = (rand()%BOARD_ROWS);

        std::cout << "x = " << x << " y = " << y << std::endl;
        new_pos = sf::Vector2f(x*BOARD_WIDTH,y*BOARD_HEIGHT);
    } while(check_apple_new_pos_with_snake_pos(new_pos, snake));

    apple->shape->setPosition(new_pos);
}

static bool check_apple_new_pos_with_snake_pos(sf::Vector2f apple_new_pos, Snake *snake)
{
    if(snake->head->getPosition() == apple_new_pos)
    {
        return true;
    }

    for(int i = 0; i < snake->tail_count; ++i)
    {
        if(snake->tail[i].getPosition() == apple_new_pos)
            return true;
    }

    return false;
}
