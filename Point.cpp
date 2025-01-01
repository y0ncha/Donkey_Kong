#include "Point.h"

/**
 * @brief Constructor to initialize the point with a character and position.
 * @param ch The character representing the point.
 * @param init_pos The initial position of the point.
 */
Point::Point(char ch, Coordinates init_pos) : icon(static_cast<Board::Icon>(ch)), pos(init_pos) {}

/**
 * @brief Draws the point at the current position.
 */
void Point::draw() const {
    gotoxy(pos); // Move the cursor to the point's position
    std::cout << static_cast<char>(icon); // Print the point's character at the position
}

/**
 * @brief Erases the point from the current position.
 * @param ch The character to restore at the point's position.
 */
void Point::erase(char ch) const {
    gotoxy(pos); // Move the cursor to the point's position
    std::cout << ch; // Restore the character from the board
}