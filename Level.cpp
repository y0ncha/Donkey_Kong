#include "Level.h"

/**
 * @brief Constructor for the Level class.
 * @param filename The name of the file that holds the board layout.
 * @param mario The Mario object.
 * @param display The Display object.
 */
Level::Level(std::string fname, const Game::Display& display, Mario& mario, Game::Difficulty dif_lvl)
    : display(display), mario(mario), barrels(&board, dif_lvl) {
	board.load(fname); // Load the board layout from the file
    mario.set_board(&board);
}

/**
 * @brief Advances to the next level by resetting and loading the new board.
 * @param next_level_file The name of the file that holds the next board layout.
 */
void Level::advance_level(const std::string& fname) {
    
    board.load(fname); // Load the new board layout from the file
    reset_level(); // Reset the current level
}

/**
 * @brief Starts the game loop.
 */
Game::Status Level::start() {

	Game::Status status = Game::RUN; // Set the game status to RUN
    char key;

    display.render_level(mario, board); // Update the game screen

    while (status == Game::RUN) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            key = _getch();

			if (key == ESC) { // If the key is ESC, open the pause menu
				status = Game::PAUSE;
			}
			else {
				mario.update_dir(key); // Update Mario's direction based on the key input
			}
        }
        advance_entities(); // Advance all the entities in the game
        Sleep(Consts::DEF_DELAY); // Delay for 100 milliseconds
        frames++; // Increment the frame counter
    }
	return status;
}

/**
 * @brief Resets the level and updates Mario's lives.
 */
void Level::reset_level() {

    Sleep(Consts::KILLED_DELAY); // Delay for 1 second
    mario.reset(); // Draw Mario at its default position
    barrels.reset(); // Reset the barrels
    frames = 0;
}

/**
 * @brief Advances the entities in the game.
 */
void Level::advance_entities() {
    mario.move(); // Move Mario if he is on a floor element
    barrels.move(frames); // Move the barrels

    if (mario.is_hit() || barrels.hitted_mario()) { // Check if Mario was hit by a barrel
        mario.get_lives() > 1 ? try_again() : finish_failure(); // Reset the level if Mario has more lives, else finish the game
    } else if (mario.is_rescued_pauline()) { // Check if Mario saved Pauline
        finish_success(); // Finish the game successfully
    }
}

/**
 * @brief Handles the logic for trying again after Mario is hit.
 */
void Level::try_again() {
    reset_level(); // Reset the game
    clear_screen(); // Clear the screen
    display.strike_messege(); // Print the try again message

    display.render_level(mario, board); // Update the game screen
}

/**
 * @brief Finishes the game successfully.
 */
void Level::finish_success() {
    reset_level(); // Reset the game
    clear_screen(); // Clear the screen
    display.success_messege(); // Print the success message
}

/**
 * @brief Finishes the game with failure.
 */
void Level::finish_failure() {
    reset_level(); // Reset the game
    clear_screen(); // Clear the screen
    display.failure_messege(); // Print the exit message
}
