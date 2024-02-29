#include "../include/helper.h"

namespace {
    std::vector<std::string> words;
}

int gen_random_int(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

std::string get_random_word() {
    if(words.empty()) {
        std::string inputFile = "data/clean_oxford_3000_word_list.txt";
        std::ifstream ifstrm{inputFile};
        std::string word;
        if(!ifstrm) {
            std::cerr << "Error opening the file!" << std::endl;
        } else {
            while(std::getline(ifstrm, word)) {
                words.push_back(word); 
            }
            ifstrm.close();
        }
    }
    return words.at(gen_random_int(0, words.size()-1));
}

char grayScaleToASCII(float scale) {
    std::string asciiChars = " :-=+*#%@";
    int index = scale * (asciiChars.size() - 1) / 255;
    return asciiChars[index];
}

void add_title_to_window(WINDOW *win, const std::string& title) {
    int start_pos = (getmaxx(win) - title.length()) / 2;
    if(start_pos < 1) {
        start_pos = 1;
    }
    box(win, 0, 0);
    mvwprintw(win, 0, start_pos, "%s", title.c_str());
}

void set_hangman_images(std::map<Stage, cv::Mat> &m) {
    for(int i = 0; i < 7; ++i) {
        std::string fileName = "resources/Hangman-" + std::to_string(i) + ".png";
        cv::Mat image = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
        m.insert({static_cast<Stage>(i), image});
    }
}