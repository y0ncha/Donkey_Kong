#pragma once

/**
 * @struct Coordinates
 * Represents a generic Coordinates with x and y values.
 */
struct Coordinates {

    Coordinates() : x(0), y(0) {}
    Coordinates(int x, int y) : x(x), y(y) {}

    int x, y;

    // Define the += operator
    Coordinates& operator+=(const Coordinates& other);

    // Define the + operator
    Coordinates operator+(const Coordinates& other) const;
};

