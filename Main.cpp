#include <windows.h>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()
#include "Game.h"

/**
 * Main function that initializes the game and starts the game loop.
 */
int main() {

	// Seed the random number generator
	show_cursor(false);
	srand(static_cast<unsigned int>(time(nullptr))); // Explicit cast to unsigned int
	
	std::string nickname; // Variable to hold the player's nickname
	Game::Statistics game_stats; // Variable to hold the game statistics
	Display::Menu_Options input; // Variable to hold the user input

	// Get the player's nickname
	std::cout << "Enter your nickname: ";
	std::cin >> nickname;

	// while not intentionaly exited the game
	while (true) {
		Game my_game; // Create a new game instance
		input = Display::get_instance().main_menu(); // Display the main menu

		if (input != Display::Menu_Options::EXIT) {
			game_stats = my_game.start(); // Start the game and get the game statistics
			// write the game_stats to a file here !
		}
		else {
			break; // Exit the game
		}
	}
	

	return 0;
}

