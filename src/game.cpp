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

    refresh();
    wrefresh(hangmanWindow);
    wrefresh(hiddenWordWindow);
    wrefresh(availableLettersWindow);
    wrefresh(promptWindow);
}

void Game::update_hangman_window() {
    wmove(hangmanWindow, 0, 0);
    int height = getmaxy(hangmanWindow)-2;
    int width = getmaxx(hangmanWindow);

    cv::Mat image = hangmanImages[hangmanState];
    cv::resize(image, image, cv::Size(height*2, height), 0, 0, cv::INTER_LINEAR);
    
    for(int y = 0; y < image.rows; ++y) {
        for(int x = 0; x < image.cols; ++x) {
            float pixelValue = image.at<uchar>(y, x);
            char asciiChar = grayScaleToASCII(pixelValue);
            mvwaddch(hangmanWindow, y+1, width/2 + x - height, asciiChar);
        }
    }
    wrefresh(hangmanWindow);
}

void Game::update_hidden_word_window() {
    int maxy, maxx;
    getmaxyx(hiddenWordWindow, maxy, maxx);
    int wordLength = randomWord.size();
    for(int i = 0; i < wordLength; ++i) {
        mvwaddch(hiddenWordWindow, maxy/2, maxx/2 - wordLength + i*2, hiddenWord.at(i));
    }
    wrefresh(hiddenWordWindow);
}

void Game::update_available_letters_window() {
    wclear(availableLettersWindow);
    box(availableLettersWindow, 0, 0);
    add_title_to_window(availableLettersWindow, "Available Letters");
    int maxy, maxx;
    getmaxyx(availableLettersWindow, maxy, maxx);
    for(size_t i = 0; i < availableLetters.size(); ++i) {
        mvwaddch(availableLettersWindow, maxy/2, maxx/2 - availableLetters.size() + i*2, availableLetters.at(i));
    }
    wrefresh(availableLettersWindow);
}

std::string Game::update_prompt_window() {
    int input;
    int maxy, maxx;
    getmaxyx(promptWindow, maxy, maxx);
    mvwaddstr(promptWindow, maxy/2, 1, "\tPlease enter a letter >> ");
    wrefresh(promptWindow);
    std::string result;
    while((input = wgetch(promptWindow)) != '\n') {
        if(input >= 'a' && input <= 'z') {
            input -= 32;
        }
        result.push_back(static_cast<char>(input));
    }
    wclear(promptWindow);
    box(promptWindow, 0, 0);
    add_title_to_window(promptWindow, "Prompt Window");
    mvwaddstr(promptWindow, maxy/2, 1, "\tPlease enter a letter >> ");
    wrefresh(promptWindow);
    return result;
}

void Game::game_over() {
    initscr();
    if(isWinner) {
        waddstr(stdscr, "You won!!!\n");
    } else {
        waddstr(stdscr, "You lose!!!\n");
    }
    waddstr(stdscr, std::string("The word was " + randomWord).c_str());
    waddstr(stdscr, "\n\nPress any key to go to the main menu.");
    wrefresh(stdscr);
    getch();
    endwin();
}

Game::Game() {
    hangmanState = ZERO;
    set_hangman_images(hangmanImages);
    for(char i = 'A'; i <= 'Z'; ++i) {
        availableLetters.push_back(i);
    }
    randomWord = get_random_word();
    hiddenWord = std::string(randomWord.length(), '_');
    finish = false;
    isWinner = false;
}

void Game::update_round(std::string input) {
    std::vector<int> positionsFound;
    if(input.size() == 1) {
        char ch = input.at(0);
        availableLetters.erase(std::remove(availableLetters.begin(), availableLetters.end(), ch), availableLetters.end());
        for(size_t i = 0; i < randomWord.size(); ++i) {
            if(randomWord.at(i) == ch) {
                positionsFound.push_back(i);
            }
        }
        if(positionsFound.empty()) {
            if(hangmanState != SIX) {
                hangmanState = static_cast<Stage>(static_cast<int>(hangmanState) + 1);
            }
        } else {
            for(size_t i = 0; i < positionsFound.size(); ++i) {
                hiddenWord.at(positionsFound.at(i)) = ch;
            }
        }
    } else {
        if(input.compare(randomWord) == 0) {
            hiddenWord = randomWord;
        } else {
            hangmanState = static_cast<Stage>(static_cast<int>(hangmanState) + 1);
        }
    }
}

Game::~Game() {

}

void Game::run() {
    initscr();

    initialize_windows();

    std::string input;

    do {
        update_hangman_window();
        update_hidden_word_window();
        update_available_letters_window();
        input = update_prompt_window();
        update_round(input);
        if(hangmanState == SIX) {
            finish = true;
        } else if(randomWord.compare(hiddenWord) == 0) {
            finish = true;
            isWinner = true;
        }
    } while(finish != true);

    wclear(hangmanWindow);
    wclear(hiddenWordWindow);
    wclear(availableLettersWindow);
    wclear(promptWindow);
    
    wrefresh(hangmanWindow);
    wrefresh(hiddenWordWindow);
    wrefresh(availableLettersWindow);
    wrefresh(promptWindow);

    delwin(hangmanWindow);
    delwin(hiddenWordWindow);
    delwin(availableLettersWindow);
    delwin(promptWindow);

    wclear(stdscr);
    wrefresh(stdscr);
    endwin();
}