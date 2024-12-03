#include "Coord.h"

/**
 * Overloads the += operator to add the coordinates of another Coordinates object to this one.
 * Updates the x and y values of this object.
 */
Coordinates& Coordinates::operator+=(const Coordinates& other) {
    this->x += other.x; // Add the x values
    this->y += other.y; // Add the y values
    return *this; // Return the updated object
}

/**
 * Overloads the + operator to return a new Coordinates object that is the sum of this object and another.
 * Does not modify the original objects.
 */
Coordinates Coordinates::operator+(const Coordinates& other) const {
    return Coordinates(this->x + other.x, this->y + other.y); // Return a new Coordinates object with summed values
}