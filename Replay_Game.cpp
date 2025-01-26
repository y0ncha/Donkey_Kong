#include "Replay_Game.h"
#include "Visual_Level.h"
#include "Silent_Level.h"

/**
 * @brief Starts the Replay_Game loop.
 */
void Replay_Game::run() {

	show_cursor(false); // Seed the random number generator
	set_state(Game_State::RUN);

	start();
	reset();

	display.exit_message(); // Display the exit message
}

/**
 * @brief Starts the Replay_Game loop and handles file input.
 */
void Replay_Game::start() {
	
	auto start_t = start_timer(); // Start the timer

	while (state != Game_State::TERMINATE) { // Main Game_Base loop
		switch (state) { // Main Game_Base loop managing the different states of the Game_Base
		case Game_State::RUN: // Run the Game_Base
			handle_run();
			break;
		case Game_State::RETRY: // Reset the level
			handle_retry();
			break;
		case Game_State::FAIL: // Finish the Game_Base unsuccessfully
			handle_fail(start_t);
			break;
		case Game_State::SUCCESS: // Finish the Game_Base successfully
			handle_success(start_t);
			break;
		case Game_State::EXIT: // Exit the Game_Base
			handle_exit(start_t);
			break;
		default: // Do nothing if the state is not valid
			break;
		}
	}
}

/**
 * @brief Handles the RUN state 
 */
void Replay_Game::handle_run() {

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
 * @brief Handles the RETRY state
 */
void Replay_Game::handle_retry() {
	curr_level->retry_level();
	display.strike_message(MSG_DELAY);
	state = Game_State::RUN;
}

/**
 * @brief Handles the FAIL state
 * @param start_t The start time of the Game_Base.
 */
void Replay_Game::handle_fail(std::chrono::steady_clock::time_point start_t) {
	stats.time_played = stop_timer(start_t);
	update_statistics();
	display.failure_message(MSG_DELAY);
	state = Game_State::TERMINATE;
}

/**
 * @brief Handles the SUCCESS state
 * @param start_t The start time of the Game_Base.
 */
void Replay_Game::handle_success(std::chrono::steady_clock::time_point start_t) {
	if (advance_level()) {
		display.success_message(MSG_DELAY);
		state = Game_State::RUN;
	}
	else {
		set_state(Game_State::TERMINATE);
		stats.time_played = stop_timer(start_t);
		mario.update_score(Points::GAME_COMPLETE);
		update_statistics();
		display.winning_message(MSG_DELAY);
	}
}

/**
 * @brief Handles the EXIT state
 * @param start_t The start time of the Game_Base.
 */
void Replay_Game::handle_exit(std::chrono::steady_clock::time_point start_t) {
	stats.time_played = stop_timer(start_t);
	update_statistics();
	state = Game_State::TERMINATE;
}

/**
 * @brief Loads the level from the specified file.
 * @param screen The filename of the level to load.
 * @return True if the level was loaded, false otherwise.
 */
bool Replay_Game::load_level(const std::string& screen) {

    curr_level.reset(); // Free current level

	if (screen.empty()) return false;

	if (mode == Game_Mode::LOAD) {
		curr_level = std::make_unique<Visual_Level>(screen, mario);
	}
	else if (mode == Game_Mode::SILENT) {
		//curr_level = std::make_unique<Silent_Level>(screen, mario);
	}
	else {
		return false;
	}

    return curr_level != nullptr;
}

/**
 * @brief Advances to the next level.
 * @param screen The filename of the next level.
 */
bool Replay_Game::advance_level() {

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