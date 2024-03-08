#include <iostream>
#include "../include/menu.hpp"
#include "../include/helper.hpp"
#include "../include/game.hpp"
#include "../include/audio.hpp"
#define MINIAUDIO_IMPLEMENTATION
#include "../include/miniaudio.hpp"

int main()
{
    Audio * audio = nullptr;
    try {
        audio = new Audio("./resources/audios/game-music.mp3");
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    audio->play();
    Option selection(NEW_GAME);
    do
    {
        initscr();
        noecho();
        Menu mainMenu(stdscr);
        selection = mainMenu.display();
        if (selection == NEW_GAME)
        {
            endwin();
            // Loop until the user selects exit
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
                wclear(stdscr);
                wrefresh(stdscr);
                endwin();
                exit(1);
            }
        }
    } while (selection != EXIT);
    delete audio;
    wclear(stdscr);
    wrefresh(stdscr);
    endwin();
    return 0;
}
