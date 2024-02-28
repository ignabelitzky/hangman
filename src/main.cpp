#include <iostream>
#include "../include/menu.h"
#include "../include/helper.h"
#include "../include/game.h"

int main() {
    initscr();
    Menu mainMenu(stdscr);
    Option selection = mainMenu.display();
    if(selection == NEW_GAME) {
        // run game
        endwin();
        Game game;
        game.run();
        // code to delete
        /*
        wclear(stdscr);
        move(0, 0);
        cv::Mat image = cv::imread("resources/Hangman-6.png", cv::IMREAD_GRAYSCALE);
        if(image.empty()) {
            std::cout << "Could not open or find the image\n";
            return -1;
        }
        cv::resize(image, image, cv::Size(80, 24), 0, 0, cv::INTER_LINEAR);
        for(int y = 0; y < image.rows; ++y) {
            for(int x = 0; x < image.cols; ++x) {
                float pixelValue = image.at<uchar>(y, x);
                char asciiChar = grayScaleToASCII(pixelValue);
                mvaddch(y, x, asciiChar);
            }
        }
        refresh();
        getch();
        */
    } else if(selection == EXIT) {
        // close application
        endwin();
    }
    return 0;
}