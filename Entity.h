#pragma once

#include <iostream>
#include <windows.h>
#include "Board.h"
#include "Coord.h"

/**
 * @class Entity
 * Represents a generic game entity with position, movement, and rendering capabilities.
 */
class Entity {

protected:

    const Board* org_board; // Reference to the game board

    Board* curr_board;

	Coordinates pos; // Position of the entity

    Coordinates dir = { 0, 0 }; // Direction of the entity

    char icon; // Character representation

    int last_dx = 0;

    void step();

public:

    Entity(const Board* layout, Board* board, Coordinates _pos, char ch);

    int get_x() const { return pos.x; };

    int get_y() const { return pos.y; };

	Coordinates get_pos() const { return pos; };

	Coordinates get_dir() const { return dir; };

    void set_pos(int _x, int _y);

    void set_dir(int dx, int dy);

	void set_pos(Coordinates coord);

	void set_dir(Coordinates coord);

    void draw() const; // Draws the entity at its current position

    void erase() const; // Erases the entity from its current position
};
