#pragma once
#include "Entity.h"
#include "Board.h"

/**
 * @class GhostEntity
 * Represents a generic ghost entity in the game.
 */
class GhostEntity : public Entity {

public:

    // Constructor for the GhostEntity class
    GhostEntity(const Board* pBoard, char icon, Coordinates init_pos);

    // Virtual destructor for the GhostEntity class
    virtual ~GhostEntity() = default;

    // Method to move the ghost
    virtual void move() override = 0;

    // Method to reset the ghost
    void reset();

    // Method to kill the ghost
    void kill();

    // Method to check if the ghost is active
    bool is_active() const;

    // Method to activate the ghost
    void activate();

    // Method to check if the ghost hit Mario
    bool is_hit_mario() const;

    // Method to set the direction of the ghost
    void set_dir(Coordinates coord);

    // Method to clone the ghost entity
    virtual std::unique_ptr<GhostEntity> clone() const = 0;


protected:
    // Method to update the direction of the ghost
    virtual void update_dir(char key = static_cast<char>(Ctrl::DEF)) override;

private:

    // Flag to indicate if the ghost is active
    bool active = false;

    // Method to check if the ghost's next move is valid
    bool valid_move();

    // Method to initialize the direction of the ghost
    Coordinates init_dir();

    // Empty implementation of handle_falling
    virtual void handle_falling() override;

    // Empty implementation of handle_collision
    virtual char handle_collision() override;



};