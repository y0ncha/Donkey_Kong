#pragma once

#include <iostream>
#include "Board.h"
#include "Coord.h"
#include "Utils.h"

// Forward declaration of the handle_err function
void handle_err(const std::string& message, const char* file, int line);

/**
 * @class Entity
 * Represents a generic game entity with position, movement, and rendering capabilities.
 */
class Entity {

protected:

    // Constructor for the Entity class
    Entity(const Board* pBoard, char ch, Coordinates init_pos, Coordinates dir = {0, 0});

    const Board* board; // Reference to the original game board

    char icon; // Character representation of the entity

    int last_dx = 0; // Last horizontal direction

    Coordinates pos; // Default position of an entity
    Coordinates dir; // Direction of the entity

    // Moves the entity by one step with an optional delay
    void step();

    // Virtual method to handle collisions with other entities or obstacles
    virtual char handle_collision() = 0;

    // Virtual method to update the entity's direction
	virtual void update_dir(char key = static_cast<char>(Ctrl::DEF)) = 0; // Explicitly cast the default value

	// Virtual method to handle the direction change when the entity is on different types of floors
    virtual void handle_falling() = 0;


public:
    
	// Virtual method to move the Entity
    virtual void move() = 0;

    // Virtual method to reset the Entity
    virtual void reset() = 0;

    // Draws the entity at its current position
    void draw() const;

    // Erases the entity from its current position
    void erase() const;

	// Getter for the entity's icon
	char curr_ch() const;

	// Getter for the entity's icon
    char next_ch() const;

    // Checks the character beneath Mario
    char beneath_ch() const;

	// Checks the character above Mario
	char above_ch() const;

    // Getter for the x-coordinate of the entity's position
    int get_x() const { return pos.x; }

    // Getter for the y-coordinate of the entity's position
    int get_y() const { return pos.y; }

    // Getter for the entity's position
    Coordinates get_pos() const { return pos; }

    // Getter for the entity's direction
    Coordinates get_dir() const { return dir; }

    // Setter for the entity's position using x and y coordinates
    void set_pos(int _x, int _y);
    void set_pos(Coordinates coord);

    // Setter for the entity's direction using dx and dy values
    void set_dir(int dx, int dy);
    void set_dir(Coordinates coord);

    // Checks if Entity is on the ground
    bool off_ground() const;

    // Checks if Entity is on the ground
    bool on_ground() const;
};
