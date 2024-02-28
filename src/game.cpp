#include "../include/game.h"

void Game::initialize_windows() {
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    int yOffset = maxy / 2;

    hangmanWindow = newwin(yOffset, maxx, 0, 0);
    yOffset = 5;
    hiddenWordWindow = newwin(yOffset, maxx, maxy/2, 0);
    yOffset = 9;
    availableLettersWindow = newwin(yOffset, maxx, maxy/2 + 5, 0);
    yOffset = maxy - maxy / 2 - 14;
    promptWindow = newwin(yOffset, maxx, maxy/2 + 14, 0);

    add_title_to_window(hangmanWindow, "The Hangman");
    add_title_to_window(hiddenWordWindow, "Hidden Word");
    add_title_to_window(availableLettersWindow, "Available Letters");
    add_title_to_window(promptWindow, "Prompt Window");

    /*box(hangmanWindow, 0, 0);
    box(hiddenWordWindow, 0, 0);
    box(availableLettersWindow, 0, 0);
    box(promptWindow, 0, 0);*/

    refresh();
    wrefresh(hangmanWindow);
    wrefresh(hiddenWordWindow);
    wrefresh(availableLettersWindow);
    wrefresh(promptWindow);
}

Game::Game() {
    for(char i = 'A'; i <= 'Z'; ++i) {
        availableLetters.push_back(i);
    }
    hiddenWord = get_random_word();
}

Game::~Game() {

}

void Game::run() {
    initscr();
    wclear(stdscr);

    initialize_windows();

    getch();

    delwin(hangmanWindow);
    delwin(hiddenWordWindow);
    delwin(availableLettersWindow);
    delwin(promptWindow);
    endwin();
}