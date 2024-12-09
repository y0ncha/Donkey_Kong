#include "Game.h"

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
    if (menu.run(START_MENU) == EXIT)
        return;

    int i = 0;
    
    org_board.print(); // Draw the game board

    mario.draw(); // Draw Mario at its default position

    while (true) {

        i++;

        if (_kbhit()) { // Check if a key is pressed

            char key = _getch(); // Get the key input
            if (key == ESC)// Pause the game and open the menu
            {
                if (menu.run(PAUSE_MENU) == EXIT)
                    break;
            } 
			

            mario.update_dir(key); // Update Mario's direction based on the key input
        }
        mario.move(); // Move Mario if he is on a floor element
		Sleep(100); // Delay for 100 milliseconds
    }
}


