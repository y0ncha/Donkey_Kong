#pragma once

/**
 * @struct Coordinates
 * Represents a generic Coordinates with x and y values.
 */
struct Coordinates {

	Coordinates() : x(0), y(0) {} // Default constructor
	Coordinates(int x, int y) : x(x), y(y) {} // Constructor with x and y values

    int x, y;

    // Define the += operator
    Coordinates& operator+=(const Coordinates& other);

    // Define the + operator
    Coordinates operator+(const Coordinates& other) const;
};

