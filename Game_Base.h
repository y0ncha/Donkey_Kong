#pragma once

#include <string>
#include <list> 
#include <filesystem>
#include <regex>
#include <chrono>
#include <algorithm>
#include "Config.h"
#include "Mario.h"
#include "Display.h"
#include "Level.h"
#include "Utils.h"
#include "Hof.h"


// Forward declaration
class Level;
class Display;
class Hof;
/**
 * @class Game_Base
 * Represents the main Game_Base loop and controls the Game_Base's logic.
 */
class Game_Base {

public:

	// todo delete
	virtual void pure() = 0;

    // Constructor for the Game_Base class
    Game_Base(Game_Mode);

	// Destructor for the Game_Base class
	virtual ~Game_Base() = default;

	// Method to run the Game_Base
	void run();

    // Starts the Game_Base loop and handles user input
    void start();

	// Resets the Game_Base
	void reset();

	// Setter for the Game_Base status
    bool set_state(Game_State _state);

	// Getter for the Game_Base status
    Game_State get_state() const;

	// Setter for the Game_Base difficulty
	bool set_difficulty(Difficulty);

	// Getter for the Game_Base difficulty
	Difficulty get_difficulty() const;

	// Setter for the Game_Base level index
	bool set_level(short ind);

	// Getter for the Game_Base level index
    int get_mario_lives() const;

    // Method to get the level file names list
    const std::list<std::string>& get_fnames() const;

	// Method to get the number of levels
    int get_nof_levels() const;

    // Method to pop the level file names from the list
    const std::string& pop_fname(int i = -1) const;

	// Method to get the Game_Base statistics
	const Hof::Statistics& get_statistics() const;

	// Method to set the player's nickname
	void set_nickname(const std::string&);

	// Method to get the hall of fame list
	const std::list<Hof::Statistics>& get_hof() const;

private:

	// Game mode
	Game_Mode mode;

	// Gam state
    Game_State state;

    // Difficulty level
    Difficulty dif_lvl;

	// Level index to manage the Game_Base levels from the array
    short lvl_ind; 

    // Mario to be passed to the levels
    Mario mario;

	// Display to print different messages and menus on screen
    Display& display;

	// Game_Base statistics
	Hof::Statistics stats; // Game_Base statistics

	// Hall of fame (Top 10 best scores)
	Hof& hall_of_fame;

	// Pointer to hold the current level, using unique pointer for better memory management and to ease the level incrementation
	std::unique_ptr<Level> curr_level;

	// List to hold the level files names, sorted alphabetically
    std::list<std::string> level_fnames;

	// Method to save the Game_Base statistics
    void save_statistics();

	// Method to push the level file names to the list
	bool push_fname(const std::string& fname);

	// Method to load the levels from the files
	void advance_level(const std::string& fname);

	// Method to inittiate and validate the level
    void set_level(const std::string& fname);

	// Method to scan for level files in a directory (default the .exe directory)
	void scan_for_fnames(const std::string& directory = std::filesystem::current_path().string());
};
