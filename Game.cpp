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
			handle_input(); // Handle the key input
        }
		else { // If no key is pressed
			advance_entities(); // Advance the entities in the game
            Sleep(100); // Delay for 100 milliseconds
        }
		frames++; // Increment the frame counter
    }
    
}

void Game::handle_input() {

    char key = _getch(); // Get the key input

	if (key == ESC) { // If the key is ESC, open the pause menu
        if (menu.run(Menu::PAUSE_MENU) == Menu::EXIT)
			return;
	}
    else {
        mario.update_dir(key); // Update Mario's direction based on the key input
    }
}
/*
* Resets the level and updates mari's lives.
*/
void Game::reset_level() {
	Sleep(1000); // Delay for 1 second
	mario.reset(); // Draw Mario at its default position
	barrels.reset(); // Reset the barrels
    frames = 0;

    // todo print success screen
	clear_screen(); // Clear the screen
    std::cout << "###PRINT RESET SCREEN###" << std::endl; // Print the reset message (opiional "press key to continue")
	Sleep(1000); // Delay for 1 second

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

/**
 * Updates the game screen by printing the board and the game data.
 */
void Game::print_screen() const {
	board.print(); // Draw the game board
	print_data(); // Update the lives display
}

/**
 * Advances the entities in the game.
 */
void Game::advance_entities() {
    mario.move(); // move Mario if he is on a floor element
    barrels.move(frames); // Move the barrels

    if (mario.is_hit() || barrels.hitted_mario()) { // Check if Mario was hit by a barrel
        reset_level(); // Reset the level if Mario was hit
    }
	else if (mario.is_rescued_pauline()) { // Check if Mario saved Pauline
        finish_success(); // Finish the game successfully
    }
}

/*
* Finish the game successfully.
*/
void Game::finish_success() {
	// todo print success screen
	clear_screen(); // Clear the screen
	std::cout << "###PRINT SUCCESS SCREEN###" << std::endl; // Print the success message
}

void Game::finish_failure(){
	// todo print failure screen
	clear_screen(); // Clear the screen
	std::cout << "###PRINT FAILURE SCREEN###" << std::endl; // Print the success message
}