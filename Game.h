#pragma once

#include <conio.h>
#include "Menu.h"
#include "Mario.h"
#include "Board.h"
#include "Barrels.h"

// The Game class represents the main game loop and controls the game's logic, future to control the game levels and score
class Game {

public:

    // Constructor for the Game class
    Game();

    // Starts the game loop and handles user input
    void play(int max_barrels = 10, int sapwn_interval = 30);

private: 

	int max_barrels = 10, spawn_interval = 30; // Maximum number of barrels and the interval for spawning barrels

	Menu menu; // Initialize the menu
  
    const Board board; // Initialize a board to hold the original layout

    Mario mario; // Initialize Mario

	Barrels barrels; // Initialize the barrels

	unsigned long int frames = 0; // Used to follow the game frames for barrel control (can be used for future game features)

	// Method to handle user input
	void handle_input(); // Method to handle user input

	// Resets the level
	void reset_level();

    // Method to update the lives display
    void print_data() const;

	// Method to update print the board and the game's data
	void print_screen() const;

	// Method to advance the entities in the game
	void advance_entities(); 

	// Method to finish the game successfully
	void finish_success(); 

	// Method to finish the game unsuccessfully
	void finish_failure();

	// For exercise 2 and 3 
    //int level = 1; // Current game level
    //int score = 0; // Current game score
};
