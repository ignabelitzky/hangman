#ifndef GAME_H
#define GAME_H

#include <ncurses.h>
#include <vector>
#include <string>
#include "helper.h"

enum Stage {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX
};

class Game {
    private:
        Stage state;
        WINDOW *hangmanWindow;
        WINDOW *hiddenWordWindow;
        WINDOW *availableLettersWindow;
        WINDOW *promptWindow;
        std::vector<char> availableLetters;
        std::string hiddenWord;
        void initialize_windows();
    public:
        Game();
        ~Game();
        void run();
};

#endif