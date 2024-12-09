#pragma once

#include <iostream>
#include <windows.h>
#include <conio.h>

#include "Config.h"
#include "Utils.h"
#include "Mario.h"
#include "Board.h"
#include "Barrel.h"
#include "Menu.h"

/**
 * @class Game
 * Manages the main game structure, including the player (Mario),
 * the game board, and progress such as score and level.
 * This class handles the game loop, player input, and other gameplay logic.
 */
class Game {

    Menu menu;

	const Board org_board; // Initialize a board to hold the orginal layout

	Board curr_board; // Initialize a board to hold the data real-time

    Mario mario; // Initialize mario with board and config in constructor

    int level = 1; // Current game level
    int score = 0; // Current game score

public:

    Game():mario(&org_board, &curr_board){} // Initializes the Game class with the board and Mario

    void play(); // Starts the game loop and handles user input
};
