#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <random>
#include <ncurses.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

int gen_random_int(int min, int max);

std::string get_random_word();

char grayScaleToASCII(float scale);

void add_title_to_window(WINDOW *win, const std::string& title);

#endif