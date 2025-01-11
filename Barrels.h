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
    Barrels(const Board* pBoard, Difficulty dif_lvl = EASY);

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

    // Checks if a barrel is in a given position and resets it if it is
    bool in_range(Coordinates& pos) ;

    enum consts {
        DEF_AMOUNT = 10,
        MED_AMOUNT = 15,
        HARD_AMOUNT = 20,

        DEF_INTERVAL = 30,
        MED_INTERVAL = 20,
        HARD_INTERVAL = 15,
    };

private:
    const Board* board; // Pointer to the game board
    int interval = DEF_INTERVAL; // Interval for spawning barrels
    int amount = DEF_AMOUNT; // Maximum number of barrels
    bool hit_mario = false; // Flag to check if Mario was hit

    // Vector to store the barrels (using unique pointers for future preparation)
    std::vector<std::unique_ptr<Barrel>> barrels;

};
