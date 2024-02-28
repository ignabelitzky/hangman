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
    cv::Mat image;
    int height = getmaxy(hangmanWindow)-2;
    int width = getmaxx(hangmanWindow);
    switch(state) {
        case ZERO:
            image = cv::imread("resources/Hangman-0.png", cv::IMREAD_GRAYSCALE);
            break;
        case ONE:
            image = cv::imread("resources/Hangman-1.png", cv::IMREAD_GRAYSCALE);
            break;
        case TWO:
            image = cv::imread("resources/Hangman-2.png", cv::IMREAD_GRAYSCALE);
            break;
        case THREE:
            image = cv::imread("resources/Hangman-3.png", cv::IMREAD_GRAYSCALE);
            break;
        case FOUR:
            image = cv::imread("resources/Hangman-4.png", cv::IMREAD_GRAYSCALE);
            break;
        case FIVE:
            image = cv::imread("resources/Hangman-5.png", cv::IMREAD_GRAYSCALE);
            break;
        case SIX:
            image = cv::imread("resources/Hangman-6.png", cv::IMREAD_GRAYSCALE);
            break;
        default:
            break;
    }
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

int Game::update_prompt_window() {
    int input;
    int maxy, maxx;
    getmaxyx(promptWindow, maxy, maxx);
    mvwaddstr(promptWindow, maxy/2, 1, "\tPlease enter a letter or a word >> ");
    wrefresh(promptWindow);
    input = wgetch(promptWindow);
    return input;
}

Game::Game() {
    state = ZERO;
    for(char i = 'A'; i <= 'Z'; ++i) {
        availableLetters.push_back(i);
    }
    randomWord = get_random_word();
    for(char& c : randomWord) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    hiddenWord = std::string(randomWord.length(), '_');
    finish = false;
    isWinner = false;
}

void Game::update_round(int letter) {
    std::vector<int> positionsFound;
    char ch = char(letter);
    availableLetters.erase(std::remove(availableLetters.begin(), availableLetters.end(), ch), availableLetters.end());
    for(size_t i = 0; i < randomWord.size(); ++i) {
        if(randomWord.at(i) == ch) {
            positionsFound.push_back(i);
        }
    }
    if(positionsFound.empty()) {
        if(state != SIX) {
            state = static_cast<Stage>(static_cast<int>(state) + 1);
        }
    } else {
        for(size_t i = 0; i < positionsFound.size(); ++i) {
            hiddenWord.at(positionsFound.at(i)) = ch;
        }
    }
}

Game::~Game() {

}

void Game::run() {
    initscr();

    initialize_windows();

    int ch = 0;

    do {
        update_hangman_window();
        update_hidden_word_window();
        update_available_letters_window();
        ch = update_prompt_window();
        update_round(ch);
        if(state == SIX) {
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
    move(0, 0);
    if(isWinner) 
        waddstr(stdscr, "You win!!!\n");
    else
        waddstr(stdscr, "You lose!!!\n");
    wrefresh(stdscr);
    
    getch();
    endwin();
}