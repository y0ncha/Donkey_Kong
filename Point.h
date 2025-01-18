#pragma once

#include <iostream> 
#include "Utils.h"
#include "Coord.h"
#include "Board.h"

/**
 * @class Point
 * @brief The Point class represents a point in the game board.
 * It holds a character icon and a position on the board.
 */
class Point {
public:

	// Constructor for the Point class
    Point(char ch, Coordinates init_pos);
	Point(Board::Icon icon, Coordinates init_pos);

    // Character representation of the point
	Board::Icon icon;

    // Position of the point
	mutable Coordinates pos;

    friend std::ostream& operator<<(std::ostream& os, const Point& point);

	// Draw the point on the console
    void draw() const;
 
	// Erase the point from the console
    void erase(char ch) const;
};