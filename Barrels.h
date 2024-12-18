#pragma once

#include <vector>
#include <memory>
#include "Barrel.h"
#include "Board.h"

/**
 * @class Barrels
 * Manages a collection of barrels in the game.
 */
class Barrels {

public:
    // Constructor to initialize the Barrels class
    Barrels(const Board* pBoard);

    // Moves all active barrels and returns if Mario was hit
    void move(int frames);

    // Resets the barrels
    void reset();

    // Checks if Mario was hit by a barrel
    bool hitted_mario() const;

	// Initializes the barrels with the defficulty level
    void update(int max_barrels, int spawn_interval);

    enum consts {
		DEF_AMOUNT = 10,
		MED_AMOUNT = 15,
		HARD_AMOUNT = 20,

		DEF_INTERVAL = 30,
		MED_INTERVAL = 20,
		HARD_INTERVAL = 15,
    };

private:

	// Vector to store the barrels (using unique pointers for fututere preperation)
    std::vector<std::unique_ptr<Barrel>> barrels;

    const Board* board; // Pointer to the game board
    int amount = DEF_AMOUNT;  // Maximum number of barrels
    int interval = DEF_INTERVAL; // Interval for spawning barrels
    bool hit_mario = false; // Flag to check if Mario was hit
};
