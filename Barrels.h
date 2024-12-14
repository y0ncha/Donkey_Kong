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
    Barrels(const Board* pBoard, int max_barrels = 10, int spawn_intvl = 30);

    // Moves all active barrels and returns if Mario was hit
    void move(int frames);

    // Resets the barrels
    void reset();

    // Checks if Mario was hit by a barrel
    bool hitted_mario() const;

private:
    // Pointer to the game board
    const Board* board;

    // Vector to store the barrels
    std::vector<std::unique_ptr<Barrel>> barrels;

    // Maximum number of barrels
    int max_barrels;

    // Interval for spawning barrels
    int spawn_intvl;

    // Flag to check if Mario was hit
    bool hit_mario = false;
};
