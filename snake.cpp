#include "common.h"

void init_snake(Snake *snake)
{
//    Log::info("init_snake::started\n");
    snake->tail = new sf::RectangleShape[100];
    snake->tail_count= 0;
    
    snake->needs_to_grow = false;

    snake->current_direction = Direction::RIGHT;
    snake->tail_zero_direction = snake->current_direction;

    snake->head = new sf::RectangleShape;
    snake->head->setSize(sf::Vector2f(BOARD_WIDTH-2,BOARD_HEIGHT-2));
    snake->head->setPosition(BOARD_WIDTH*3,BOARD_HEIGHT*2);
    snake->head->setFillColor(sf::Color::Blue);

    for(int i = 0; i < 2; ++i)
    {
        snake->tail[snake->tail_count].setPosition(
                snake->head->getPosition().x - BOARD_WIDTH*(i+1),
                snake->head->getPosition().y);
        snake->tail[snake->tail_count].setSize(sf::Vector2f(BOARD_WIDTH-2, BOARD_HEIGHT-2));
        snake->tail[snake->tail_count].setFillColor(sf::Color::Magenta);
        snake->tail_count++;
    }

}

void free_snake(Snake *snake)
{
    delete snake->head;
    delete[] snake->tail;
}

void render_snake(sf::RenderWindow *window, Snake *snake)
{
    window->draw(*snake->head);
    for(int i = 0; i < snake->tail_count; ++i)
    {
        window->draw(snake->tail[i]);
    }
}

void keyboard_snake_control(Snake *snake)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) &&
            snake->current_direction != Direction::DOWN &&
            snake->tail_zero_direction != Direction::DOWN)
    {
        snake->current_direction = Direction::UP;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
            snake->current_direction != Direction::UP &&
            snake->tail_zero_direction != Direction::UP)
    {
        snake->current_direction = Direction::DOWN;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) &&
            snake->current_direction != Direction::RIGHT &&
            snake->tail_zero_direction != Direction::RIGHT)
    {
        snake->current_direction = Direction::LEFT;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
            snake->current_direction != Direction::LEFT &&
            snake->tail_zero_direction != Direction::LEFT)
    {
        snake->current_direction = Direction::RIGHT;
    }
}

bool block_snake_movement()
{
    static int block = 0;
    int block_max = 10;

    if(block == block_max)
    {
        block = 0;
        return false;
    }

    block++;
    return true;
}

void move_snake(Snake *snake)
{
    sf::Vector2f dir;
    if(!block_snake_movement())
    {
        if(snake->current_direction == Direction::RIGHT)
        {
            dir = sf::Vector2f(1,0);
            _move_snake(snake, dir);
            snake->tail_zero_direction = Direction::RIGHT;
        }
        else if(snake->current_direction == Direction::LEFT)
        {
            dir = sf::Vector2f(-1,0);
            _move_snake(snake, dir);
            snake->tail_zero_direction = Direction::LEFT;
        }
        else if(snake->current_direction == Direction::UP)
        {
            dir = sf::Vector2f(0,-1);
            _move_snake(snake, dir);
            snake->tail_zero_direction = Direction::UP;
        }
        else if(snake->current_direction == Direction::DOWN)
        {
            dir = sf::Vector2f(0,1);
            _move_snake(snake, dir);
            snake->tail_zero_direction = Direction::DOWN;
        }
    }
}

void _move_snake(Snake *snake, sf::Vector2f dir)
{
    sf::Vector2f prev_head_position = snake->head->getPosition();
    sf::Vector2f prev_tail_pos1 = snake->tail[0].getPosition();
    sf::Vector2f prev_tail_pos2;
    sf::Vector2f prev_last_tail_pos;
    
    if(snake->needs_to_grow)
    {
        prev_last_tail_pos = snake->tail[snake->tail_count-1].getPosition();
    }

    snake->head->move(BOARD_WIDTH * dir.x, BOARD_HEIGHT * dir.y);
    snake->tail[0].setPosition(prev_head_position);

    for(int i = 1; i < snake->tail_count; ++i)
    {
        prev_tail_pos2 = snake->tail[i].getPosition();
        snake->tail[i].setPosition(prev_tail_pos1);
        prev_tail_pos1 = prev_tail_pos2;
    }

    if(snake->needs_to_grow)
    {
        grow_snake(snake, prev_last_tail_pos);
    }
}

void grow_snake(Snake *snake, sf::Vector2f prev_last_tail_pos)
{
    snake->needs_to_grow = false;
    snake->tail[snake->tail_count].setPosition(prev_last_tail_pos);
    snake->tail[snake->tail_count].setSize(sf::Vector2f(BOARD_WIDTH-2,BOARD_HEIGHT-2));
    snake->tail[snake->tail_count].setFillColor(sf::Color::Magenta);
    snake->tail_count++;
}

bool check_snake_collision_with_borders(sf::Vector2u window_pos, Snake *snake)
{
    if(snake->head->getPosition().x >= window_pos.x)
        return true;
    if(snake->head->getPosition().x < 0)
        return true;
    if(snake->head->getPosition().y >= window_pos.y)
        return true;
    if(snake->head->getPosition().y < 0)
        return true;

    return false;
}

bool check_snake_collision_with_apple(Apple *apple, Snake *snake)
{
    if(snake->head->getPosition() == apple->shape->getPosition())
    {
        return true;
    }

    return false;
}

bool check_snake_collision_with_itself(Snake *snake)
{
    for(int i = 0; i < snake->tail_count; ++i)
    {
        if(snake->head->getPosition() == snake->tail[i].getPosition())
            return true;
    }

    return false;
}

void snake_game_over(Snake *snake)
{
    snake->head->setFillColor(sf::Color(96,96,96));

    for(int i = 0; i < snake->tail_count; ++i)
    {
        snake->tail[i].setFillColor(sf::Color(96,96,96));
    }
}
