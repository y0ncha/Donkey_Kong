#pragma once

#include "Entity.h"
#include "Config.h"
#include "Utils.h"

class Mario : public Entity {

    int lives_left = LIVES; // Number of lives Mario has

    int fall_count = 0;

    bool falling = false;

    bool jumping = false;

    bool climbing = false;

    void jump(); // Makes Mario jump

	void fall(); // Makes Mario fall

	void climb_up(); // Makes Mario climb up

	void climb_down(); // Makes Mario climb down

	char dest_ch() const; // Gets the character at the destination

	char curr_ch() const; // Gets the character at the current position

	bool on_ground() const; // Checks if Mario is on the ground

public:

    // Updated constructor to match the argument list in Game class
    Mario(const Board* org_board, Board* curr_board);

    void move(); // Moves Mario one step with delay

    void update_dir(char key); // Updates Mario's direction based on the input key
};
