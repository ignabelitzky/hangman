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
#include "../include/message_box.hpp"
#include "miniaudio.hpp"

enum Stage
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX
};

void populate_words();

int gen_random_int(int min, int max);

std::string get_random_word();

char grayScaleToASCII(float scale);

void add_title_to_window(WINDOW *win, const std::string &title);

void set_hangman_images(std::map<Stage, cv::Mat> &m);

void display_scores();

void save_score(const std::string &name, int score);

void sort_scores();

void clear_scores();

std::string get_player_name();

void data_callback(ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount);

#endif