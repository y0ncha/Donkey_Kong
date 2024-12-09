#pragma once

#include <conio.h>
#include "Mario.h"
#include "Board.h"
#include "Barrel.h"

class Game {

    // Enum for initial positions of characters
    enum CONSTS {
        MAX_BARRELS = 10, // Maximum number of barrels
		BARREL_INTERVAL = 30 // Interval for spawning barrels
    };

    // Initializes the barrels
    void init_barrels();

    // Moves all active barrels
    void move_barrels();

    // Controls the spawning and movement of barrels
    void ctrl_barrels();

    const Board org_board; // Initialize a board to hold the original layout
    Board curr_board; // Initialize a board to hold the data in real-time

    Mario mario; // Initialize Mario

    Barrel barrels[CONSTS::MAX_BARRELS]; // Initialize an array of barrels

    unsigned long int frames = 0; // Frame counter

    // For exercise 2 and 3 
    //int level = 1; // Current game level
    //int score = 0; // Current game score

public:

    // Constructor for the Game class
    Game();

    // Starts the game loop and handles user input
    void play();
};
