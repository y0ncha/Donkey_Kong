#include "Silent_Level.h"

/**
 * @brief Constructor for the Silent_Level class.
 * @param
 */
Silent_Level::Silent_Level(std::string screen, Mario& mario) : Visual_Level(screen, mario) {
	display_flag = false; // Set the display flag to false
}

/**
 * @brief Starts the Silent_Level loop.
 * @return The game state.
 */
Game_State Silent_Level::start() {

	Game_State state = Game_State::RUN; // Variable to hold the game state
	char input; // Variable to hold the user input
	Ctrl key; // Variable to hold the key input

	if (!steps_file_open()) return handle_steps_isnt_open(Game_Mode::SILENT);
	if (!result_file_open() && !res_message_appear) handle_result_isnt_open(Game_Mode::SILENT);

	render_level(); // Update the game screen

	while (state == Game_State::RUN) { // Main game loop

		if (frames == next_step.first) {

			input = tolower(next_step.second);
			key = static_cast<Ctrl>(input);

			if (input == TERMINATOR) {
				state = Game_State::EXIT;
				break;
			}
			else if (key == Ctrl::HIT && mario.is_armed()) {
				perform_attack(); // Handle the hammer attack
			}
			else {
				mario.update_dir(input); // If any other key is pressed
			}
			next_step = read_next(File_Type::STEPS);
		}
		state = advance_entities(); // Advance all the entities in the game
		if (result_file_open()&& is_result_action_required(state)) {
			check_result(state);
			if (next_res.second != static_cast<char>(Result_Type::SCORE_GAINED))
				next_res = read_next(File_Type::RES);
		}
		frames++; // Increment the frame counter
	}
	if (level_success && (state == Game_State::EXIT || state == Game_State::FAIL))
		state = Game_State::SUCCESS;

	if (state == Game_State::EXIT || state == Game_State::FAIL || state == Game_State::SUCCESS)
		push_remaining_results();

	return state;
}

/**
 * @brief Performs and hammer attack.
 */
void Silent_Level::perform_attack() {

	Coordinates pos = mario.get_dest(); // Get the next position of Mario
	Coordinates dir = mario.get_dir(); // Get the direction of Mario
	Point enemy = is_enemy_hit(pos, dir);

	if (enemy.icon == Board::BARREL) {
		barrels.was_hit(enemy.pos);
		mario.update_score(Points::ENEMY_HIT);// Update the score by 10 points
	}
	else if (enemy.icon == Board::Regular_Ghost) {
		ghosts.was_hit(enemy.pos);
		mario.update_score(Points::ENEMY_HIT); // Update the score by 10 points
	}
}

/**
 * @brief Advances the entities in the game.
 */
Game_State Silent_Level::advance_entities() {
	mario.move(); // Move Mario if he is on a floor element
	barrels.move_all(frames); // Move the barrels
	ghosts.move_all(); // Move the ghosts
	// If Mario is armed and remove the hammer from the board
	if (mario.is_armed()) board.remove_hammer();
	return calc_state(); // Calculate the game state
}

/**
* @brief Renders the Level_Base by drawing the board, Mario, and the HUD.
*/
void Silent_Level::render_level() {
	board.print(current_screen); // Draw the game board
	mario.set(); // Draw Mario
	ghosts.set_all(); // Draw the ghosts
}