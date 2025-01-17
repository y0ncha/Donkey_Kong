#pragma once

#include <conio.h>
#include <string>
#include "Config.h"
#include <iomanip>
#include "Mario.h"
#include "Game.h"
#include "Level.h"

// Forward declaration of the Game class
class Game;
class Level;

static constexpr int NAME_LEN = 7; // Maximum length of the player's name

struct Statistics {
    char player_name[NAME_LEN] = "";
    int score = 0;
    std::pair<int, int> time_played = { 0 ,0 };
    int difficulty = 0;
};

/**
 * @class Display
 * Represents the game display and menus.
 */
class Display {
public:
    // Enum for the menu options
    enum class Menu_Options {
        DEF,
        START = '1', // Start the game
        LEVELS = '2', // Choose the level
		HALL_OF_FAME = '7', // Show the hall of fame
        KEYS = '8',  // Show the keys
        EXIT = '9',   // Exit the game
		ENTER = '\r', // Enter key
        RESUME = 27, // Resume to the game
    };

    // Get the singleton instance of Display
    static Display& get_instance(Game* pGame = nullptr);

	// Display the game's different menus and messages
    void pause_menu() const;
    Menu_Options main_menu() const;
    bool difficulty_menu() const;
    bool levels_menu() const;
    void exit_message() const;
    void strike_message() const;
    void failure_message() const;
    void success_message() const;
	bool error_message(const std::vector<Board::Err_Code>& errors) const;
	void winning_message() const;
    void keys_menu() const;
	void prompt_nickname() const;

private:

    // Static consts for the game
    static constexpr int LEVELS_PER_PAGE = 5; // Number of levels to display per page 

    // Private constructor to prevent instantiation
    Display() = default;

	// Pointer to the game
	Game* game = nullptr;

	// Prints the layout to the console
    void print_layout(const char layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1]) const;

	// Prints the levels from the levels_fname list
	void print_levels(int page_ind, int last_page) const;

    // Prints the top score
    void print_top_score() const;

    // read statistics from a file
    void readStatistics(std::fstream& file,int size, Statistics* stats)const;

    // sort the statistics and write them to the file
    void sortStatistics(Statistics* stats, int size, std::fstream& file) const;

    // Prints the statistics on the screen
    void printStatistics(const Statistics& stats, int line) const;

	// Displays a falshing message on the screen
	void flash_message(const std::vector<std::string>& messages, const std::vector<Coordinates>& positions) const;

    static char main_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char keys_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char pause_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char exit_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char fail_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char success_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char difficulty_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char strike_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char levels_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
	static char winning_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char error_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
	static char nickname_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1]; 
    static char top_score[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
};
