#ifndef MENU_H
#define MENU_H

#include <vector>
#include <utility>
#include <string>
#include <ncurses.h>

class Menu {
    private:
        std::string title;
        std::vector<std::pair<int, std::string>> entries;
        WINDOW *window;
        int windowHeight;
        int windowWidth;
        int menuItem;
        void drawMenu();
    public:
        Menu(WINDOW *window);
        ~Menu();
        int display();
};

#endif