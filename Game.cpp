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
    
    // Run the menu and check if the user wants to exit
    if (menu.run(Menu::START_MENU) == Menu::EXIT)
        return;

    int i = 0;
    
    org_board.print(); // Draw the game board

    mario.draw(); // Draw Mario at its default position

	while (true) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
          
            char key = _getch(); // Get the key input
          
            if (key == ESC) { // Pause the game and open the me
                if (menu.run(Menu::PAUSE_MENU) == Menu::EXIT)
                    break;
            } 
            mario.update_dir(key); // Update Mario's direction based on the key input
        }

        if (mario.is_dead()) { // Check if Mario is dead
            break; // todo reset function
        } 
        else {

			if (mario.curr_dest() == Board::BARREL || curr_board.get_char(mario.get_pos()) == Board::BARREL) { // Check if Mario has hit a barrel
				mario.kill(); // Kill Mario
				break;
			}
            mario.move(); // Move Mario if he is on a floor element
			spawn_barrels(); // Spawn a new barrel every 30 frames

			if (!move_barrels()) break; // Move all active barrels
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
bool Game::move_barrels() {
    for (int i = 0; i < MAX_BARRELS; i++) {
        if (barrels[i].is_active()) {

			if (barrels[i].curr_dest() == Board::MARIO || curr_board.get_char(barrels[i].get_pos()) == Board::MARIO) { // Check if the barrel has hit Mario
				mario.kill(); // Kill Mario
                return false;
			}
            else {
                barrels[i].move();
            }
        }
    }
	return true;
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
