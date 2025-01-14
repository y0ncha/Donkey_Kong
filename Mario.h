#pragma once

#include "Entity.h"
#include "Config.h"

/**
 * @class Mario
 * Represents Mario in the game, inheriting from Entity.
 */
class Mario : public Entity {

public:
    // Constructor to initialize Mario with the original and current board
    Mario(const Board* pBoard);

    // Moves Mario one step with delay (Override of Entity's move method)
    void move() override;

    // Updates Mario's direction based on the input key
    void update_dir(char key = static_cast<char>(Ctrl::DEF)) override;

    // Gets the number of lives Mario has left
    int get_lives() const;

    // Resets Mario to the initial position
    void reset() override;

    // Reset Mario to it initial feilds
    void fatory_reset();

    // Checks if Mario was hit
    bool is_hit() const;

    // Checks if Mario saved Pauline
    bool has_rescued_pauline() const;
    
    // Checks if Mario picked up the hammer
    bool is_armed() const;

	// Setter for the board
    void set_board(const Board* pBoard);

	// Decreases the number of lives Mario has left
	void lose_lives();

	// Gets the number of points Mario has
    int get_score() const;

	// Updates Mario's score
	void update_score(Points points);

  // Consts for Mario's properties
  static constexpr int JMP_H = 2; // Max height of a jump
  static constexpr int MAX_FALL_H = 5; // Max height of a fall
  static constexpr int MAX_LIVES = 3; // Mario's number of lives

private:

    // Enum for Mario's State
    enum class State {
        IDLE,
        JUMPING,
        FALLING,
        CLIMBING,
    };

    State state = State::IDLE; // Current state of Mario

    int lives_left = MAX_LIVES; // Number of lives Mario has
    int fall_count = 0; // Counter for the number of steps Mario has been falling
    int jump_ascend = 0, jump_descend = 0; // Counter for the height of Mario's jump
    int score = 0;

    bool mario_hit = false; // Indicates if Mario has been hit
    bool rescued_pauline = false; // Indicates if Mario has saved Pauline
    bool armed = false; // Indicates if Mario has a hammer

    // Makes Mario jump
    void jump();

    // Makes Mario fall
    void fall();

    // Makes Mario climb up
    void climb_up();

    // Makes Mario climb down
    void climb_down();

    // Checks if Mario can climb
    bool can_climb() const;

	// Checks if Mario can jump
	bool can_jump() const;

    // Handles Mario's jumping logic
    void handle_jumping();

    // Handles Mario's climbing logic
    void handle_climbing();

    // Handles Mario's falling logic
    void handle_falling() override;

    // Handles Mario's idle logic
    void handle_idle();

    // Handles Mario's collision with other objects
    char handle_collision() override;
};
