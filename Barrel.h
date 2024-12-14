#pragma once

#include "Entity.h"
#include "Board.h"

/**
 * @class Barrel
 * Represents a barrel entity in the game.
 */
class Barrel : public Entity {

public:
    // Constructor for the Barrel class
    Barrel(const Board* pBoard);

    // Method to handle the movement logic of the barrel
    void move() override;

    // Method to handle collision logic for the barrel
    char handle_collision() override;

    // Method to reset the barrel
    void reset() override;

    // Method to check if the barrel is active
    bool is_active() const;

    // Method to check if the barrel hit Mario
    bool hitted_mario() const;

    // Method to set the board for the barrel
    void set_board(const Board* pBoard);

    // Method to spawn the barrel
    void spawn();

private:
    // Method to handle the direction change when the barrel is on different types of floors
    void update_dir(char beneath) override;

    // Method to handle the falling of the barrel
    void handle_falling() override;

    // Method to print the explosion phase within a given radius
    void print_explosion_phase(int radius);

    // Method to clear the explosion phase within a given radius
    void clear_explosion_phase(int radius);

    // Method to set the initial position of the barrel
    Coordinates init_pos();

    // Method to handle the explosion of the barrel
    void explode();

    // State of the barrel
    enum class State { IDLE, FALLING, HIT_MARIO } state = State::IDLE;

    // Maximum fall height before the barrel explodes
    static constexpr int MAX_FALL_H = 8;

    // Explosion radius
    static constexpr int EXPLOSION_RADIUS = 2;

    // Explosion delay in milliseconds
    static constexpr int EXPLOSION_DELAY = 100;

    // Fall count
    int fall_count = 0;


    // Flag to check if the barrel is active
    bool active = false;
};
