#include <iostream>
#include "../include/menu.h"
#include "../include/helper.h"
#include "../include/game.h"

int main()
{
    Option selection(NEW_GAME);
    do
    {
        initscr();
        noecho();
        Menu mainMenu(stdscr);
        selection = mainMenu.display();
        if (selection == NEW_GAME)
        {
            // run game
            endwin();
            do
            {
                Game game;
                game.run();
                game.game_over();
                selection = mainMenu.display();
            } while (selection != EXIT && selection != SCORES);
        }
        if (selection == SCORES)
        {
            endwin();
            try
            {
                display_scores();
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                exit(1);
            }
        }
    } while (selection != EXIT);
    wclear(stdscr);
    wrefresh(stdscr);
    endwin();
    return 0;
}
