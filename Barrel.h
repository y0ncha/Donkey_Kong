#pragma once
#include <cstdlib>
#include "Board.h"
#include "Entity.h"

// Barrel class inheriting from Entity
class Barrel : public Entity {

    bool falling = false; // Indicates if the barrel is currently falling
    bool explode = false; // Indicates if the barrel should explode
    bool active = false; // Indicates if the barrel is active

    int fall_count = 0; // Counter for the number of steps the barrel has been falling

    // Method to handle the direction change when the barrel is on different types of floors
    void floor_switch(char bellow_barrel);

public:

    // Constructor for the Barrel class
    Barrel();

    // Enum for Barrel's related constants
    enum CONSTS {
        MAX_FALL_H = 8 // Maximum height of a fall
    };

    // Method to handle the movement logic of the barrel (Override of Entity's move method)
    void move() override;

    // Checks if the barrel is active
    bool is_active() const;

    // Returns the initial position of the barrel
    Coordinates init_pos();

    // Sets the original and current board for the barrel
    void set_board(const Board* org_board, Board* curr_board);

    // Spawns the barrel at the initial position
    void spawn();
};
