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

	// Initialize the game
	Game my_game; 
	my_game.start();

	return 0;
}

