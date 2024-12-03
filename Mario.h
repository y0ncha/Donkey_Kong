#pragma once

#include "Entity.h"
#include "Config.h"
#include "Utils.h"

// Mario class inheriting from Entity
class Mario : public Entity {

    int lives_left = LIVES; // Number of lives Mario has
    int fall_count = 0; // Counter for the number of steps Mario has been falling
    bool falling = false; // Indicates if Mario is currently falling
    bool jumping = false; // Indicates if Mario is currently jumping
    bool climbing = false; // Indicates if Mario is currently climbing

    // Makes Mario jump
    void jump();

    // Makes Mario fall
    void fall();

    // Makes Mario climb up
    void climb_up();

    // Makes Mario climb down
    void climb_down();

    // Gets the character at the destination position
    char dest_ch() const;

    // Gets the character at the current position
    char curr_ch() const;

    // Checks if Mario is on the ground
    bool on_ground() const;

public:
    // Constructor to initialize Mario with the original and current board
    Mario(const Board* org_board, Board* curr_board);

    // Moves Mario one step with delay
    void move();

    // Updates Mario's direction based on the input key
    void update_dir(char key);
};
