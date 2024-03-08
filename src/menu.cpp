#include "../include/menu.hpp"

Menu::Menu(WINDOW *window)
{
    title = " [ Hangman ] ";
    this->window = window;
    getmaxyx(window, windowHeight, windowWidth);
    entries.push_back(MenuItem{0, "New Game"});
    entries.push_back(MenuItem(1, "Scores"));
    entries.push_back(MenuItem{2, "Exit"});
    menuItem = 0;
    options.push_back(NEW_GAME);
    options.push_back(SCORES);
    options.push_back(EXIT);
}

Menu::~Menu()
{
}

void Menu::drawMenu()
{
    int offset;
    int y = (windowHeight / 2) - (entries.size() * 2);
    int x = windowWidth / 2;
    for (size_t i = 0; i < entries.size(); ++i)
    {
        offset = entries.at(i).name.length() / 2;
        y += 2;
        if (i == static_cast<size_t>(menuItem))
        {
            wattron(window, A_REVERSE); // Highlight the present choice
        }
        // Move cursor and add menu item
        wmove(window, y, x - offset);
        waddstr(window, entries.at(i).name.c_str());
        wattroff(window, A_REVERSE);
    }
    y = (windowHeight / 2) - (entries.size() * 2);
}

Option Menu::display()
{
    wclear(window);
    keypad(window, TRUE);
    noecho();
    curs_set(0);

    int entriesSize = entries.size();
    int offset = title.length() / 2;
    int x = windowWidth / 2;
    int key = 0;

    box(window, 0, 0);
    mvwaddstr(window, 0, x - offset, title.c_str());

    drawMenu();

    // Handle user input
    do
    {
        key = getch();
        switch (key)
        {
        case KEY_DOWN:
            menuItem++;
            if (menuItem > entriesSize - 1)
                menuItem = 0;
            break;
        case KEY_UP:
            menuItem--;
            if (menuItem < 0)
                menuItem = entriesSize - 1;
            break;
        default:
            break;
        }
        drawMenu();
        wrefresh(window);
    } while (key != '\n');

    echo();
    curs_set(1);
    wclear(window);
    wrefresh(window);
    return options.at(menuItem);    // Return user selection
}