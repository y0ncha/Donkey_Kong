#include "Barrel.h"

// Constructor for the Barrel class, initializing the base Entity class with the given parameters
Barrel::Barrel(const Board* org_board, Board* curr_board, Coordinates _pos) : Entity(org_board, curr_board, _pos, BARREL) {}

// Method to handle the movement logic of the barrel
void Barrel::move() { // @ decide what happens if barrel is off bound

    // If the barrel has been falling for 8 or more steps, it should explode
    if (fall_count >= 8) {
        explode = true;
    }

    // Get the character directly below the barrel's current position
    char bellow_barrel = curr_board->get_char(pos.x, pos.y + 1);

    // If the barrel is currently falling
    if (falling) {

        // Check if the barrel has landed on the floor
        if (is_floor(bellow_barrel)) {

            // Stop the falling process
            falling = false;
            dir.y = 0;
            fall_count = 0;

            // If the barrel should explode, erase it from the board
            if (explode) {
                erase();
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
        if (is_floor(bellow_barrel)) {
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
    step(70);
}

// Method to handle the direction change when the barrel is on different types of floors
void Barrel::floor_switch(char bellow_barrel) {
    switch (bellow_barrel) {
    case FLOOR_L:
        dir.x = -1; // Move left
        break;
    case FLOOR_R:
        dir.x = 1; // Move right
        break;
    case FLOOR:
        dir.x = last_dx; // Continue in the last horizontal direction
    default:
        break;
    }
}
