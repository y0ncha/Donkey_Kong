#include "Barrel.h"

/**
* Constructor for the Barrel class.
* @warning This constructor does not initialize the barrel's position and pointer.
*/
Barrel::Barrel() : Entity(Board::BARREL) {}

/**
 * Method to handle the movement logic of the barrel.
 */
void Barrel::Move() { // @ decide what happens if barrel is off bound
    if (!pos_inbound(pos + dir)) { // Check if the next position is within the game bounds
        erase(); // Erase the barrel from the board
        active = false; // Deactivate the barrel
        return;
    }
    // If the barrel has been falling for 8 or more steps, it should explode
    if (fall_count >= MAX_FALL_H) {
        explode = true;
    }

    // Get the character directly below the barrel's current position
	char bellow_barrel = beneath_ch();

    // If the barrel is currently falling
    if (falling) {
        // Check if the barrel has landed on the floor
        if (board->is_floor(bellow_barrel)) {
            // Stop the falling process
            falling = false;
            dir.y = 0;
            fall_count = 0;

            // If the barrel should explode, erase it from the board
            if (explode) {
                erase();
                active = false; // Deactivate the barrel
                return;
            }

            // Handle the floor switch logic based on the type of floor
            floor_switch(bellow_barrel);
        } else {
            // Continue falling
            dir.y = 1;
            fall_count++;   
        }
    } else {
        // Store the last horizontal direction
        last_dx = dir.x;

        // Check if the barrel is on the floor
        if (board->is_floor(bellow_barrel)) {
            floor_switch(bellow_barrel);
        } else {
            // Start falling
            dir.y = 1;
            dir.x = 0;
            falling = true;
            fall_count++;
        }
    }
    step(); // Move the barrel one step
}

/**
 * Method to handle the direction change when the barrel is on different types of floors.
 */
void Barrel::floor_switch(char bellow_barrel) {

    switch (bellow_barrel) {
    case Board::FLOOR_L:
        dir.x = -1; // Move left
        break;

    case Board::FLOOR_R:
        dir.x = 1; // Move right
        break;

    case Board::FLOOR:
        dir.x = last_dx; // Continue in the last horizontal direction
        break;
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
void Barrel::handle_collision() {

	char obst = getch_console(pos + dir);

    switch (obst) {
	case Board::MARIO:
		// todo add Mario logic
		break;
	case Board::ERR:
		// todo set inactive and erase
        break;
    }
}
