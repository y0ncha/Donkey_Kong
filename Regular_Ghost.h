#pragma once
#include "Ghost_Base.h"

/**
 * @class Regular_Ghost
 * Represents a Regular_Ghost entity in the game.
 */
class Regular_Ghost : public Ghost_Base {

public:
	// Constructor for the Regular_Ghost class
	Regular_Ghost(const Board* pBoard = nullptr);

	// Method to move the Regular_Ghost
	virtual void move() override;

	// Method to clone the Regular_Ghost entity
	std::unique_ptr<Ghost_Base> clone() const override;

};