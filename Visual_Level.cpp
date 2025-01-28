#include "Visual_Level.h"



/**
 * @brief Constructor for the Visual_Level class.
 * @param
 */
Visual_Level::Visual_Level(std::string screen, Mario& mario) :
	Level_Base(screen, mario), 
	steps(generate_fname("steps"), std::ios::in),
	result(generate_fname("result"), std::ios::in) {

	if (!steps.is_open()) {
		push_error(Board::Err_Code::STEPS_FAIL);
	}
	else {
		steps >> diff;
		steps >> seed;
		next_step = read_next();
	}
	if (!result.is_open()) {
		push_error(Board::Err_Code::RESULT_FAIL);
	}
	else {
		result.close();
	}
	srand(seed);
}

/**
 * @brief Destructor for the Visual_Level class.
 */
Visual_Level::~Visual_Level() {
	steps.close();
	result.close();
}

/**
 * @brief Starts the level loop.
 * @return The game state.
 */
Game_State Visual_Level::start() {

	Game_State state = Game_State::RUN; // Variable to hold the game state
	char input; // Variable to hold the user input
	Ctrl key; // Variable to hold the key input

	if (!steps.is_open()) return Game_State::TERMINATE; // todo check if result needs to be open
	render_level(); // Update the game screen

	while (state == Game_State::RUN) { // Main game loop

		if (frames == next_step.first) {
			input = std::tolower(next_step.second);
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
			next_step = read_next();
		}
		state = advance_entities(); // Advance all the entities in the game
		Sleep(DEF_DELAY); // Delay for 100 milliseconds
		frames++;
	}
	return state;
}

/**
 * @brief Reads the next step from the file.
 * @return The next step.
 */
std::pair<int, char> Visual_Level::read_next() {
	std::pair<int, char> next_step;
	if (steps.is_open()) {
		steps >> next_step.first >> next_step.second;
	}
	return next_step;
}



