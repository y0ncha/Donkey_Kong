#pragma once
#include <iostream>
#include <conio.h>
#include "Utils.h"
#include "Board.h"

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

    // Enum for the menu options
    enum Entry_menu {
        START = '1', // Start the game
        KEYS = '8',  // Show the keys
        EXIT = '9'   // Exit the game
    };

    // Enum for the menu types
    enum Menu_types {
        START_MENU = 0, // Show the start menu
        PAUSE_MENU = 1  // Show the pause menu
    };

    // Enum for the game levels
    enum Level {
        EASY = '1',
        MEDIUM = '2',
        HARD = '3'
    };

    // Run the menu
    int run(Menu_types type) const;

    // Choose the level
    int levels_menu() const;

    // Print the exit layout
    void exit_messege() const;

    // Print the try again layout
    void strike_messege() const;

    // Print the fail layout
    void failure_messege() const;

    // Print the success layout
    void success_messege() const;

    // Print the menu
    void print(Menu_types type) const;

    // Print the keys
    void keys_menu(Menu_types type) const;

private:

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
    static char levels_layout[Screen_dim::Y][Screen_dim::X + 1];
    // Strike message layout
    static char strike_layout[Screen_dim::Y][Screen_dim::X + 1];
};
