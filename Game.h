#pragma once

#include <conio.h>
#include "Menu.h"
#include "Mario.h"
#include "Board.h"
#include "Barrels.h"

/**
 * @class Game
 * Represents the main game loop and controls the game's logic, including levels and score.
 */
class Game {

public:
    // Constructor for the Game class
    Game();

    // Starts the game loop and handles user input
    void play(int max_barrels = 10, int spawn_interval = 30,int game_status=RUN);

    // Enum for game constants
    enum Consts {
        DEF_DELAY = 100, // Default delay for the game
        KILLED_DELAY = 800, // Delay for the killed animation
        PROMPT_DELAY = 1000, // Delay for the prompt message
    };
    enum Status
    {
        RUN = 1,
        EXIT = 2
    };


private:
    // Maximum number of barrels and the interval for spawning barrels
    int max_barrels = 10;
    int spawn_interval = 30;
    int game_status = RUN;

    // Game components
    Menu menu; // Initialize the menu
    Board board; // Initialize a board to hold the original layout
    Mario mario; // Initialize Mario
    Barrels barrels; // Initialize the barrels

    // Frame counter used to follow the game frames for barrel control (can be used for future game features)
    unsigned long int frames = 0;

    // Method to handle user input
    void handle_input();

    // Resets the level
    void reset_level();

    // Method to update the lives display
    void print_data() const;

    // Method to update and print the board and the game's data
    void print_game() const;

    // Method to advance the entities in the game
    void advance_entities();

    // Method to finish the game successfully
    void finish_success();

    // Method to finish the game unsuccessfully
    void finish_failure();

    // Method to try again
    void try_again();

    // For exercise 2 and 3
    // int level = 1; // Current game level
    // int score = 0; // Current game score
};
