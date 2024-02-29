#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <random>
#include <ncurses.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

enum Stage {
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX
};

int gen_random_int(int min, int max);

std::string get_random_word();

char grayScaleToASCII(float scale);

void add_title_to_window(WINDOW *win, const std::string& title);

void set_hangman_images(std::map<Stage, cv::Mat> &m);

#endif