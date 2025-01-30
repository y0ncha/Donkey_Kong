#include "Save_Level.h"

/**
 * @brief Constructor for Save_Level
 * @param fname The file name of the level.
 * @param mario The Mario object.
 * @param dif_lvl The difficulty level.
 */
Save_Level::Save_Level(std::string screen, Mario& mario, Difficulty _diff) :
	Level_Base(screen, mario),
	steps(generate_fname("steps"), std::ios::out),
    result(generate_fname("result"), std::ios::out) {

	// Check if the files are open
	if (!steps.is_open()) {
		push_error(Board::Err_Code::STEPS_FAIL);
	}
	else {
		steps << static_cast<int>(diff) << std::endl; // Write the difficulty level to the steps file
		steps << seed << std::endl; // Write the seed to the steps file
	}

	if (!result.is_open()) {
		push_error(Board::Err_Code::RESULT_FAIL);
	}
}

Save_Level::~Save_Level() {
	
	steps << frames << " " << TERMINATOR << std::endl; // Write the terminator to the steps file

	steps.close();
	result.close();
}

/**
 * @brief Starts the level loop and saves the relevant data.
 * @param seed The seed for the random number generator.
 * @return The game state.
 */
Game_State Save_Level::start() {

    Game_State state = Game_State::RUN; // Variable to hold the game state
    char input; // Variable to hold the user input
    Ctrl key; // Variable to hold the key input

	//todo add screen for failure open steps 
	if (!steps.is_open()) return Game_State::TERMINATE;
	if (!result.is_open()) {};//todo add screen for failure open result
    render_level(); // Update the game screen

	while (state == Game_State::RUN) { // Main game loop

		if (_kbhit()) { // Check if a key is pressed
			input = _getch();
			key = static_cast<Ctrl>(input);

			if (key == Ctrl::ESC) { // If the key is ESC, open the pause menu
				return Game_State::PAUSE;
			}
			else if (key == Ctrl::HIT && mario.is_armed()) { // If the key is HIT, handle the hammer attack
				steps << frames << " " << input << std::endl;
				perform_attack();
			}
			else if (mario.update_dir(input)) { // If any other key is pressed
				steps << frames << " " << input << std::endl;
			}
		}
		state = advance_entities(); // Advance all the entities in the game
		if (is_result_action_required(state)) write_to_result(state);// Write the result to the file if needed
		Sleep(DEF_DELAY); // Delay for 100 milliseconds
		frames++; // Increment the frame counter
	}
	return state;
}

/**
 * @brief write the result to the file
 * @param game state The game state.
 */
void Save_Level::write_to_result(Game_State state)
{
	switch (state) {
	case Game_State::RETRY:
		result <<frames << " " << static_cast<char>(Result_Type::LIFE_LOST) << std::endl;
		break;
	case Game_State::SUCCESS:
		result << frames << " " << static_cast<char>(Result_Type::FINISH_SCREEN) << std::endl;
		result << mario.get_score() << " " << static_cast<char>(Result_Type::SCORE_GAINED) << std::endl;
		break;
	case Game_State::FAIL:
		result << frames << " " << static_cast<char>(Result_Type::LIFE_LOST) << std::endl;
		result << mario.get_score() << " " << static_cast<char>(Result_Type::SCORE_GAINED) << std::endl;
		break;
	}
}

