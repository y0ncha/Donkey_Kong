#pragma once
#include "Ghost_Base.h"

/**
 * @class Master_Ghost
 * Represents a Master_Ghost entity in the game.
 */
class Master_Ghost : public Ghost_Base {

public:
	// Constructor for the Master_Ghost class
	Master_Ghost(const Board* pBoard);

	// Method to move the Master_Ghost
	void move() override;

	// Method to clone the Master_Ghost entity
	std::unique_ptr<Ghost_Base> clone() const override;

	// Method to reset the Master_Ghost
	void reset() override;

private:

	// State of the Master_Ghost
	enum class State { IDLE, CLIMBING } state = State::IDLE;

	// Makes Master_Ghost climb up
	void climb();

	// Checks if Master_Ghost can climb down
	bool can_climb_down() const;

	// Checks if Master_Ghost can climb up
	bool can_climb_up() const;

	// Checks if Master_Ghost can start climb
	bool can_start_climb() const;

	// Checks if Master_Ghost can climb
	bool can_climb() const;

	// Handles Master_Ghost's climbing logic
	void handle_climbing();

};