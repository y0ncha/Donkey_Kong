#include "Game.h"

/**
 * @brief Constructor for the Game class.
 */
Game::Game() 
    : mario(nullptr), display(Display::get_instance(this)) {}

/**
 * @brief Starts the game loop and handles user input.
 * @return The game state after the game loop ends (FIN_SUC, FIN_FAIL, TERMINATE).
 */
Game_State Game::start() {

    show_cursor(false); // Hide the console cursor for better visuals
    display.main_menu();

    // Dynamic allocation to ease the level incrementation and to initiate level only after all the needed data is available
    curr_level = std::make_unique<Level>(level_files[lvl_ind], mario, dif_lvl);

    while (state != TERMINATE) {
		// Main game loop mamging the different states of the game
        switch (state) {
		case RUN: // Run the game
            state = curr_level->start();
            break;
		case PAUSE: // Pause the game
            display.pause_menu();
            break;
		case LVL_RESET: // Reset the level
			curr_level->reset_level();
            display.strike_messege();
			state = RUN;
            break;
		case FIN_FAIL: // Finish the game unsuccessfully
            curr_level->reset_level();
            display.failure_messege();
            state = TERMINATE;
            break;
		case FIN_SUC: // Finish the game successfully
            curr_level->reset_level();
			if (lvl_ind < NOF_LEVELS - 1) { // Check if there are more levels
                display.success_messege(); // todo change to fin game and fin level
                state = RUN;
                //lvl_ind++;
                // todo advance level
			}
			else { // If all the levels are finished, exit the game
                display.success_messege(); // todo change to fin game and fin level
                state = TERMINATE;
            }
            break;
        }
    }
    display.exit_messege();
	return state;
}

/**
 * @brief Validates and sets the game status.
 * @param stat The status to set.
 */
bool Game::set_state(Game_State _state) {
    switch (_state) {
    case TERMINATE:
    case RUN:
    case PAUSE:
    case LVL_RESET:
    case FIN_FAIL:
    case FIN_SUC:
    case IDLE:
        state = _state;
        return true;
    default:
        return false;
    }
}

/**
 * @brief Gets the game status.
 */
Game_State Game::get_state() const {
    return state;
}

/**
 * @brief Validate and sets the game difficulty.
 * @param dif The difficulty to set.
 */
bool Game::set_difficulty(Difficulty dif) {

    switch (dif) {
    case EASY:
    case MEDIUM:
    case HARD:
        dif_lvl = dif;
        return true;
    default:
        return false;
    }
}

/**
 * @brief Gets the game difficulty.
 */
Difficulty Game::get_difficulty() const {
    return dif_lvl;
}

/**
 * @brief Validate and sets the level index.
 * @param ind The indemenagifull name for x to set.
 */
bool Game::set_level(short ind) {
    if (0 <= ind && ind < NOF_LEVELS) {
        lvl_ind = ind;
        return true;
    }
    return false;
}

/**
 * @brief Gets the number of lives Mario has left.
 * @return The number of lives left.
 */
int Game::get_mario_lives() const {
    return mario.get_lives();
}
