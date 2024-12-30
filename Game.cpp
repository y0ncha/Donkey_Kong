#include "Game.h"
#include "Level.h"
/**
 * @brief Constructor for the Game class.
 */
Game::Game() : mario(nullptr) {}

/**
 * @brief Starts the game loop and handles user input.
 */
void Game::start() {

	show_cursor(false); // Hide the console cursor for better visuals
	display.main_menu(*this);

	Level level(level_files[lvl_ind], display, mario, dif_lvl);

	while (status != EXIT) {

		switch (status) {
		case PAUSE:
			display.pause_menu(*this);
		case RUN:
			level.start();
			break;
		case FIN_FAIL:
			display.failure_messege();
			break;
		case FIN_SUC:
			if (lvl_ind < NOF_LEVELS - 1) {
				display.success_messege();
				status = Status::RUN;
				lvl_ind++;
			}
			else {
				display.success_messege();
				status = EXIT;
			}
			break;
		}
	}
	display.exit_messege();
}
