#include "Game.h"

/**
 * Constructor to initialize the Game class with the board and Mario.
 * Also initializes the barrels.
 */
Game::Game() : mario(&board), barrels(&board) {}

/**
 * Starts the game loop.
 *
 * Initializes the game components, hides the console cursor, and begins the main game loop.
 * The loop listens for key inputs to control Mario and updates the game state.
 * Pressing the ESC key pauses the game and opens the menu.
 */
void Game::play(int max_barrels, int sapwn_interval) {

    show_cursor(false); // Hide the console cursor for better visuals
    
    // Run the menu and check if the user wants to exit
    if (menu.run(Menu::START_MENU) == Menu::EXIT)
        return;
    
	print_screen(); // Update the game screen

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
			barrels.move(frames); // Move the barrels

			if (mario.is_dead()) { // If Mario is DEAD
                reset_level();
			}
            Sleep(100); // Delay for 100 milliseconds
        }
        frames++; // 
    }
}

void handle_input() {
}
/*
* Resets the level
*/
void Game::reset_level() {

	mario.reset(); // Draw Mario at its default position
	barrels.reset(); // Reset the barrels
    frames = 0;

	print_screen(); // Update the game screen
}

/**
 * Updates the lives display by printing the hearts in the right location.
 */
void Game::print_data() const {

	int n = mario.get_lives(); // Get the number of lives Mario has left
    gotoxy(Board::HRTS_DISP_X, Board::HRTS_DISP_Y); // Move the cursor to the position where lives are displayed

    // Print the lives
    for (int i = 0; i < n; ++i) {
        std::cout << "<3 ";
    }
}

void Game::print_screen() const {
	board.print(); // Draw the game board
	print_data(); // Update the lives display
}

