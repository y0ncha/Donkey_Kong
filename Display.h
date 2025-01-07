#pragma once

#include <conio.h>
#include <string>
#include "Config.h"
#include "Mario.h"
#include "Game.h"
#include "Level.h"

// Forward declaration of the Game class
class Game;
class Level;

/**
 * @class Display
 * Represents the game display and menus.
 */
class Display {
public:
    // Enum for the menu options
    enum Menu_Options {
        DEF,
        START = '1', // Start the game
        LEVELS = '2', // Choose the level
        KEYS = '8',  // Show the keys
        EXIT = '9',   // Exit the game
        RESUME = 27, // Resume to the game
    };

    // Get the singleton instance of Display
    static Display& get_instance(Game* pGame = nullptr);


    void pause_menu() const;
    void main_menu() const;
    bool difficulty_menu() const;
    void levels_menu() const;
    void exit_messege() const;
    void strike_messege() const;
    void failure_messege() const;
    void success_messege() const;
    void keys_menu() const;

private:

    // Private constructor to prevent instantiation
    Display() = default;

	// Pointer to the game
	Game* game = nullptr;

	// Prints the layout to the console
    void print_layout(const char layout[Screen_Dim::Y][Screen_Dim::X + 1]) const;

	// Prints the levels from the levels_fname list
	void print_levels() const;

    static char main_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char keys_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char pause_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char exit_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char fail_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char success_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char difficulty_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char strike_layout[Screen_Dim::Y][Screen_Dim::X + 1];
    static char levels_layout[Screen_Dim::Y][Screen_Dim::X + 1];
};
