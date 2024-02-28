#ifndef MENU_H
#define MENU_H

#include <vector>
#include <utility>
#include <string>
#include <ncurses.h>

enum Option {
    NEW_GAME,
    EXIT
};

class Menu {
    private:
        std::string title;
        std::vector<std::pair<int, std::string>> entries;
        WINDOW *window;
        int windowHeight;
        int windowWidth;
        int menuItem;
        std::vector<Option> Options;
        void drawMenu();
    public:
        Menu(WINDOW *window);
        ~Menu();
        Option display();
};

#endif