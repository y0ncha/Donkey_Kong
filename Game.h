#pragma once

#include <string>
#include <list> 
#include <filesystem>
#include <regex>
#include "Config.h"
#include "Mario.h"
#include "Display.h"
#include "Level.h"
#include "Utils.h"


class Level;
class Display;

/**
 * @class Game
 * Represents the main game loop and controls the game's logic.
 */
class Game {

public:
    // Constructor for the Game class
    Game();

    // Enum for game constants
    enum Consts {
        NOF_LEVELS = 10, // Number of levels in the game
		LEVELS_PER_PAGE = 5 // Number of levels to display per page 
    };

    // Starts the game loop and handles user input
    Game_State start();

	// Setter for the game status
    bool set_state(Game_State _state);

	// Getter for the game status
    Game_State get_state() const;

	// Setter for the game difficulty
	bool set_difficulty(Difficulty);

	// Getter for the game difficulty
	Difficulty get_difficulty() const;

	// Setter for the game level index
	bool set_level(short ind);

	// Getter for the game level index
    int get_mario_lives() const;

    // Method to get the level file names list
    const std::list<std::string>& get_fnames() const;

	// Method to get the number of levels
    int get_nof_levels() const;

private:

	// Game state
    Game_State state = IDLE; 

    // Difficulty level
    Difficulty dif_lvl = EASY; 

	// Level index to manage the game levels from the array
    short lvl_ind = 0; 

    // Mario to be passed to the levels
    Mario mario;

	// Display to print different messages and menus on screen
    Display& display;

	// Pointer to hold the current level, using unique pointer for better memory management and to ease the level incrementation
	std::unique_ptr<Level> curr_level = nullptr; 

	// Array of level files to load the levels from
    std::string level_files[Consts::NOF_LEVELS] = {"dkong_01.screen.txt", "dkong_02.screen.txt" , "dkong_03.screen.txt"};

	// List to hold the level files names, sorted alphabetically
    std::list<std::string> level_fnames;

    // Method to scan for level files in the directory
    void scan_for_fnames(const std::string& directory = std::filesystem::current_path().string());

	// Method to push the level file names to the list
	bool push_fname(const std::string& fname);

	// Method to pop the level file names from the list
    const std::string& pop_fname(int i = 0);

	// Method to load the levels from the files
	void advance_level(const std::string& fname);

    // int level = 1; // Current game level
    // int score = 0; // Current game score
};
