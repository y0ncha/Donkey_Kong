#pragma once

#include <vector>
#include "Barrel.h"
#include "Board.h"

/*
* The Barrels class represents a collection of barrels in the game.
* It controls the spawning, movement, and resetting of barrels.
*/
class Barrels {

public:
    // Constructor to initialize the Barrels class
    Barrels(const Board* pBoard, int max_barrels = 10, int spawn_intvl = 30);

    // Moves all active barrels and returns if Mario was hit
    void move(int frames);

    // Resets the barrels
    void reset();

	// Checks if Mario was hit by a barrel
	bool hitted_mario() const;

private:

    const Board* board; // Pointer to the game board

    std::vector<Barrel> barrels; // Vector of barrels

    int max_barrels; // Maximum number of barrels

    int spawn_intvl; // Interval for spawning barrels

	bool hit_mario = false; // Indicates if Mario was hit by a barrel
};
