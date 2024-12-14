#pragma once

#include <iostream>
#include "Utils.h"
#include "Coord.h"


/*
 * @class Point
 * The Point class represents a point in the game board.
 * It holds a character icon and a position on the board.
 */
class Point {

public:

	Point(char ch, Coordinates init_pos); // Constructor to initialize the point with a character and position

	// Character representation of the point
	char icon; 

	// Position of the point
	Coordinates pos;

	// Draws the point at the current position
	void draw() const;

	// Erases the point from the current position
	void erase(char ch) const;
};