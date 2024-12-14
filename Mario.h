#pragma once

#include "Entity.h"
#include "Utils.h"
#include "Config.h"

// Mario class inheriting from Entity
class Mario : public Entity {

public:

    // Constructor to initialize Mario with the original and current board
    Mario(const Board* pBoard);

    // Enum for Mario's related constants
    enum Consts {
        JMP_H = 2, // Max height of a jump
        MAX_FALL_H = 5, // Max height of a fall
        LIVES = 3, // Mario's number of lives
    };

    // Moves Mario one step with delay (Override of Entity's move method)
    void move() override;

    // Updates Mario's direction based on the input key
    void update_dir(char key) override;

	// Gets the number of lives Mario has left
	int get_lives() const;

    // Reset Mario to the initial position
    void reset() override;

	// Checks if Mario was hit
	bool is_hit() const;

    // Cheks if Mario saved Pauline
    bool is_rescued_pauline() const;

private:

    // Enum for Mario's status
    enum class Status {
        IDLE,
        JUMPING,
        FALLING,
        CLIMBING,
    };

    Status status = Status::IDLE; // Current status of Mario

    int lives_left = LIVES; // Number of lives Mario has
    int fall_count = 0; // Counter for the number of steps Mario has been FALLING
	int jump_ascend = 0, jump_descend = 0; // Counter for the height of Mario's jump

	bool mario_hit = false; // Indicates if Mario has been hit
	bool rescued_pauline = false; // Indicates if Mario has saved Pauline

    // Makes Mario jump
    void jump();

    // Makes Mario fall
    void fall();

    // Makes Mario climb up
    void climb_up();

    // Makes Mario climb down
    void climb_down();

	// Checks if Mario can climb
	bool can_climb();

    // Handles Mario's JUMPING logic
    void handle_jumping();

    // Handles Mario's CLIMBING logic
    void handle_climbing();

    // Handles Mario's FALLING logic
    void handle_falling() override;

    // Handles Mario's IDLE logic
    void handle_idle();

	// Handles Mario's collision with other objects
	char handle_collision() override;
};
