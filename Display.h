#pragma once
#include <iostream>
#include <conio.h>
#include "Utils.h"
#include "Board.h"
#include "Mario.h"
#include "Level.h"
#include "Game.h"
/**
 * @class Display
 * Handles the display and interaction of the game's menus and messegaes.
 * This class is responsible for:
 * - Displaying the main menu when the program starts.
 * - Showing the keys and controls to the user.
 * - Managing the option to exit the game gracefully.
 */
class Display {

public:

    // Get the singleton instance of Display
    static const Display& getInstance() {
        static Display instance;
        return instance;
    }

    // Enum for the menu options
    enum Main {
        START = '1', // Start the game
        KEYS = '8',  // Show the keys
        EXIT = '9',   // Exit the game
    };

    enum Pause {
        RESUME = 27, // Resume the game
        KEYS = '8',  // Show the keys
        EXIT = '9',   // Exit the game
    };

    // Enum for the game levels
    enum Difficulty {
        EASY = '1',
        MEDIUM = '2',
        HARD = '3'
    };

    // Run the menu
    //int run(Menu_types type) const;

    Game::Status pause_menu(const Mario* mario, const Board& board) const;

    Game::Status main_menu() const;

    // Choose the level
    Difficulty difficulty_menu() const;

    // Print the exit layout
    void exit_messege() const;

    // Print the try again layout
    void strike_messege() const;

    // Print the fail layout
    void failure_messege() const;

    // Print the success layout
    void success_messege() const;

    // Print the menu
    //void print(Menu_types type) const;

    // Print the keys
    void keys_menu() const;

    // Method to update the Head-Up Display (in the future will use to keep track on score, time etc.)
	void render_hud(const Mario* mario) const;

    // Method to update and print the board and the game's data
	void render_level(const Mario* mario, const Board& board) const;

private:

	// Singlton design pattern - preventing multiple instances of Display
	Display() = default;

    // Print a given layout
    void print_layout(const char layout[Screen_dim::Y][Screen_dim::X + 1]) const;

    // Main menu layout
    static char main_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Keys instructions layout
    static char keys_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Pause menu layout
    static char pause_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Exit message layout
    static char exit_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Fail message layout
    static char fail_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Success message layout
    static char success_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Levels layout
    static char difficulty_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Strike message layout
    static char strike_layout[Screen_dim::Y][Screen_dim::X + 1];
};
