#include <windows.h>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()
#include "Game.h"

/**
 * Main function that initializes the game and starts the game loop.
 */
int main() {

	// Seed the random number generator
	srand(static_cast<unsigned int>(time(nullptr))); // Explicit cast to unsigned int
	
	Game my_game; // Create a new game instance
	std::string nickname; // Variable to hold the player's nickname
	Game::Statistics game_stats; // Variable to hold the game statistics

	// Get the player's nickname
	std::cout << "Enter your nickname: ";
	std::cin >> nickname;

	// Start the game loop
	game_stats = my_game.start();

	return 0;
}

