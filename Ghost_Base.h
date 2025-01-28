#pragma once
#include "Entity.h"
#include "Board.h"

/**
 * @class Ghost_Base
 * Represents a generic Regular_Ghost entity in the game.
 */
class Ghost_Base : public Entity {

public:

    // Constructor for the Ghost_Base class
    Ghost_Base(const Board* pBoard, char icon, Coordinates init_pos);

    // Virtual destructor for the Ghost_Base class
    virtual ~Ghost_Base() = default;

    // Method to move the Regular_Ghost
    virtual void move() override = 0;

    // Method to reset the Regular_Ghost
    void reset();

    // Method to kill the Regular_Ghost
    void kill();

    // Method to check if the Regular_Ghost is active
    bool is_active() const;

    // Method to activate the Regular_Ghost
    void activate();

    // Method to check if the Regular_Ghost hit Mario
    bool is_hit_mario() const;

    // Method to set the direction of the Regular_Ghost
    void set_dir(Coordinates coord);

    // Method to clone the Regular_Ghost entity
    virtual std::unique_ptr<Ghost_Base> clone() const = 0;


protected:
    // Method to update the direction of the Regular_Ghost
    virtual bool update_dir(char key = static_cast<char>(Ctrl::DEF)) override;

private:

    // Flag to indicate if the Regular_Ghost is active
    bool active = false;

    // Method to check if the Regular_Ghost's next move is valid
    bool valid_move();

    // Method to initialize the direction of the Regular_Ghost
    Coordinates init_dir();

    // Empty implementation of handle_falling
    virtual void handle_falling() override;

    // Empty implementation of handle_collision
    virtual char handle_collision() override;



};