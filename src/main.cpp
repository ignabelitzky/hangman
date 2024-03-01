#include <iostream>
#include "../include/menu.h"
#include "../include/helper.h"
#include "../include/game.h"

int main() {
    initscr();
    Menu mainMenu(stdscr);
    Option selection = mainMenu.display();
    if(selection == NEW_GAME) {
        // run game
        endwin();
        do {
            Game game;
            game.run();
            game.game_over();
            selection = mainMenu.display();
        } while(selection != EXIT);
    }
    wclear(stdscr);
    wrefresh(stdscr);
    endwin();
    return 0;
}
