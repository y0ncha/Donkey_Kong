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

    /**
     * @brief Constructor to initialize the point with a character and position.
     * @param ch The character representing the point.
     * @param init_pos The initial position of the point.
     */
    Point(char ch, Coordinates init_pos);

    // Character representation of the point
    Board::Icon icon;

    // Position of the point
	mutable Coordinates pos;

    /**
     * @brief Draws the point at the current position.
     */
    void draw() const;

    /**
     * @brief Erases the point from the current position.
     * @param ch The character to restore at the point's position.
     */
    void erase(char ch) const;
};