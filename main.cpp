#include "common.h"
#include <sstream>

void init_font(sf::Font *font);
void init_game_over_text(sf::Text *text, sf::Font *font);
bool is_keyboard_blocked();

// Release key event can handle only in main event loop
// Add Score text on the top
// Add Pause text in the pause state
// Add Visible borders ?
// Add Log system
// apple taking adjust
// if I just press 'space' continually while playing it restarts after game over immediatelly
int main()
{
    srand(time(0));
    sf::RenderWindow window(
            sf::VideoMode(BOARD_COLS*BOARD_WIDTH, BOARD_ROWS*BOARD_HEIGHT), "Snake",
                    sf::Style::Close);
    window.setFramerateLimit(40);
    
    int apples_eaten = 0;
    int current_state = PLAYING_STATE;

    Board board;
    Snake snake;
    Apple apple;

    init_board(&board);
    init_snake(&snake);
    init_apple(&apple);
    
    set_apple_pos(&apple, &snake);
    
    sf::Font main_font;
    sf::Text game_over_text;
   
    init_font(&main_font);
    init_game_over_text(&game_over_text, &main_font);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
       
        //LOGIC STARTS HERE
        //
        if(current_state == PLAYING_STATE)
        {
            // if(!is_keyboard_blocked() &&
            //         sf::Keyboard::isKeyReleased(sf::Keyboard::Enter))
            // {
            //     current_state = PAUSE_STATE;
            //     printf("debug::pause state activated!\n");
            // }
        
            keyboard_snake_control(&snake);
    
            move_snake(&snake);

            if(check_snake_collision_with_borders(window.getSize(), &snake))
            {
                current_state = GAME_OVER_STATE;
                std::stringstream ss;
                ss << "OUT OF BOARD\nScore: " << apples_eaten << "!";
                game_over_text.setString(ss.str());
                game_over_text.setPosition(sf::Vector2f(
                    BOARD_WIDTH*BOARD_COLS/2 - game_over_text.getGlobalBounds().width/2,
                    BOARD_HEIGHT*BOARD_ROWS/2 - game_over_text.getGlobalBounds().height
                ));

                snake_game_over(&snake);
            }
            
            if(check_snake_collision_with_itself(&snake))
            {
                current_state = GAME_OVER_STATE;
                std::stringstream ss;
                ss << "DON't EAT YOURSELF!\nScore: " << apples_eaten << "!";
                game_over_text.setString(ss.str());
                game_over_text.setPosition(sf::Vector2f(
                    BOARD_WIDTH*BOARD_COLS/2 - game_over_text.getGlobalBounds().width/2,
                    BOARD_HEIGHT*BOARD_ROWS/2 - game_over_text.getGlobalBounds().height
                ));

                snake_game_over(&snake);
            }

            if(check_snake_collision_with_apple(&apple, &snake))
            {
                snake.needs_to_grow = true;
                apples_eaten++;
                set_apple_pos(&apple, &snake);
            }
        }
        else if(current_state == GAME_OVER_STATE)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                current_state = PLAYING_STATE;
                apples_eaten = 0;
                free_snake(&snake);
                init_snake(&snake);
                set_apple_pos(&apple,&snake);
            }
        }
        else if(current_state == PAUSE_STATE)
        {
            // if(!is_keyboard_blocked() &&
            //         sf::Keyboard::isKeyReleased(sf::Keyboard::Enter))
            // {
            //     printf("debug::pause state deactivated!\n");
            //     current_state = PLAYING_STATE;
            // }
        }
        
        //RENDER SECTION starts
        window.clear();
				
        render_board(&window,&board);
        render_snake(&window,&snake);
        render_apple(&window,&apple);

        if(current_state == GAME_OVER_STATE)
        {
            window.draw(game_over_text);
        }

        window.display();
        //RENDER SECTION ends
    }

    free_board(&board);
    free_snake(&snake);
    free_apple(&apple);

    return 0;
}

void init_font(sf::Font *font)
{
    if(!font->loadFromFile("Roboto-Regular.ttf"))
    {
        printf("debug::main font hasn't been loaded\n");
    }
}

void init_game_over_text(sf::Text *text, sf::Font *font)
{
    text->setCharacterSize(60);
    text->setFillColor(sf::Color::Yellow);
    text->setFont(*font);
    text->setString("Default");
}

bool is_keyboard_blocked()
{
    static int num = 0;
    int max_num = 10;

    if(num == max_num)
    {
        num = 0;
        return false;
    }

    num++;
    return true;
}
