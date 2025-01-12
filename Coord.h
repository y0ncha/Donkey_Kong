#pragma once

/**
 * @struct Coordinates
 * Represents a generic Coordinates with x and y values.
 * Definded as a struct to allow public access to its members, to be held in private section of a class.
 */
struct Coordinates {

    // Default constructor
    Coordinates() : x(0), y(0) {}

    // Constructor with x and y values
    Coordinates(int x, int y) : x(x), y(y) {}

    // x and y coordinates
    int x, y;

    // Overloads the += operator to add the coordinates of another Coordinates object to this one
    Coordinates& operator+=(const Coordinates& other);

    // Overloads the + operator to return a new Coordinates object that is the sum of this object and another
    Coordinates operator+(const Coordinates& other) const;

    // Overloads the - operator to return a new Coordinates object that is the difference of this object and another
    Coordinates operator-(const Coordinates& other) const;

    // Overloads the == operator to compare two Coordinates objects
    bool operator==(const Coordinates& other) const;

    // Overloads the != operator to compare two Coordinates objects
    bool operator!=(const Coordinates& other) const;

    // Resets the coordinates to (0, 0)
    void reset();
};
