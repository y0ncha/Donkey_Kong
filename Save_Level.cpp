#include "Save_Level.h"

/**
 * @brief Constructor for Save_Level
 * @param fname The file name of the level.
 * @param mario The Mario object.
 * @param dif_lvl The difficulty level.
 */
Save_Level::Save_Level(std::string fname, Mario& mario, Difficulty diff, unsigned int seed) :
	Level_Base(fname, mario, diff),
	steps(generate_fname("steps"), std::ios::out),
    result(generate_fname("result"), std::ios::out) {

	// Check if the files are open
	if (!steps.is_open()) {
		push_error(Board::Err_Code::STEPS_FAIL);
	}
	if (!result.is_open()) {
		push_error(Board::Err_Code::RESULT_FAIL);
	}
	steps << static_cast<int>(diff) << std::endl; // Write the difficulty level to the steps file
	steps << seed << std::endl; // Write the seed to the steps file
}

Save_Level::~Save_Level() {
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
		Sleep(DEF_DELAY); // Delay for 100 milliseconds
		frames++; // Increment the frame counter
	}
	return state;
}


/**
 * @brief Gets the file name for the save file.
 * @param type The type of the file.
 * @return The file name.
 */
const std::string Save_Level::generate_fname(const std::string& type) {

	std::string fname = screen;

	fname = remove_ext(fname, ".screen.txt");
	fname += "." + type + ".txt";

	return fname;
}