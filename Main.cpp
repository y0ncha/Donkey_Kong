#include <windows.h>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()
#include "Game.h"

/**
 * Main function that initializes the game and starts the game loop.
 */
void main() {
	srand((time_t)time(nullptr)); // Seed the random number generator
	Game myGame; // Initialize the game
	myGame.play();
}

