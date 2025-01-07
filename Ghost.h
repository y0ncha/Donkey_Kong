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
	void set_board(const Board* pBoard);
	// Method to reset the ghost
	void reset() override;
	// Method to check if the ghost is active
	bool is_active() const;
	// method to activate the ghost
	void activate();
	// Method to invert the direction of the ghost
	void invert_dir();
	// Method to check if the ghost hit Mario
	bool is_hit_mario() const;


private:
	// Method to check if the ghost next step is valid
	bool valid_move();

	//method to set the initial direction of the ghost
	Coordinates init_dir(); 

	void handle_falling() override; //not needed here

	//TODO add the following methods, and change the ghost hit_mario based on them
	char handle_collision() override; 

	void update_dir(char key = static_cast<char>(Ctrl::DEF)) override;
	
	bool active = false; // Flag to indicate if the ghost is active

};





