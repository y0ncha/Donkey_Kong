#include "Barrels.h"

/**
 * Constructor to initialize the Barrels class.
 */
Barrels::Barrels(const Board* pBoard, int max_barrels, int spawn_interval)
    : board(pBoard), max_barrels(max_barrels), spawn_interval(spawn_interval) {
	// Initialize the barrels with the board pointer
    for (int i = 0; i < max_barrels; i++) {
        barrels.emplace_back(pBoard);
    }
}

/**
 * Moves all active barrels.
 */
void Barrels::move(int frames) {

    bool spawn_flag = false; // Flag to indicate if a new barrel should be spawned

    for (auto& barrel : barrels) {

		if (barrel.is_active()) { // If the barrel is active move it
            barrel.move();
        }
		else if (frames % spawn_interval == 0 && !spawn_flag) { // If the barrel is not active and the interval has passed
            spawn_flag = true;
            barrel.spawn();
        }
    }
}

/**
 * Resets the barrels.
 */
void Barrels::reset() {
    for (auto& barrel : barrels) {
        barrel.reset();
    }
}
