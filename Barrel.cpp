#include "Barrel.h"

/**
* Constructor for the Barrel class.
* @warning This constructor does not initialize the barrel's position and pointer.
*/
Barrel::Barrel() : Entity(Board::BARREL) {}

/**
 * Method to handle the movement logic of the barrel.
 */
void Barrel::move() { // @ decide what happens if barrel is off bound
    // If the barrel has been FALLING for 8 or more steps, it should explode

    char beneath = beneath_ch();

    if (FALLING) {
        handle_falling();
    }
    else {
		update_dir(beneath);
		step();
    }
}

/**
 * Method to handle the direction change when the barrel is on different types of floors.
 */
void Barrel::update_dir(char beneath) {

    switch (beneath) {
    case Board::FLOOR_L: // If the barrel is on a left-sloping floor
        last_dx = dir.x = -1; // move left
        break;

    case Board::FLOOR_R: // If the barrel is on a right-sloping floor
        last_dx = dir.x = 1; // move right
        break;

	case Board::AIR: // If the barrel is in the air
        FALLING = true;
		dir = { 0, 1 }; // move down
        fall_count++;

    default: // If the barrel is on a flat floor keep moving in the same direction
        break;
    }
}

/*
* Method to handle the FALLING of the barrel.
*/
void Barrel::handle_falling() { // todo make virtual

    FALLING = true;
	fall_count++;

	// Set the direction to fall and step
	dir = { 0, 1 };
    step();
	
	// If the barrel is now on the ground
	if (on_ground()) {
		explode = (fall_count >= MAX_FALL_H);
		dir = { last_dx, 0 };
		FALLING = false;
		fall_count = 0;
	}
}

/**
 * Checks if the barrel is active.
 */
bool Barrel::is_active() const {
    return active;
}

/**
 * Returns the initial position of the barrel.
 */
void Barrel::init_pos() { 
    pos = {(rand() % 2 == 0) ? Board::DKONG_X0 + 1 : Board::DKONG_X0 - 1, Board::DKONG_Y0};
}

/**
 * Sets the original and current board for the barrel.
 */
void Barrel::set_board(const Board* pBoard) {
	board = pBoard;
}

/**
 * Spawns the barrel at the initial position and activates it.
 */
void Barrel::spawn() {
	init_pos();
    active = true;
    draw();
}

/**
 * Handles collision logic for the barrel.
 */
char Barrel::handle_collision() {

	char obst = getch_console(pos + dir);

    switch (obst) {
	case Board::MARIO: // If the barrel hits Mario
        explode = true;
		break;

	case Board::ERR: // If the barrel is out of bounds
        reset();
        break;
    }
	return obst; // Return the type of object the barrel hits (optional for next exercise) 
}

void Barrel::reset() {
    erase();
    dir = { 0,0 };
    active = false;
}
