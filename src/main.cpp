#include <iostream>
#include "../include/menu.h"
#include "../include/helper.h"

int main() {
    initscr();
    Menu mainMenu(stdscr);
    Option selection = mainMenu.display();
    if(selection == NEW_GAME) {
        // run game
        wclear(stdscr);
        move(0, 0);
        waddstr(stdscr, get_random_word().c_str());
        wrefresh(stdscr);
        getch();
    } else if(selection == EXIT) {
        // close application
    }
    endwin();
    return 0;
}