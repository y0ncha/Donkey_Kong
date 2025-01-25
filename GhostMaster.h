#pragma once
#include "GhostEntity.h"

/**
 * @class Ghost
 * Represents a ghost entity in the game.
 */
class GhostMaster : public GhostEntity {

public:
	// Constructor for the Ghost class
	GhostMaster(const Board* pBoard);

	// Method to move the ghost
	void move() override;

	// Method to clone the ghost entity
	GhostMaster* clone() const override;

private:

	// State of the ghost
	enum class State { IDLE, CLIMBING } state = State::IDLE;

	// Makes Ghost climb up
	void climb();

	// Checks if Ghost can climb down
	bool can_climb_down() const;

	// Checks if Ghost can climb up
	bool can_climb_up() const;

	// Checks if Ghost can start climb
	bool can_start_climb() const;

	// Checks if Ghost can climb
	bool can_climb() const;

	// Handles Ghost's climbing logic
	void handle_climbing();

};