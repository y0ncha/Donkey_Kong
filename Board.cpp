#include "Board.h"

/**
 * Draws the game board by printing each row of the layout.
 * Loops through all rows (from 0 to Screen_dim::Y-1) and prints each line to the console.
 */
void Board::print(int lives_left) const {
    gotoxy(0, 0); // move the cursor to the top-left corner of the console

	// Print the rest of the layout
    for (int i = 0; i < Screen_dim::Y - 1; i++) {
        std::cout << layout[i] << std::endl; // Prints each row of the preset board
    }
    std::cout << layout[Screen_dim::Y - 1]; // Print the last row without a newline
}

/**
 * Retrieves the character at the specified position on the board.
 * Returns ERR if the position is out of bounds.
 */
char Board::get_char(Coordinates coord) const {
    if (coord.x < 0 || coord.x >= Screen_dim::X || coord.y < 0 || coord.y >= Screen_dim::Y)
        return ERR; // Return error character if out of bounds

    return layout[coord.y][coord.x]; // Return the character at the specified position
}

/**
 * Retrieves the character at the specified position on the board.
 * Returns ERR if the position is out of bounds.
 */
char Board::get_char(int x, int y) const {
    if (x < 0 || x >= Screen_dim::X || y < 0 || y >= Screen_dim::Y)
        return ERR; // Return error character if out of bounds

    return layout[y][x]; // Return the character at the specified position
}

/**
 * Sets the character at the specified position on the board.
 * Only sets the character if the position is within bounds.
 */
void Board::set_char(Coordinates coord, char ch) {
    if (pos_inbound(coord)) { // Check if the position is within the game bounds
        layout[coord.y][coord.x] = ch; // Set the character at the specified position
    }
}

/**
 * Sets the character at the specified position on the board.
 * Only sets the character if the position is within bounds.
 */
void Board::set_char(int x, int y, char ch) {
    if (pos_inbound({ x, y })) { // Check if the position is within the game bounds
        layout[y][x] = ch; // Set the character at the specified position
    }
}

/**
 * Checks if the character / position is / holds a floor element.
 */
bool Board::is_floor(Coordinates coord) const {
    char ch = get_char(coord); // Get the character at the specified position
    return (ch == FLOOR || ch == FLOOR_L || ch == FLOOR_R); // Return true if the character is a floor element
}

/**
 * Checks if the character is a floor element.
 */
bool Board::is_floor(char ch) const {
    return (ch == Board::FLOOR || ch == Board::FLOOR_L || ch == Board::FLOOR_R); // Checks if the character is a floor element
}

/**
 * Checks if the path is clear at the specified position.
 * Returns true if the path is clear, false otherwise.
 */
bool Board::path_clear(Coordinates coord) const {
    char ch = get_char(coord); // Get the character at the specified position
    return (ch == AIR || ch == LADDER); // Check if the path is clear
}

/**
 * Checks if the path is clear at the specified position.
 * Returns true if the path is clear, false otherwise.
 */
bool Board::path_clear(int x, int y) const {
    return path_clear({ x, y }); // Check if the path is clear
}
