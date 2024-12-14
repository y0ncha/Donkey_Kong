#include "Board.h"

/**
 * @brief Draws the game board by printing each row of the layout.
 * Loops through all rows (from 0 to Screen_dim::Y-1) and prints each line to the console.
 * @param lives_left The number of lives left (default is 3).
 */
void Board::print(int lives_left) const {
    gotoxy(0, 0); // Move the cursor to the top-left corner of the console

    // Print the rest of the layout
    for (int i = 0; i < Screen_dim::Y - 1; i++) {
        std::cout << layout[i] << std::endl; // Print each row of the preset board
    }
    std::cout << layout[Screen_dim::Y - 1]; // Print the last row without a newline
}

/**
 * @brief Retrieves the character at the specified position on the board.
 * Returns ERR if the position is out of bounds.
 * @param coord The coordinates of the position.
 * @return The character at the specified position.
 */
char Board::get_char(Coordinates coord) const {
    if (!pos_inbound(coord))
        return ERR; // Return error character if out of bounds

    return layout[coord.y][coord.x]; // Return the character at the specified position
}

/**
 * @brief Retrieves the character at the specified position on the board.
 * Returns ERR if the position is out of bounds.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @return The character at the specified position.
 */
char Board::get_char(int x, int y) const {
    return get_char({ x, y }); // Delegate to the other get_char method
}

/**
 * @brief Sets the character at the specified position on the board.
 * Only sets the character if the position is within bounds.
 * @param coord The coordinates of the position.
 * @param ch The character to set at the specified position.
 */
void Board::set_char(Coordinates coord, char ch) {
    if (pos_inbound(coord)) { // Check if the position is within the game bounds
        layout[coord.y][coord.x] = ch; // Set the character at the specified position
    }
}

/**
 * @brief Sets the character at the specified position on the board.
 * Only sets the character if the position is within bounds.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @param ch The character to set at the specified position.
 */
void Board::set_char(int x, int y, char ch) {
    set_char({ x, y }, ch); // Delegate to the other set_char method
}

/**
 * @brief Checks if the character / position is / holds a floor element.
 * @param coord The coordinates of the position.
 * @return True if the position holds a floor element, false otherwise.
 */
bool Board::is_floor(Coordinates coord) const {
    char ch = get_char(coord); // Get the character at the specified position
    return is_floor(ch); // Delegate to the other is_floor method
}

/**
 * @brief Checks if the character is a floor element.
 * @param ch The character to check.
 * @return True if the character is a floor element, false otherwise.
 */
bool Board::is_floor(char ch) const {
    return (ch == FLOOR || ch == FLOOR_L || ch == FLOOR_R); // Check if the character is a floor element
}

/**
 * @brief Checks if the path is clear at the specified position.
 * Returns true if the path is clear, false otherwise.
 * @param coord The coordinates of the position.
 * @return True if the path is clear, false otherwise.
 */
bool Board::path_clear(Coordinates coord) const {
    char ch = get_char(coord); // Get the character at the specified position
    return (ch == AIR || ch == LADDER); // Check if the path is clear
}

/**
 * @brief Checks if the path is clear at the specified position.
 * Returns true if the path is clear, false otherwise.
 * @param x The x-coordinate of the position.
 * @param y The y-coordinate of the position.
 * @return True if the path is clear, false otherwise.
 */
bool Board::path_clear(int x, int y) const {
    return path_clear({ x, y }); // Delegate to the other path_clear method
}
