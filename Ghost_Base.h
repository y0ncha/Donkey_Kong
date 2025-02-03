#pragma once
#include "Entity.h"
#include "Board.h"
#include "Mario.h"

/**
 * @class Ghost_Base
 * Represents a generic Ghost_Base entity in the game.
 */
class Ghost_Base : public Entity {

public:

    // Constructor for the Ghost_Base class
    Ghost_Base(const Board* pBoard, char icon, Coordinates init_pos);

    // Virtual destructor for the Ghost_Base class
    virtual ~Ghost_Base() = default;

    // Method to move the Ghost_Base
    virtual void move() override = 0;

    // Method to reset the Ghost_Base
    virtual void reset();

    // Method to kill the Ghost_Base
    void kill();

    // Method to check if the Ghost_Base is active
    bool is_active() const;

    // Method to activate the Ghost_Base
    void activate();

    // Method to check if the Ghost_Base hit Mario
    bool is_hit_mario() const;

    // Method to set the direction of the Ghost_Base
    void set_dir(Coordinates coord);

    // Method to clone the Ghost_Base entity
    virtual std::unique_ptr<Ghost_Base> clone() const = 0;


protected:

    // Method to update the direction of the Ghost_Base
    bool update_dir(char key = static_cast<char>(Ctrl::DEF));
    
    // Method to check if the Ghost_Base's next move is valid
    bool valid_move();

private:

    // Flag to indicate if the Ghost_Base is active
    bool active = false;

    // Method to initialize the direction of the Ghost_Base
    Coordinates init_dir();

    // Empty implementation of handle_falling
    void handle_falling() override;

    // Empty implementation of handle_collision
    char handle_collision() override;
};