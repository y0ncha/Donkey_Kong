#include <windows.h>
#include <cstdlib> // Required for rand() and srand()
#include <ctime>   // Required for time()
#include "Game.h"

/**
 * Main function that initializes the game and starts the game loop.
 */
int main() {

	Game donkey_kong;
	donkey_kong.run();
	return 0;
}

