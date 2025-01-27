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

	if (display_flag) {
		gotoxy(point.pos); // Move the cursor to the point's position
		return std::cout << static_cast<char>(point.icon); // Print the point's character at the position
	}
	else {
		current_screen[point.pos.y][point.pos.x] = static_cast<char>(point.icon); // Set the point on the screen buffer
		return os;
	}
}

/**
 * @brief Draws the point at the current position.
 */
void Point::draw() const {

	if (display_flag) {
		if (Board::pos_inbound(pos)) std::cout << *this; // Print the point on the console
	}
	else {
		current_screen[pos.y][pos.x] = static_cast<char>(icon); // Set the point on the screen buffer
	}
}

/**
 * @brief Erases the point from the current position.
 * @param ch The character to restore at the point's position.
 */
void Point::erase(char ch) const {

	if (display_flag) {
		gotoxy(pos); // Move the cursor to the point's position
		if (Board::pos_inbound(pos)) std::cout << ch; // Restore the character from the board
	}
	else {
		current_screen[pos.y][pos.x] = ch; // Restore the character from the screen buffer
	}
}