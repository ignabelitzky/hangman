#ifndef GAME_H
#define GAME_H

#include "helper.hpp"
#include "message_box.hpp"
#include <format>
#include <map>
#include <ncurses.h>
#include <string>
#include <vector>

class Game
{
  private:
    Stage hangmanState;
    std::map<Stage, cv::Mat> hangmanImages;
    WINDOW *hangmanWindow;
    WINDOW *hiddenWordWindow;
    WINDOW *availableLettersWindow;
    WINDOW *promptWindow;
    std::vector<char> availableLetters;
    std::string randomWord;
    std::string hiddenWord;
    std::string playerName;
    int playerScore;
    bool finish;
    bool isWinner;
    void initialize_windows();
    void update_hangman_window();
    void update_hidden_word_window();
    void update_available_letters_window();
    std::string update_prompt_window();
    void update_round(std::string input);
    static void update_text_from_prompt_window(WINDOW *promptWindow, std::string input);

  public:
    Game();
    ~Game();
    void run();
    void game_over();
};

#endif