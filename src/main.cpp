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
        Game game;
        game.run();
    } else if(selection == EXIT) {
        // close application
        endwin();
    }
    return 0;
}
