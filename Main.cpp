#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Config.h"
#include "Game.h"

// Process the input arguments and return the game mode
Game_Mode process_input(int argc, char* argv[]);

/**
 * Main function that initializes the game and starts the game loop.
 */
int main(int argc, char* argv[]) {

	// Process the input arguments
	Game_Mode mode;
	mode = process_input(argc, argv);

	// Check if the mode is invalid
	if (mode == Game_Mode::INVALID) {
		return 1;
	}

	// Create the game object and run the it
	Game donkey_kong(mode);
	donkey_kong.run();

	return 0;

}

/**
 * @brief Processes the input arguments and returns the game mode.
 * @param argc The number of arguments.
 * @param argv The arguments.
 * @return The game mode.
 */
Game_Mode process_input(int argc, char* argv[]) {

	Game_Mode mode = Game_Mode::INVALID;
	std::string arg = argc > 1 ? std::string(argv[1]) : empty;

	if (arg == empty) {
		mode = Game_Mode::REGULAR;
	}
	else if (arg == "-save") {
		std::cout << "Running in SAVE mode." << std::endl;
		mode = Game_Mode::SAVE;
	}
	else if (arg == "-load") {

		arg = argc > 2 ? std::string(argv[2]) : "";

		if (arg == "-silent") {
			std::cout << "Running in LOAD mode (silent)." << std::endl;
			mode = Game_Mode::SILENT;
		}
		else {
			std::cout << "Running in LOAD mode." << std::endl;
			mode = Game_Mode::LOAD;
		}
	}
	else {
		std::cout << "Invalid or missing arguments. Usage: dkong.exe -load | -save [-silent]" << std::endl;
		mode = Game_Mode::INVALID;
	}
	return mode;
}