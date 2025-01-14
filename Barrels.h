#pragma once

#include <vector>
#include <memory>
#include "Barrel.h"
#include "Board.h"
#include "Config.h"

/**
 * @class Barrels
 * Manages a collection of barrels in the game.
 */
class Barrels {

public:
    // Constructor to initialize the Barrels class
    Barrels(const Board* pBoard, Difficulty dif_lvl = Difficulty::EASY);

    // Custom copy constructor
    Barrels(const Barrels& other);

    // Custom copy assignment operator
    Barrels& operator=(const Barrels& other);

    // Default move constructor and move assignment operator
    Barrels(Barrels&&) noexcept = default;
    Barrels& operator=(Barrels&&) noexcept = default;

    // Moves all active barrels and returns if Mario was hit
    void move_all(int frames);

    // Resets the barrels
    void reset_all();

    // Checks if Mario was hit by a barrel
    bool hitted_mario() const;

	// Checks if a barrel is in a given position
    void was_hit(Coordinates pos);

	// Map to store the default amount and interval for each difficulty level
    const std::unordered_map<Difficulty, std::pair<size_t, size_t>> difficulty = {
        { Difficulty::EASY, {10, 30} },
        { Difficulty::MEDIUM, {15, 20} },
        { Difficulty::HARD, {20, 15} }
    };

private:
    const Board* board; // Pointer to the game board
    size_t amount; // Maximum number of barrels
    size_t interval; // Interval for spawning barrels
    bool hit_mario = false; // Flag to check if Mario was hit

    // Vector to store the barrels (using unique pointers for future preparation)
    std::vector<std::unique_ptr<Barrel>> barrels;
};
