#pragma once

#include <conio.h>
#include "Menu.h"
#include "Mario.h"
#include "Board.h"
#include "Barrel.h"

// The Game class represents the main game loop and controls the game's logic, future to control the game levels and score
class Game {

public:

    // Constructor for the Game class
    Game();

    // Starts the game loop and handles user input
    void play();

    // Enum for initial positions of characters
    enum Consts {
        MAX_BARRELS = 10, // Maximum number of barrels
        BARREL_INTERVAL = 30, // Interval for spawning barrels
    };

private: 

	Menu menu; // Initialize the menu
  
    const Board board; // Initialize a board to hold the original layout

    Mario mario; // Initialize Mario

    Barrel barrels[MAX_BARRELS]; // Initialize an array of barrels

    unsigned long int frames = 0; // Frame counter
  
    // Initializes the barrels
    void init_barrels();

    // Moves all active barrels
    void move_barrels();

    // Controls the spawning and movement of barrels
    void spawn_barrels();

    // For exercise 2 and 3 
    //int level = 1; // Current game level
    //int score = 0; // Current game score
};
