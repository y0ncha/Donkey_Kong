#pragma once

#include <conio.h>
#include <string>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include "Config.h"
#include "Mario.h"
#include "Game_Base.h"
#include "Hof.h"
#include "Level_Base.h"

// Forward declaration of the Game_Base class
class Game_Base;
class Level;

/**
 * @class Display
 * Represents the Game_Base display and menus.
 */
class Display {
public:
    // Enum for the menu options
    enum class Menu_Options {
        DEF,
        START = '1', // Start the Game_Base
        LEVELS = '2', // Choose the level
        HALL_OF_FAME = '7', // Show the hall of fame
        KEYS = '8',  // Show the keys
        EXIT = '9',   // Exit the Game_Base
        ENTER = '\r', // Enter key
        RESUME = 27, // Resume to the Game_Base
    };

    // Get the singleton instance of Display
    static Display& get_instance(Game_Base* pGame = nullptr);

    // put the result errors in the static vector
    static void push_res_errors(const std::string str);

    // print the file missing message
    static void print_file_missing(File_Type type, Game_Mode mode);

    // Display the Game_Base's different menus and messages
    void pause_menu() const;
    Menu_Options main_menu() const;
    bool difficulty_menu() const;
    bool levels_menu() const;
    void exit_message() const;
    void strike_message() const;
    void failure_message() const;
    void success_message() const;
    bool error_message(const std::vector<Board::Err_Code>& errors) const;
    bool error_message(std::string mesage) const;
    void winning_message() const;
    void keys_menu() const;
    void prompt_nickname() const;
	void top_scores() const;
    void result_message() const;

private:

    // Static consts for the Game_Base
    static constexpr int LEVELS_PER_PAGE = 5; // Number of levels to display per page 

    // Private constructor to prevent instantiation
    Display() = default;

    // Delete copy constructor and copy assignment operator
    Display(const Display&) = delete;
    Display& operator=(const Display&) = delete;

    // Delete move constructor and move assignment operator
    Display(Display&&) = delete;
    Display& operator=(Display&&) = delete;

    // Pointer to the Game_Base
    Game_Base* pGame = nullptr;

    // Prints the layout to the console
    void print_layout(const char layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1]) const;

    // Prints the levels from the levels_fname list
    void print_levels(int page_ind, int last_page) const;

    // Displays a flashing message on the screen
    void flash_message(const std::vector<std::string>& messages, const std::vector<Coordinates>& positions) const;

    // Vector of results errors messages
    static std::vector<std::string> Res_Errors;

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
    static char scores_board[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char result_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char step_file_missing_load[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char step_file_missing_save[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char result_file_missing_save[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
    static char result_file_missing_load[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
};
