#include "common.h"

void init_board(Board *board)
{
    board->cells = new sf::RectangleShape[BOARD_COLS*BOARD_ROWS];

    for(int i = 0; i < BOARD_ROWS; ++i)
    {
        for(int j = 0; j < BOARD_COLS; ++j)
        {
            int index = i*BOARD_COLS + j;
            board->cells[index].setPosition(
                    BOARD_WIDTH * j, BOARD_HEIGHT * i);
            board->cells[index].setOutlineThickness(1);
            board->cells[index].setOutlineColor(sf::Color::Red);
            board->cells[index].setSize(sf::Vector2f(
                BOARD_WIDTH, BOARD_HEIGHT            
            ));
            board->cells[index].setFillColor(sf::Color::Black);
        }
    }

}

void free_board(Board *board)
{
    delete[] board->cells;
}

void render_board(sf::RenderWindow *window, Board *board)
{
    for(int i = 0; i < BOARD_ROWS; ++i)
    {
        for(int j = 0; j < BOARD_COLS; ++j)
        {   
            int index = i*BOARD_COLS + j;
            window->draw(board->cells[index]);
        }
    }
}
