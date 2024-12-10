#include "Barrel.h"

/**
* Constructor for the Barrel class (WARNING - THIS C'TOR DOES NOT INITIALIZE THE BOARD POINTERS).
* --------------- please see @init_barrels() in Game.cpp for the correct c'tor ------------------
*/
Barrel::Barrel() : Entity(Board::BARREL, init_pos()) {}

/**
 * Method to handle the movement logic of the barrel.
 */
void Barrel::move() { // @ decide what happens if barrel is off bound
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
    char bellow_barrel = curr_board->get_char(pos.x, pos.y + 1);

    // If the barrel is currently falling
    if (falling) {
        // Check if the barrel has landed on the floor
        if (org_board->is_floor(bellow_barrel)) {
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
        if (org_board->is_floor(bellow_barrel)) {
            floor_switch(bellow_barrel);
        } else {
            // Start falling
            dir.y = 1;
            dir.x = 0;
            falling = true;
            fall_count++;
        }
    }
    // Move the barrel by a step of 70 units
    step();
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
    default:
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
Coordinates Barrel::init_pos() { 
    return {(rand() % 2 == 0) ? Board::DKONG_X0 + 1 : Board::DKONG_X0 - 1, Board::DKONG_Y0};
}

/**
 * Sets the original and current board for the barrel.
 */
void Barrel::set_board(const Board* layout, Board* board) {
    org_board = layout;
    curr_board = board;
}

/**
 * Spawns the barrel at the initial position and activates it.
 */
void Barrel::spawn() {
    pos = init_pos();
    active = true;
    draw();
}

// todo delete
