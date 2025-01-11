#include "Coord.h"


/**
 * @brief Overloads the += operator to add the coordinates of another Coordinates object to this one.
 * Updates the x and y values of this object.
 * @param other The other Coordinates object to add.
 * @return A reference to the updated Coordinates object.
 */
Coordinates& Coordinates::operator+=(const Coordinates& other) {
    this->x += other.x; // Add the x values
    this->y += other.y; // Add the y values
    return *this; // Return the updated object
}

/**
 * @brief Overloads the + operator to return a new Coordinates object that is the sum of this object and another.
 * Does not modify the original objects.
 * @param other The other Coordinates object to add.
 * @return A new Coordinates object with summed values.
 */
Coordinates Coordinates::operator+(const Coordinates& other) const {
    return Coordinates(this->x + other.x, this->y + other.y); // Return a new Coordinates object with summed values
}

/**
 * @brief Overloads the - operator to return a new Coordinates object that is the difference of this object and another.
 * Does not modify the original objects.
 * @param other The other Coordinates object to subtract.
 * @return A new Coordinates object with subtracted values.
 */
Coordinates Coordinates::operator-(const Coordinates& other) const
{
    return Coordinates(this->x - other.x, this->y - other.y); // Return a new Coordinates object with subtracted values
}

/**
 * @brief Overloads the == operator to compare two Coordinates objects.
 * Returns true if the x and y values are equal.
 * @param other The other Coordinates object to compare.
 * @return True if the x and y values are equal, false otherwise.
 */
bool Coordinates::operator==(const Coordinates& other) const {
    return this->x == other.x && this->y == other.y; // Compare the x and y values
}

/**
 * @brief Overloads the != operator to compare two Coordinates objects.
 * Returns true if the x or y values are not equal.
 * @param other The other Coordinates object to compare.
 * @return True if the x or y values are not equal, false otherwise.
 */
bool Coordinates::operator!=(const Coordinates& other) const {
    return !(*this == other); // Use the == operator to determine inequality
}

/**
 * @brief Resets the coordinates to (0, 0).
 */
void Coordinates::reset() {
    this->x = 0; // Reset x to 0
    this->y = 0; // Reset y to 0
}