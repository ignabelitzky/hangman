#include "../include/game.hpp"

void Game::initialize_windows()
{
    // Get screen dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);
    int yOffset = maxy / 2;

    // Create windows for different parts of the game
    hangmanWindow = newwin(yOffset, maxx, 0, 0);
    yOffset = 5;
    hiddenWordWindow = newwin(yOffset, maxx, maxy / 2, 0);
    yOffset = 9;
    availableLettersWindow = newwin(yOffset, maxx, maxy / 2 + 5, 0);
    yOffset = maxy - maxy / 2 - 14;
    promptWindow = newwin(yOffset, maxx, maxy / 2 + 14, 0);

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

// Update hangman windowwith the current hangman state
void Game::update_hangman_window()
{
    wmove(hangmanWindow, 0, 0);
    int height = getmaxy(hangmanWindow) - 2;
    int width = getmaxx(hangmanWindow);

    // Resize hangman image to fit the window
    cv::Mat image = hangmanImages[hangmanState];
    cv::resize(image, image, cv::Size(height * 2, height), 0, 0, cv::INTER_LINEAR);

    // Draw the hangman image to the window
    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            float pixelValue = image.at<uchar>(y, x);
            char asciiChar = grayScaleToASCII(pixelValue);
            mvwaddch(hangmanWindow, y + 1, width / 2 + x - height, asciiChar);
        }
    }

    // Print player name and score on hangman window
    mvwprintw(hangmanWindow, 1, 1, "Player: %s", playerName.c_str());
    mvwprintw(hangmanWindow, 2, 1, "Score: %d", playerScore);
    wrefresh(hangmanWindow);
}

// Update hidden word window with the current hidden word
void Game::update_hidden_word_window()
{
    int maxy, maxx;
    getmaxyx(hiddenWordWindow, maxy, maxx);
    int wordLength = randomWord.size();
    for (int i = 0; i < wordLength; ++i)
    {
        mvwaddch(hiddenWordWindow, maxy / 2, maxx / 2 - wordLength + i * 2, hiddenWord.at(i));
    }
    wrefresh(hiddenWordWindow);
}

// Update available letters window with the current available letters
void Game::update_available_letters_window()
{
    wclear(availableLettersWindow);
    box(availableLettersWindow, 0, 0);
    add_title_to_window(availableLettersWindow, "Available Letters");
    int maxy, maxx;
    getmaxyx(availableLettersWindow, maxy, maxx);
    for (size_t i = 0; i < availableLetters.size(); ++i)
    {
        mvwaddch(availableLettersWindow, maxy / 2, maxx / 2 - availableLetters.size() + i * 2, availableLetters.at(i));
    }
    wrefresh(availableLettersWindow);
}

// Update prompt window to get user input
std::string Game::update_prompt_window()
{
    int input;
    update_text_from_prompt_window(promptWindow, "");
    std::string result;

    // Continue to get input until the user presses enter
    while ((input = wgetch(promptWindow)) != '\n')
    {
        if (input == 127) // Handle backspace(delete) key
        {
            if (result.size() > 0)
            {
                result.pop_back();
                update_text_from_prompt_window(promptWindow, result);
            }
            continue;
        }
        if (input >= 'a' && input <= 'z')
        {
            input -= 32;
        }
        wprintw(promptWindow, "%c", input);
        wrefresh(promptWindow);
        result.push_back(static_cast<char>(input));
    }
    update_text_from_prompt_window(promptWindow, result);
    return result;
}

// Display game over message and save player score
void Game::game_over()
{
    std::vector<std::string> options = {"Go to the main menu"};
    std::string message =
        std::format("You {}!!!\n\nThe word was {}\n\nScore: {}", isWinner ? "won" : "lose", randomWord, playerScore);
    try
    {
        MessageBox *mboxGameOver = new MessageBox(" [Game Over] ", message, options);
        mboxGameOver->show();
        delete mboxGameOver;
    }
    catch (const std::runtime_error &e)
    {
        endwin();
        std::cerr << e.what() << '\n';
        exit(1);
    }
    save_score(playerName, playerScore);
}

Game::Game()
{
    hangmanState = ZERO;
    set_hangman_images(hangmanImages);
    for (char i = 'A'; i <= 'Z'; ++i)
    {
        availableLetters.push_back(i);
    }
    randomWord = get_random_word();
    hiddenWord = std::string(randomWord.length(), '_');
    finish = false;
    isWinner = false;
    playerName = "";
    playerScore = 0;
}

// Update the game state based on the user input
void Game::update_round(std::string input)
{
    std::vector<int> positionsFound;
    if (input.size() == 1)
    {
        char ch = input.at(0);
        availableLetters.erase(std::remove(availableLetters.begin(), availableLetters.end(), ch),
                               availableLetters.end());
        for (size_t i = 0; i < randomWord.size(); ++i)
        {
            if (randomWord.at(i) == ch)
            {
                positionsFound.push_back(i);
            }
        }
        if (positionsFound.empty())
        {
            playerScore -= 10;
            if (hangmanState != SIX)
            {
                hangmanState = static_cast<Stage>(static_cast<int>(hangmanState) + 1);
            }
        }
        else
        {
            for (size_t i = 0; i < positionsFound.size(); ++i)
            {
                playerScore += 5;
                hiddenWord.at(positionsFound.at(i)) = ch;
            }
        }
    }
    else
    {
        if (input.compare(randomWord) == 0) // If the user guessed the word
        {
            playerScore += 50;
            hiddenWord = randomWord;
        }
        else
        {
            playerScore -= 50;
            hangmanState = static_cast<Stage>(static_cast<int>(hangmanState) + 1);
        }
    }
}

Game::~Game()
{
}

// Main function to run the game
void Game::run()
{
    playerName = get_player_name();
    initscr();
    noecho();
    initialize_windows();

    std::string input;

    // Main loop game
    do
    {
        update_hangman_window();
        update_hidden_word_window();
        update_available_letters_window();
        input = update_prompt_window();
        update_round(input);

        // Check game ending conditions
        if (hangmanState == SIX)
        {
            finish = true;
        }
        else if (randomWord.compare(hiddenWord) == 0)
        {
            finish = true;
            isWinner = true;
        }
    } while (finish != true); // Continue game loop until the game is finished

    // Clear all game windows
    wclear(hangmanWindow);
    wclear(hiddenWordWindow);
    wclear(availableLettersWindow);
    wclear(promptWindow);

    // Refresh all game windows
    wrefresh(hangmanWindow);
    wrefresh(hiddenWordWindow);
    wrefresh(availableLettersWindow);
    wrefresh(promptWindow);

    // Delete all game windows
    delwin(hangmanWindow);
    delwin(hiddenWordWindow);
    delwin(availableLettersWindow);
    delwin(promptWindow);

    wclear(stdscr);
    wrefresh(stdscr);
    endwin();
}

// Update text on the prompt window
void Game::update_text_from_prompt_window(WINDOW *promptWindow, std::string input)
{
    int maxy = getmaxy(promptWindow);
    std::string message = std::format("\tPlease enter a letter or a word >> {}", input);
    wclear(promptWindow);
    box(promptWindow, 0, 0);
    add_title_to_window(promptWindow, "Prompt Window");
    mvwaddstr(promptWindow, maxy / 2, 1, message.c_str());
    wrefresh(promptWindow);
}