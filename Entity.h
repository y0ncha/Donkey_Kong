#pragma once

#include "Board.h"
#include "Coord.h"
#include "Point.h"

// Forward declaration of the handle_err function
void handle_err(const std::string& message, const char* file, int line);

/**
 * @class Entity
 * Represents a generic game entity with position, movement, and rendering capabilities.
 */
class Entity {

public:
    // Constructor for the Entity class
    Entity(const Board* pBoard, char ch, Coordinates init_pos, Coordinates dir = {0, 0});

    // Virtual method to move the Entity
    virtual void move() = 0;

    // Virtual method to reset the Entity
    virtual void reset() = 0;

	// Draws the entity at its current position
    void set() const;

    // Erases the entity from its current position
    void vanish() const;

    // Getter for the char behind the entity
    char behind_ch() const;

    // Getter for the entity's icon
    char next_ch() const;

    // Checks the character beneath the entity
    char beneath_ch() const;

    // Checks the character above the entity
    char above_ch() const;

    // Getter for the entity's position
    Coordinates get_pos() const { return point.pos; }

    // Getter for the entity's direction
    Coordinates get_dir() const { return dir; }

    // Checks if the entity is off the ground
    bool off_ground() const;

    // Checks if the entity is on the ground
    bool on_ground() const;

protected:

    // Setter for the entity's direction using dx and dy values
    bool set_dir(int dx, int dy);
    bool set_dir(Coordinates coord);

    // Setter for the entity's position using x and y coordinates
    bool set_pos(int _x, int _y) const;
    bool set_pos(Coordinates coord) const;

    // Pointer to the original game board
    const Board* board;

    // Point representation of the entity
    Point point;

    // Last horizontal direction
    int last_dx = 0;

    // Direction of the entity
    Coordinates dir;

    // Moves the entity by one step with an optional delay
    void step();

    // Virtual method to handle collisions with other entities or obstacles
    virtual char handle_collision() = 0;

    // Virtual method to update the entity's direction
    virtual void update_dir(char key = static_cast<char>(Ctrl::DEF)) = 0; // Explicitly cast the default value

    // Virtual method to handle the direction change when the entity is on different types of floors
    virtual void handle_falling() = 0;
};
