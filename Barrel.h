#pragma once

#include "Board.h"
#include "Entity.h"

// Barrel class inheriting from Entity
class Barrel : public Entity {

    bool falling = false; // Indicates if the barrel is currently falling
    int fall_count = 0; // Counter for the number of steps the barrel has been falling
    bool explode = false; // Indicates if the barrel should explode

    // Method to handle the direction change when the barrel is on different types of floors
    void floor_switch(char bellow_barrel);

public:
    // Constructor for the Barrel class, initializing the base Entity class with the given parameters
    Barrel(const Board* org_board, Board* curr_board, Coordinates _pos);

	// Enum for Barrel's related constants
	enum CONSTS {
		MAX_FALL_H = 8 // Maximum height of a fall
	};

    // Method to handle the movement logic of the barrel (Override of Entity's move method)
    void move() override;
};
