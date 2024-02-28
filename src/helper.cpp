#include "../include/helper.h"

int gen_random_int(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

std::string get_random_word() {
    std::string inputFile = "data/clean_oxford_3000_word_list.txt";
    std::ifstream ifstrm{inputFile};
    std::string word;
    std::vector<std::string> words;
    if(!ifstrm) {
        std::cerr << "Error opening the file!" << std::endl;
    } else {
        while(std::getline(ifstrm, word)) {
            words.push_back(word); 
        }
        ifstrm.close();
    }
    return words.at(gen_random_int(0, words.size()-1));
}