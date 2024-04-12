#include "../include/helper.hpp"

namespace
{
std::vector<std::string> words; // static vector to store the words
}

// Function to populate the words vector
void populate_words()
{
    std::string inputFile = "data/clean_oxford_3000_word_list.txt";
    std::ifstream ifstrm{inputFile};
    std::string word;
    if (ifstrm)
    {
        while (std::getline(ifstrm, word))
        {
            words.push_back(word);
        }
        ifstrm.close();
    }
    else
    {
        std::cerr << "Error opening the words file!" << std::endl;
    }
}

int gen_random_int(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

std::string get_random_word()
{
    if (words.empty())
    {
        populate_words();
    }
    return words.at(gen_random_int(0, words.size() - 1));
}

// Fucntion to convert a grayscale value to an ASCII character
char grayScaleToASCII(float scale)
{
    std::string asciiChars = " :-=+*#%@";
    int index = scale * (asciiChars.size() - 1) / 255;
    return asciiChars[index];
}

void add_title_to_window(WINDOW *win, const std::string &title)
{
    int start_pos = (getmaxx(win) - title.length()) / 2;
    if (start_pos < 1)
    {
        start_pos = 1;
    }
    box(win, 0, 0);
    mvwprintw(win, 0, start_pos, "%s", title.c_str());
}

void set_hangman_images(std::map<Stage, cv::Mat> &m)
{
    for (int i = 0; i < 7; ++i)
    {
        std::string fileName = "resources/Hangman-" + std::to_string(i) + ".png";
        cv::Mat image = cv::imread(fileName, cv::IMREAD_GRAYSCALE);
        m.insert({static_cast<Stage>(i), image});
    }
}

// Function to display the top 5 scores
void display_scores()
{
    sort_scores();
    std::string inputFile = "data/scores.txt";
    std::ifstream ifstrm(inputFile);
    std::string line;
    std::string output = "";
    if (ifstrm)
    {
        std::string topScores = "";
        int scoreCounter = 0;
        while (std::getline(ifstrm, line) && scoreCounter < 5)
        {
            topScores += line + "\n";
            ++scoreCounter;
        }
        if (scoreCounter == 0)
        {
            topScores = "No scores yet!";
        }
        ifstrm.close();
        try
        {
            std::vector<std::string> options = {"Go to menu", "Clear score"};
            MessageBox *msgBoxScores = new MessageBox(" [Top 5 scores] ", topScores, options);
            output = msgBoxScores->show();
            if (output == options.at(1))
            {
                clear_scores();
            }
            delete msgBoxScores;
        }
        catch (std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
    else
    {
        std::cerr << "Error opening the scores file!" << std::endl;
    }
}

// Function to save the player's score
void save_score(const std::string &name, int score)
{
    std::string inputFile = "data/scores.txt";
    std::ofstream ofstrm(inputFile, std::ios::app);
    if (ofstrm)
    {
        ofstrm << name << " " << score << std::endl;
        ofstrm.close();
    }
    else
    {
        std::cerr << "Error opening the scores file!" << std::endl;
    }
}

// Function to sort the scores in descending order
void sort_scores()
{
    std::string inputFile = "data/scores.txt";
    std::ifstream ifstrm(inputFile);
    std::string line;
    std::vector<std::pair<std::string, int>> scores;
    if (ifstrm)
    {
        for (int i = 0; std::getline(ifstrm, line); ++i)
        {
            std::istringstream iss(line);
            std::string name;
            int score;
            iss >> name >> score;
            scores.push_back(std::make_pair(name, score));
        }
        ifstrm.close();
        std::sort(scores.begin(), scores.end(),
                  [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b) {
                      return a.second > b.second;
                  });
        std::ofstream ofstrm(inputFile);
        if (ofstrm)
        {
            for (auto &score : scores)
            {
                ofstrm << score.first << " " << score.second << std::endl;
            }
            ofstrm.close();
        }
        else
        {
            std::cerr << "Error opening the scores file!" << std::endl;
        }
    }
    else
    {
        std::cerr << "Error opening the scores file!" << std::endl;
    }
}

// Function to clear the scores
void clear_scores()
{
    std::string inputFile = "data/scores.txt";
    std::ofstream ofstrm(inputFile);
    if (ofstrm)
    {
        ofstrm.close();
    }
    else
    {
        std::cerr << "Error opening the scores file!" << std::endl;
    }
}

// Function to get the player's name
std::string get_player_name()
{
    initscr();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *nameWin = newwin(3, xMax - 6, yMax / 2 - 1, 2);
    box(nameWin, 0, 0);
    add_title_to_window(nameWin, " [Enter your name] ");
    wrefresh(nameWin);
    char name[50];
    mvwgetnstr(nameWin, 1, 2, name, 50);
    delwin(nameWin);
    wrefresh(stdscr);
    endwin();
    return std::string(name);
}

void data_callback(ma_device *pDevice, void *pOutput, const void *pInput, ma_uint32 frameCount)
{
    ma_decoder *pDecoder = (ma_decoder *)pDevice->pUserData;
    if (pDecoder == nullptr)
    {
        return;
    }

    ma_data_source_read_pcm_frames(pDecoder, pOutput, frameCount, nullptr);

    (void)pInput;
}