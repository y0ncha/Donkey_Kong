#pragma once

#include <iostream>
#include "Board.h"
#include "Coord.h"


/**
 * @class Entity
 * Represents a generic game entity with position, movement, and rendering capabilities.
 */
class Entity {

protected:

    const Board* org_board; // Reference to the original game board
    Board* curr_board; // Reference to the current game board

    char icon; // Character representation of the entity

    Coordinates pos; // Default position of an entity
    Coordinates dir; // Direction of the entity

    int last_dx = 0; // Last horizontal direction

    // Moves the entity by one step with an optional delay
    void step();

    // Constructor for the Entity class
    Entity(const Board* layout, Board* board, char ch, Coordinates init_pos = { Board::MARIO_X0, Board::MARIO_Y0 }, Coordinates dir = { 0, 0 });
    Entity(char ch, Coordinates init_pos = { Board::MARIO_X0, Board::MARIO_Y0 }, Coordinates dir = { 0, 0 });

public:

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

    // Draws the entity at its current position
    void draw() const; // todo move to pirivate

    // Erases the entity from its current position
    void erase() const; // todo move to pirivate

    // Virtual move method to be overridden by derived classes
    virtual void move() = 0;
};
