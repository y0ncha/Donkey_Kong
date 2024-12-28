#include "Barrels.h"

/**
 * @brief Constructor to initialize the Barrels class.
 * @param pBoard Pointer to the game board.
 * @param max_barrels Maximum number of barrels.
 * @param spawn_intvl Interval for spawning barrels.
 */
Barrels::Barrels(const Board* pBoard)
    : board(pBoard) {
    // Initialize the barrels with the board pointer
	barrels.reserve(DEF_AMOUNT);

    for (size_t i = 0; i < DEF_AMOUNT; i++) {
		barrels.emplace_back(std::make_unique<Barrel>(pBoard)); // Unique pointer used as a preperatuion for the next exercises
    }
}

/**
 * @brief Moves all active barrels and returns if Mario was hit.
 * @param frames The current frame count.
 */
void Barrels::move(int frames) {
    bool spawn_flag = false; // Flag to indicate if a new barrel should be spawned

    for (auto& barrel : barrels) {
        if (barrel->is_active()) { // If the barrel is active, move it
            barrel->move();

            if (barrel->hitted_mario()) {
                hit_mario = true;
                break;
            }
        } else if (frames % interval == 0 && !spawn_flag) { // If the barrel is not active and the interval has passed
            spawn_flag = true;
            barrel->spawn();
        }
    }
}

/**
 * @brief Resets the barrels.
 */
void Barrels::reset() {
    hit_mario = false;

    for (auto& barrel : barrels) {
        barrel->reset();
    }
}

/**
 * @brief Checks if Mario was hit by a barrel.
 * @return True if Mario was hit, false otherwise.
 */
bool Barrels::hitted_mario() const {
    return hit_mario;
}

/*
* @brief updates the barrels with the defficulty level prefrences
* @param max_barrels Maximum number of barrels.
* @param spawn_interval Interval for spawning barrels.
*/
void Barrels::update(int max_barrels, int spawn_interval) {

    amount = max_barrels;
    interval = spawn_interval;

    for (size_t i = DEF_AMOUNT; i < amount; i++) {
        barrels.emplace_back(std::make_unique<Barrel>(board));
    }
}