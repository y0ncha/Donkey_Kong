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
    void reset();

    // Method to check if the barrel is active
    bool is_active() const;

    // Method to check if the barrel hit Mario
    bool hitted_mario() const;

    // Method to spawn the barrel
    void spawn();

    static constexpr int MAX_FALL_H = 8; // Max height of a fall
    static constexpr int EXPLOSION_RADIUS = 2; // Radius of the explosion
    static constexpr int EXPLOSSION_DELAY = 60; // Delay for the explosion


private:
    // Method to handle the direction change when the barrel is on different types of floors
    void update_dir(char beneath) override;

    // Method to handle the falling of the barrel
    void handle_falling() override;

    // Method to print the explosion phase within a given radius
    void print_explosion_phase(int radius, Coordinates pos);

    // Method to clear the explosion phase within a given radius
    void clear_explosion_phase(int radius, Coordinates pos);

    // Method to set the initial position of the barrel
    Coordinates init_pos();

    // Method to handle the explosion of the barrel
    void explode();

    // State of the barrel
    enum class State { IDLE, FALLING, HIT_MARIO } state = State::IDLE;

    // Fall count
    int fall_count = 0;

    // Flag to check if the barrel is active
    bool active = false;
};
