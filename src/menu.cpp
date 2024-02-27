#include "../include/menu.h"

Menu::Menu(WINDOW *window) {
    title = "THE HANGMAN";
    this->window = window;
    getmaxyx(window, windowHeight, windowWidth);
    entries.push_back(std::pair(0, "New Game"));
    entries.push_back(std::pair(1, "Exit"));
    menuItem = 0;
}

Menu::~Menu() {

}

void Menu::drawMenu() {
    int offset;
    int y = (windowHeight / 2) - (entries.size() * 2);
    int x = windowWidth / 2;
    for(size_t i = 0; i < entries.size(); ++i) {
            offset = entries.at(i).second.length() / 2;
            y += 2;
            if(i == static_cast<size_t>(menuItem))
                attron(A_REVERSE);
            wmove(window, y, x - offset);
            waddstr(window, entries.at(i).second.c_str());
            attroff(A_REVERSE);
        }
        y = (windowHeight / 2) - (entries.size() * 2);
        wrefresh(window);
}

int Menu::display() {
    wclear(window);
    keypad(window, TRUE);
    noecho();
    curs_set(0);
    
    int entriesSize = entries.size();
    int offset = title.length() / 2;
    int y = (windowHeight / 2) - (entriesSize * 2);
    int x = windowWidth / 2;
    int key = 0;
    
    wmove(window, y, x - offset);
    waddstr(window, title.c_str());

    drawMenu();
    
    do {
        key = getch();
        switch(key) {
            case KEY_DOWN:
                menuItem++;
                if(menuItem > entriesSize - 1)
                    menuItem = 0;
                break;
            case KEY_UP:
                menuItem--;
                if(menuItem < 0)
                    menuItem = entriesSize - 1;
                break;
            default:
                break;
        }
        drawMenu();
    } while(key != '\n');
    
    echo();
    curs_set(1);
    return menuItem;
}