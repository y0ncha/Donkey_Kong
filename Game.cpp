#include "Game.h"

/**
 * Starts the game loop.
 *
 * Initializes the game components, hides the console cursor, and begins the main game loop.
 * The loop listens for key inputs to control Mario and updates the game state.
 * Pressing the ESC key pauses the game and opens the menu.
 */
void Game::play() {
  
    Menu menu;

    int selectedValue = menu.run();

    if (selectedValue == EXIT) 
        return;

    int i = 0;
    
    ShowConsoleCursor(false); // Hide the console cursor for better visuals

    org_board.print(); // Draw the game board

    mario.draw(); // Draw Mario at its default position

    while (true) {

        i++;

        if (_kbhit()) { // Check if a key is pressed

            char key = _getch(); // Get the key input
            if (key == ESC) break; // Pause the game and open the menu
			// @ assgin menu functionality to key

            mario.update_dir(key); // Update Mario's direction based on the key input
        }
        mario.move(); // Move Mario if he is on a floor element
		Sleep(100); // Delay for 100 milliseconds
    }
}


