#include "Coord.h"

Coordinates& Coordinates::operator+=(const Coordinates& other) {  // Define the += operator
    this->x += other.x;
    this->y += other.y;
    return *this;
}

Coordinates Coordinates::operator+(const Coordinates& other) const { // Define the + operator
    return Coordinates(this->x + other.x, this->y + other.y);
}