#include "Play_Game.h"

/**
 * @brief Runs the Play_Game and saves the statistics. ( will be used to save a Play_Game in Ex.3)
 */
void Play_Game::run() {

	show_cursor(false); // Seed the random number generator
	clear_screen(); // Clear the screen
	gotoxy(0, 0); // Move the cursor to the top left corner

	// Main Play_Game loop
	while (display.main_menu() != Display::Menu_Options::EXIT) {
		start();
		hall_of_fame.record_statistics(stats);
		reset();
	}
	// Display the exit message
	display.exit_message();
}

/**
 * @brief Starts the Play_Game loop and handles user input.
 * @return The Play_Game state after the Play_Game loop ends (FIN_SUC, FIN_FAIL, TERMINATE).
 */
void Play_Game::start() {

	// Start the timer
	auto start_t = start_timer();

	// Main Play_Game loop
	while (state != Game_State::TERMINATE) {
		// Main Play_Game loop mamging the different states of the Play_Game
		switch (state) {
		case Game_State::RUN: // Run the Play_Game
			handle_run();
			break;
		case Game_State::PAUSE: // Pause the Play_Game
			handle_pause();
			break;
		case Game_State::RETRY: // Reset the level
			handle_retry();
			break;
		case Game_State::FAIL: // Finish the Play_Game unsuccessfully
			handle_fail(start_t);
			break;
		case Game_State::SUCCESS: // Finish the Play_Game successfully
			handle_success(start_t);
			break;
		case Game_State::EXIT: // Exit the Play_Game
			handle_exit(start_t);
			break;
		default: // Do nothing if the state is not valid
			break;
		}
	}
}

/**
 * @brief Handles the Play_Game exit.
 * @param start_t The start time of the Play_Game.
 */
void Play_Game::handle_exit(std::chrono::steady_clock::time_point start_t) {
	stats.time_played = stop_timer(start_t);
	update_statistics();
	state = Game_State::TERMINATE;
}

/**
 * @brief Handles the Play_Game run.
 */
void Play_Game::handle_run() {

	Game_State state;

	if (curr_level == nullptr) {
		advance_level();
	}
	if (level_ind < screens.size()) {
		state = curr_level->start();
		set_state(state);
	}
}

/**
 * @brief Handles the Play_Game pause.
 */
void Play_Game::handle_pause() {
	display.pause_menu();
}

/**
 * @brief Handles the Play_Game retry.
 */
void Play_Game::handle_retry() {
	curr_level->retry_level();
	display.strike_message();
	state = Game_State::RUN;
}

/**
 * @brief Handles the Play_Game failure.
 * @param start_t The start time of the Play_Game.
 */
void Play_Game::handle_fail(std::chrono::steady_clock::time_point start_t) {
	stats.time_played = stop_timer(start_t);
	update_statistics();
	display.failure_message();
	state = Game_State::TERMINATE;
}

/**
 * @brief Handles the Play_Game success.
 * @param start_t The start time of the Play_Game.
 */
void Play_Game::handle_success(std::chrono::steady_clock::time_point start_t) {

	if (advance_level()) {
		display.success_message();
		state = Game_State::RUN;
	}
	else {
		set_state(Game_State::TERMINATE);
		stats.time_played = stop_timer(start_t);
		mario.update_score(Points::GAME_COMPLETE);
		update_statistics();
		display.winning_message();
	}
}

/**
 * @brief Sets the level.
 * @param screen The level file name.
 * @return True if the level was set, false otherwise.
 */
bool Play_Game::load_level(const std::string& screen) {
	// Free the current level
	curr_level.reset();

	// Check if the screen is empty
	if (screen.empty()) return false;

	if (mode == Game_Mode::REGULAR) {
		curr_level = std::make_unique<Regular_Level>(screen, mario, diff);
	}
	else if (mode == Game_Mode::SAVE) {
		curr_level = std::make_unique<Save_Level>(screen, mario, diff);
	}
	else {
		return false;
	}

	// If non of the above or the allocation failed return false
	return curr_level != nullptr;
}

/**
 * @brief Advances to the next level.
 * @param screen The filename of the next level.
 */
bool Play_Game::advance_level() {

	std::string screen;
	std::vector<Board::Err_Code> errors;

	// Check if the level is valid
	if (level_ind < screens.size()) {
		screen = pop_screen(level_ind);
		errors = set_level(screen);
	}
	else {
		set_state(Game_State::SUCCESS);
		return false;
	}

	// Validate the level, while invalid keep advancing
	while (!errors.empty()) {

		display.error_message(errors);
		level_ind++;
		// Check if the level is valid
		if (level_ind < screens.size()) {
			screen = pop_screen(level_ind);
			errors = set_level(screen);
		}
		else {
			set_state(Game_State::SUCCESS);
			return false;
		}
	}
	level_ind++;
	return true;
}
