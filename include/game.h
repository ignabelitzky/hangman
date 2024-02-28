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
        bool finish;
        void initialize_windows();
        void update_hangman_window();
        void update_hidden_word_window();
        void update_available_letters_window();
        int update_prompt_window();
    public:
        Game();
        ~Game();
        void run();
};

#endif