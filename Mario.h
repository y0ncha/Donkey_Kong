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

    // Enum for Mario's status
    enum class Status{
        Idle,
        Jumping,
        Falling,
        Climbing,
        Dead
    };

    Status status = Status::Idle; // Current status of Mario

    // Moves Mario one step with delay (Override of Entity's Move method)
    void Move() override;

    // Updates Mario's direction based on the input key
    void update_dir(char key);

    // Checks if Mario is dead
    bool is_dead() const;

	// Gets the number of lives Mario has left
	int get_lives() const;

    // Decreases Mario's lives by one
    void kill();

private:

    int lives_left = LIVES; // Number of lives Mario has
    int fall_count = 0; // Counter for the number of steps Mario has been falling
	int jump_h = 0; // Counter for the height of Mario's jump

    bool died = false; // Indicates if Mario is dead

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

    // Checks if Mario is on the ground
    bool off_ground() const;

	// Checks if Mario is on the ground
	bool on_ground() const;

    // Handles Mario's jumping logic
    void handle_jumping();

    // Handles Mario's climbing logic
    void handle_climbing();

    // Handles Mario's falling logic
    void handle_falling();

    // Handles Mario's idle logic
    void handle_idle();

	// Handles Mario's collision with other objects
	void handle_collision() override;
};
