#pragma once
#include "Entity.h"
#include "Board.h"

/**
 * @class Ghost
 * Represents a ghost entity in the game.
 */
class Ghost : public Entity {

public:

	// Constructor for the Ghost class
	Ghost(const Board* pBoard = nullptr);

	// Method to move the ghost
	void move() override;

	// Method to reset the ghost
	void reset();

	// Method to kill the ghost
	void kill();

	// Method to check if the ghost is active
	bool is_active() const;

	// method to activate the ghost
	void activate();

	// Method to check if the ghost hit Mario
	bool is_hit_mario() const;

	// Method to set the direction of the ghost
	void set_dir(Coordinates coord);

private:

	// Flag to indicate if the ghost is active
	bool active = false;

	// Method to check if the ghost next step is valid
	bool valid_move();

	// Method to initialize the direction of the ghost
	Coordinates init_dir(); 

	// Empty implementation of handle_falling
	void handle_falling() override;

	// Empty implementation of handle_collision
	char handle_collision() override; 

	// Method to update the direction of the ghost
	void update_dir(char key = static_cast<char>(Ctrl::DEF)) override;
};





