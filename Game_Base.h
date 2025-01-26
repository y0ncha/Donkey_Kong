#pragma once

#include <string>
#include <list> 
#include <filesystem>
#include <regex>
#include <chrono>
#include <algorithm>
#include "Level_Base.h"
#include "Config.h"
#include "Mario.h"
#include "Display.h"
#include "Utils.h"
#include "Hof.h"


// Forward declaration
class Display;
class Hof;
class Level_Base;
class Regular_Level;
class Visual_Level;
class Silent_Level;
class Save_Level;

/**
 * @class Game_Base
 * Represents the main Game_Base loop and controls the Game_Base's logic.
 */
class Game_Base {

public:

	// todo delete
	virtual void pure() = 0;

    // Constructor for the Game_Base class
    Game_Base(Game_Mode mode);

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
	bool set_index(short ind);

	// Getter for the Game_Base level index
    int get_mario_lives() const;

    // Method to get the level file names list
    const std::list<std::string>& get_screens() const;

	// Method to get the number of levels
    int get_nof_screens() const;

    // Method to pop the level file names from the list
    const std::string& pop_screen(int i = -1) const;

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
    short level_ind; 

    // Mario to be passed to the levels
    Mario mario;

	// Display to print different messages and menus on screen
    Display& display;

	// Game_Base statistics
	Hof::Statistics stats; // Game_Base statistics

	// Hall of fame (Top 10 best scores)
	Hof& hall_of_fame;

	std::unique_ptr<Level_Base> curr_level;

	// List to hold the level files names, sorted alphabetically
    std::list<std::string> screens;

	// Method to save the Game_Base statistics
    void save_statistics();

	// Method to push the level file names to the list
	bool push_screen(const std::string& screen);

	// Method to load the levels from the files
	void advance_level();

	// Method to inittiate and validate the level
    bool set_level(const std::string& screen);

	// Method to scan for level files in a directory (default the .exe directory)
	void scan_for_screens(const std::string& directory = std::filesystem::current_path().string());

	// States handling methods
	void handle_run();
	void handle_pause();
	void handle_retry();
	void handle_fail(std::chrono::steady_clock::time_point start_t);
	void handle_success(std::chrono::steady_clock::time_point start_t);
};
