#include "Game.h"

/**
 * Constructor to initialize the Game class with the board and Mario.
 * Also initializes the barrels.
 */
Game::Game() : mario(&board) {
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

    show_cursor(false); // Hide the console cursor for better visuals
    
    // Run the menu and check if the user wants to exit
    if (menu.run(Menu::START_MENU) == Menu::EXIT)
        return;
    
    board.print(); // Draw the game board

    mario.draw(); // Draw Mario at its default position

	while (mario.get_lives() > 0) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
          
            char key = _getch(); // Get the key input
          
            if (key == ESC) { // Pause the game and open the me
                if (menu.run(Menu::PAUSE_MENU) == Menu::EXIT)
                    break;
            } 
            mario.update_dir(key); // Update Mario's direction based on the key input
        }

        else {

            mario.move(); // move Mario if he is on a floor element
			move_barrels(); // move all active barrels

			if (mario.is_dead()) { // If Mario is DEAD
                reset_level();
			}
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
        barrels[i].set_board(&board);
    }
}

/**
 * Moves all active barrels.
 */
void Game::move_barrels() {
    for (int i = 0; i < MAX_BARRELS; i++) {
        if (barrels[i].is_active()) barrels[i].move();
   
    }
	spawn_barrels(); // Spawn a new barrel every 30 frames
}

/**
 * Controls the spawning and movement of barrels.
 * Spawns a new barrel every 30 frames.
 */
void Game::spawn_barrels() {
	if (frames % 30 == 0) { // Spawn a new barrel every 30 frames
        for (int i = 0; i < MAX_BARRELS; i++) {
            if (!barrels[i].is_active()) {
				barrels[i].spawn(); // Spawn a new barrel
                break;
            }
        }
    }
}

void Game::reset_barrels() {
    for (int i = 0; i < MAX_BARRELS; i++) {
        barrels[i].reset();
    }
}

void Game::reset_level() {
	board.print(); // Draw the game board
	mario.reset(); // Draw Mario at its default position
	reset_barrels();
	frames = 0;
}

