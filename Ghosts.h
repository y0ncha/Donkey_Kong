#pragma once
#include "Ghost.h"
#include <memory>

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
	int amount = 0; // Maximum number of ghosts
	bool hit_mario = false; // Flag to check if Mario was hit
	const Board* board; // Pointer to the game board
	std::vector<std::unique_ptr<Ghost>> ghosts; // Vector to store the ghosts
};



