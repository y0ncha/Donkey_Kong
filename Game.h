#pragma once

#include <string>
#include <list> 
#include <filesystem>
#include <regex>
#include <chrono>
#include "Config.h"
#include "Mario.h"
#include "Display.h"
#include "Level.h"
#include "Utils.h"

// Forward declaration of the Level class
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

	// Struct to hold the game statistics
	struct Statistics {
		std::string player_name;
		int score = 0;
		std::pair<int, int> time_played = { 0 ,0 };
		int difficulty = 0;
	};

	// Method to run the game
	void run();

    // Starts the game loop and handles user input
    void start();

	// Resets the game
	void reset();

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

    // Method to pop the level file names from the list
    const std::string& pop_fname(int i = -1) const;

	// Method to get the game statistics
	const Statistics& get_stats() const;

	// Method to scan for level files in the directory
	void scan_for_fnames(const std::string& directory = std::filesystem::current_path().string());

	// Method to set the player's nickname
	void set_nickname(const std::string& name);

private:

	// Game state
    Game_State state = Game_State::IDLE;

    // Difficulty level
    Difficulty dif_lvl = Difficulty::EASY;

	// Level index to manage the game levels from the array
    short lvl_ind = 0; 

    // Mario to be passed to the levels
    Mario mario;

	// Display to print different messages and menus on screen
    Display& display;

	// Game statistics
	Statistics stats; // Game statistics

	// Pointer to hold the current level, using unique pointer for better memory management and to ease the level incrementation
	std::unique_ptr<Level> curr_level = nullptr; 

	// List to hold the level files names, sorted alphabetically
    std::list<std::string> level_fnames;

	// Method to save the game statistics
    void save_stats();

	// Method to push the level file names to the list
	bool push_fname(const std::string& fname);

	// Method to load the levels from the files
	void advance_level(const std::string& fname);

	// Method to inittiate and validate the level
    void set_level(const std::string& fname);
};
