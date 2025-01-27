#pragma once
#include "Ghost_Base.h"

/**
 * @class Regular_Ghost
 * Represents a Regular_Ghost entity in the game.
 */
class Master_Ghost : public Ghost_Base {

public:
	// Constructor for the Regular_Ghost class
	Master_Ghost(const Board* pBoard);

	// Method to move the Regular_Ghost
	void move() override;

	// Method to clone the Regular_Ghost entity
	std::unique_ptr<Ghost_Base> clone() const override;

private:

	// State of the Regular_Ghost
	enum class State { IDLE, CLIMBING } state = State::IDLE;

	// Makes Regular_Ghost climb up
	void climb();

	// Checks if Regular_Ghost can climb down
	bool can_climb_down() const;

	// Checks if Regular_Ghost can climb up
	bool can_climb_up() const;

	// Checks if Regular_Ghost can start climb
	bool can_start_climb() const;

	// Checks if Regular_Ghost can climb
	bool can_climb() const;

	// Handles Regular_Ghost's climbing logic
	void handle_climbing();

};