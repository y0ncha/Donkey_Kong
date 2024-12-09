#include "Game.h"

/**
 * Constructor to initialize the Game class with the board and Mario.
 * Also initializes the barrels.
 */
Game::Game() : mario(&org_board, &curr_board) {
    init_barrels(); // Initialize the barrels
}

/**
 * Starts the game loop.
 *
 * Initializes the game components, hides the console cursor, and begins the main game loop.
 * The loop listens for key inputs to control Mario and updates the game state.
 * Pressing the ESC key pauses the game and opens the menu.
 */
void Game::play() {

    ShowConsoleCursor(false); // Hide the console cursor for better visuals

    org_board.print(); // Draw the game board

    mario.draw(); // Draw Mario at its default position

	while (true) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            char key = _getch(); // Get the key input
            if (key == ESC) break; // Pause the game and open the menu
            // @ assign menu functionality to key

            mario.update_dir(key); // Update Mario's direction based on the key input
        }

        if (mario.is_dead()) { // Check if Mario is dead
            break; // End the game if Mario is dead
        } 
        else {
            mario.move(); // Move Mario if he is on a floor element
            ctrl_barrels(); // Control the barrels
            Sleep(100); // Delay for 100 milliseconds
        }
        frames++;
    }
}

/**
 * Initializes the barrels by setting their board pointers.
 */
void Game::init_barrels() {
    for (int i = 0; i < MAX_BARRELS; i++) {
        barrels[i].set_board(&org_board, &curr_board);
    }
}

/**
 * Moves all active barrels.
 */
void Game::move_barrels() {
    for (int i = 0; i < MAX_BARRELS; i++) {
        if (barrels[i].is_active()) {
            barrels[i].move();
        }
    }
}

/**
 * Controls the spawning and movement of barrels.
 * Spawns a new barrel every 30 frames.
 */
void Game::ctrl_barrels() {
	if (frames % 30 == 0) { // Spawn a new barrel every 30 frames
        for (int i = 0; i < MAX_BARRELS; i++) {
            if (!barrels[i].is_active()) {
				barrels[i].spawn(); // Spawn a new barrel
                break;
            }
        }
    }
	move_barrels(); // Move all active barrels
}

//test pull request