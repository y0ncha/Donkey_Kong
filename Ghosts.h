#pragma once
#include "Ghost.h"
#include <memory>

/**
 * @class Ghosts
 * Manages a collection of ghosts in the game.
 */
class Ghosts {

public:

    // Constructor for the Ghosts class
    Ghosts(const Board* pBoard);

    // copy constructor
    Ghosts(const Ghosts& other);

    // Custom copy assignment operator
    Ghosts& operator=(const Ghosts& other);

    // Default move constructor and move assignment operator
    Ghosts(Ghosts&&) noexcept = default;
    Ghosts& operator=(Ghosts&&) noexcept = default;

    // Method to move all ghosts
    void move_all();

    // Method to initialize all ghosts at the beginning of the level
    void set_all();

    // Method to reset all ghosts
    void reset_all();

	// method to set amount of ghosts
    void set_amount();

	// Method to check ghost collision
    void check_ghosts_collision() const;

	// Method to check if any ghost hit Mario
    bool hitted_mario() const;
    
private:

	// Number of ghosts
	size_t amount = 0; // Maximum number of ghosts

	// Flag to check if Mario was hit
	bool hit_mario = false;

	// Pointer to the game board
	const Board* board;

	// Vector to store the ghosts as unique pointers
	std::vector<std::unique_ptr<Ghost>> ghosts;
};



