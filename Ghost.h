#pragma once
#include "GhostEntity.h"

/**
 * @class Ghost
 * Represents a ghost entity in the game.
 */
class Ghost : public GhostEntity {

public:
	// Constructor for the Ghost class
	Ghost(const Board* pBoard = nullptr);

	// Method to move the ghost
	virtual void move() override;

	// Method to clone the ghost entity
	std::unique_ptr<GhostEntity> clone() const override;

};