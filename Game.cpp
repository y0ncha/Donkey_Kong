#include "Game.h"

/**
 * @brief Constructor to initialize the Game class with the board and Mario.
 * Also initializes the barrels.
 */
Game::Game() : mario(&board), barrels(&board) {}

/**
 * @brief Starts the game loop.
 *
 * Initializes the game components, hides the console cursor, and begins the main game loop.
 * The loop listens for key inputs to control Mario and updates the game state.
 * Pressing the ESC key pauses the game and opens the menu.
 * @param max_barrels Maximum number of barrels.
 * @param spawn_interval Interval for spawning barrels.
 */
void Game::play() {

    show_cursor(false); // Hide the console cursor for better visuals
    status = Status::RUN;

    // Run the menu and check if the user wants to exit
    if (display.run(Display::START_MENU) == Display::EXIT) {
		status = Status::EXIT;
        display.exit_messege();
        return;
    }

	set_level(); // Set the game level based on the user's choice
    display.render_game(mario, board); // Update the game screen
    mario.set(); // Draw Mario at its default position

    while (mario.get_lives() > 0 && !mario.is_rescued_pauline()) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            handle_input(); // Handle the key input
            if (status == Status::EXIT) { // If the game status is exit
                display.exit_messege();
                return; // Exit the game
            }
        } else { // If no key is pressed
            advance_entities(); // Advance the entities in the game
            Sleep(Consts::DEF_DELAY); // Delay for 100 milliseconds
        }
        frames++; // Increment the frame counter
    }
}

/**
 * @brief Handles key input during the game.
 */
void Game::handle_input() {
    char key = _getch(); // Get the key input

    // If the key is ESC, open the pause menu
    if (key == ESC) { 
        if (display.run(Display::PAUSE_MENU) == Display::EXIT) { // Run the pause menu and check if the user wants to exit
            this->status = Status::EXIT; // Set the game status to exit
            return;
        }
        else
            display.render_game(mario, board); // Update the game screen
    } else {
        mario.update_dir(key); // Update Mario's direction based on the key input
    }
}

/**
 * @brief Resets the level and updates Mario's lives.
 */
void Game::reset_level() {
    Sleep(Consts::KILLED_DELAY); // Delay for 1 second
    mario.reset(); // Draw Mario at its default position
    barrels.reset(); // Reset the barrels
    frames = 0;
}

/**
 * @brief Advances the entities in the game.
 */
void Game::advance_entities() {
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
void Game::try_again() {
    reset_level(); // Reset the game
    clear_screen(); // Clear the screen
    display.strike_messege(); // Print the try again message

    display.render_game(mario, board); // Update the game screen
}

/**
 * @brief Finishes the game successfully.
 */
void Game::finish_success() {
    reset_level(); // Reset the game
    clear_screen(); // Clear the screen
    display.success_messege(); // Print the success message
}

/**
 * @brief Finishes the game with failure.
 */
void Game::finish_failure() {
    reset_level(); // Reset the game
    clear_screen(); // Clear the screen
    display.failure_messege(); // Print the exit message
}

/*
* @brief sets the game level
*/
void Game::set_level() {

    // Set the maximum number of barrels and the spawn interval based on the chosen level
    switch (display.levels_menu()) {

    case Display::MEDIUM: // Set the maximum number of barrels and the spawn interval for the MEDIUM level
		barrels.update(Barrels::MED_AMOUNT, Barrels::MED_INTERVAL);
        break;
    case Display::HARD: // Set the maximum number of barrels and the spawn interval for the HARD level
		barrels.update(Barrels::MED_AMOUNT, Barrels::HARD_INTERVAL);
        break;
    default: // Default to EASY (already set to the default values)
        break;
    }
}