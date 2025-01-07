#include "Point.h"

/**
 * @brief Constructor to initialize the point with a character and position.
 * @param ch The character representing the point.
 * @param init_pos The initial position of the point.
 */
Point::Point(char ch, Coordinates init_pos) : icon(static_cast<Board::Icon>(ch)), pos(init_pos) {}
Point::Point(Board::Icon ch, Coordinates init_pos) : icon(static_cast<Board::Icon>(ch)), pos(init_pos) {}

/**
 * @brief Overloads the << operator to print the point.
 * @param os The output stream to print to.
 * @param point The point to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& os, const Point& point) {
	gotoxy(point.pos); // Move the cursor to the point's position
	return std::cout << static_cast<char>(point.icon); // Print the point's character at the position
}

/**
 * @brief Draws the point at the current position.
 */
void Point::draw() const {
	if (Board::pos_inbound(pos)) std::cout << *this; // Print the point on the console
}

/**
 * @brief Erases the point from the current position.
 * @param ch The character to restore at the point's position.
 */
void Point::erase(char ch) const {
    gotoxy(pos); // Move the cursor to the point's position
	if (Board::pos_inbound(pos)) std::cout << ch; // Restore the character from the board
}