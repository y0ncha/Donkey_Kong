#pragma once

#include <conio.h>
#include <string>
#include "Mario.h"
#include "Board.h"
#include "Barrels.h"



// Forward declaration of the
class Level;

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
        NOF_LEVELS = 3 // Number of levels in the game
    };

    // Enum for game status
    enum Status {
        DEF, // Default status
        RUN, // Game is running
        PAUSE, // Game is paused
		FIN_FAIL, // Game finished unsuccessfully
		FIN_SUC, // Game finished successfully
		EXIT, // Game is exited
    };

    // Enum for the game levels
    enum Difficulty {
        EASY = '1',
        MEDIUM = '2',
        HARD = '3'
    };

    // Starts the game loop and handles user input
    void start();

    /**
     * @class Display
     * Handles the display and interaction of the game's menus and messages.
     * This class is responsible for:
     * - Displaying the main menu when the program starts.
     * - Showing the keys and controls to the user.
     * - Managing the option to exit the game gracefully.
     */
    class Display {

    public:
        // Enum for the menu options
        enum Menu_Options {
            START = '1', // Start the game
			LEVELS = '2', // Choose the level
            KEYS = '8',  // Show the keys
            EXIT = '9',   // Exit the game
            RESUME = 27, // Resume to the game
        };

        void pause_menu(Game& game);
        void main_menu(Game &game);
        void difficulty_menu(Game& game);
		void levels_menu(Game& game);
        void exit_messege() const;
        void strike_messege() const;
        void failure_messege() const;
        void success_messege() const;
        void keys_menu() const;
        void render_hud(const Mario& mario) const;
        void render_level(const Mario& mario, const Board& board) const;

    private:

        void print_layout(const char layout[Screen_dim::Y][Screen_dim::X + 1]) const;

        static char main_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char keys_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char pause_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char exit_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char fail_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char success_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char difficulty_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char strike_layout[Screen_dim::Y][Screen_dim::X + 1];
        static char levels_layout[Screen_dim::Y][Screen_dim::X + 1];
    };

private:

    // Game status
    Status status = DEF;

	// Game difficulty
    Difficulty dif_lvl = EASY;

	// Level index
    short lvl_ind = 0;

    // Game components
    Mario mario; // Initialize Mario
    Display display; // Initialize the display

    std::string level_files[Consts::NOF_LEVELS] = {"dkong_01.screen.txt", "dkong_02.screen.txt" , "dkong_03.screen.txt"};
   
    // int level = 1; // Current game level
    // int score = 0; // Current game score
};

