#include "Barrels.h"

/**
 * Constructor to initialize the Barrels class.
 */
Barrels::Barrels(const Board* pBoard, int max_barrels, int spawn_intvl)
    : board(pBoard), max_barrels(max_barrels), spawn_intvl(spawn_intvl) {
    // Initialize the barrels with the board pointer
    for (int i = 0; i < max_barrels; i++) {
        barrels.emplace_back(pBoard);
    }
}

/**
 * Moves all active barrels and returns if Mario was hit.
 */
void Barrels::move(int frames) {

    bool spawn_flag = false; // Flag to indicate if a new barrel should be spawned

    for (auto& barrel : barrels) {

        if (barrel.is_active()) { // If the barrel is active move it

            barrel.move();

            if (barrel.hitted_mario()) {
                hit_mario = true;
                break;
            }
        } 
        else if (frames % spawn_intvl == 0 && !spawn_flag) { // If the barrel is not active and the interval has passed
            spawn_flag = true;
            barrel.spawn();
        }
    }
}

/**
 * Resets the barrels.
 */
void Barrels::reset() {

	hit_mario = false;

    for (auto& barrel : barrels) {
        barrel.reset();
    }
}

/**
 * Checks if Mario was hit by a barrel.
 */
bool Barrels::hitted_mario() const {
    return hit_mario;
}