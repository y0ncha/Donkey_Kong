#pragma once
#include "Board.h"
#include "Entity.h"

// Barrel class inheriting from Entity
class Barrel : public Entity {

	bool hit_mario = false; // Indicates if the barrel hitted Mario
    bool active = false; // Indicates if the barrel is active

    int fall_count = 0; // Counter for the number of steps the barrel has been falling
    
	// Enum for the Barrel's status
    enum class Status {
        IDLE,
        FALLING,
    };

    Status status = Status::IDLE; // Current status of the Barrel

    // Method to handle the direction change when the Barrel is on different types of floors
    void update_dir(char bellow_barrel) override;

    // Handles collision logic for the Barrel (Override of Entity's handle_collision method)
    char handle_collision() override;

	// Handles the falling logic for the Barrel (Override of Entity's handle_falling method)
	void handle_falling() override;

    // Helper function to print explosion phase within a given radius
    void print_explosion_phase(int radius);

    // 
    void clear_explosion_phase(int radius);

public:

    // Constructor for the Barrel class
    Barrel(const Board* pBoard);

    // Enum for Barrel's related constants
    enum Consts {
        MAX_FALL_H = 8, // Maximum height of a fall
		EXPLOSION_RADIUS = 2, // Radius of the explosion
		EXPLOSION_DELAY = 100, // Delay between explosion phases
    };
    
    // Method to handle the movement logic of the Barrel (Override of Entity's move method)
    void move() override;

	// Checks if the Barrel hitted Mario
	bool hitted_mario() const;

    // Checks if the Barrel is active
    bool is_active() const;

    // Returns the initial position of the Barrel
    Coordinates init_pos();

    // Sets the original and current board for the Barrel
    void set_board(const Board* pBoard);

    // Spawns the Barrel at the initial position.
    void spawn();

	// Resets the Barrel status and direction.
    void reset() override;

	// Explodes the barrel.
	void explode();
};
