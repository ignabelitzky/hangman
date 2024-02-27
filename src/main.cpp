#include <iostream>
#include "../include/menu.h"

int main() {
    initscr();
    Menu mainMenu(stdscr);
    int selection = mainMenu.display();
    endwin();
    std::cout << "Option: " << selection << std::endl;
    return 0;
}