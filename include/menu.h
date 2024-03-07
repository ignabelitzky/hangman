#ifndef MENU_H
#define MENU_H

#include <vector>
#include <utility>
#include <string>
#include <ncurses.h>

enum Option
{
    NEW_GAME,
    SCORES,
    EXIT
};

struct MenuItem
{
    int id;
    std::string name;
};

class Menu
{
private:
    std::string title;
    std::vector<MenuItem> entries;
    WINDOW *window;
    int windowHeight;
    int windowWidth;
    int menuItem;
    std::vector<Option> options;
    void drawMenu();

public:
    Menu(WINDOW *window);
    ~Menu();
    Option display();
};

#endif