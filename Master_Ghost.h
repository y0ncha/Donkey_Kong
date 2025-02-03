#pragma once
#include "Ghost_Base.h"
#include "Coord.h"

/**
 * @class Master_Ghost
 * Represents a Master_Ghost entity in the game.
 */
class Master_Ghost : public Ghost_Base {

public:
	// Constructor for the Master_Ghost class
	Master_Ghost(const Board* pBoard, const Mario& mario);

	// Method to move the Master_Ghost
	void move() override;

	// Method to clone the Master_Ghost entity
	std::unique_ptr<Ghost_Base> clone() const override;

	// Method to reset the Master_Ghost
	void reset() override;

	static constexpr int CHASE_RANGE = 15;

private:
 
	// State of the Master_Ghost
	enum class State { IDLE, CLIMBING, CHASING } state = State::IDLE;

	// Bias enum for the Master_Ghost
	enum class Bias { DEF, UP, DOWN, LEFT, RIGHT };

	// Bias according to mario's reltive position
	std::pair<Bias, Bias> bias = { Bias::DEF, Bias::DEF };

	// Reference to the game's mario
	const Mario& mario;

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

	// Seek for mario to chase
	bool seek_mario();

	// Seek for ladder to go up or down
	void find_ladder();

	// Moves the Master_Ghost by defined statistics
	void random_move();

	// Moves the Master_Ghost to chase mario
	void chase();

	// Updates the direction of the Master_Ghost according to the bias
	bool update_dir();

	// Checks if mario is in the chace range
	bool in_range(Coordinates target) const;

	// Search for a ladder to to the left
	int search_left(int y) const;

	// Search for a ladder to to the right
	int search_right(int y) const;
};