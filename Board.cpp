#include "Board.h"

// todo delete
#include <iostream>
#include <filesystem>

void Board::load(std::string fname) {

	std::ifstream file(fname); // Open the file with the given filename for reading

	if (!file.is_open()) {
		handle_err("Error opening file", __FILE__, __LINE__); // Handle the error if the file cannot be opened
	}

	std::string line; // String to hold each line of the file

	int row = 0; // Counter for the current row

	while (std::getline(file, line)) { // Read each line of the file
		if (row >= Screen_dim::Y) {
			break; // Break if the number of lines exceeds the screen height
		}
		strncpy_s(board_layout[row], line.c_str(), Screen_dim::X); // Copy the line to the current row
		board_layout[row][Screen_dim::X] = '\0'; // Null-terminate the string
        row++; // Increment the row counter
	}
	file.close(); // Close the file
}

/**
 * @brief Draws the game board by printing each row of the layout.
 * Loops through all rows (from 0 to Screen_dim::Y-1) and prints each line to the console.
 * @param lives_left The number of lives left (default is 3).
 */
void Board::print(int lives_left) const {
    gotoxy(0, 0); // Move the cursor to the top-left corner of the console

    // Print the rest of the layout
    for (int i = 0; i < Screen_dim::Y - 1; i++) {
        std::cout << board_layout[i] << std::endl; // Print each row of the preset board
    }
    std::cout << board_layout[Screen_dim::Y - 1]; // Print the last row without a newline
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

    return board_layout[coord.y][coord.x]; // Return the character at the specified position
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
        board_layout[coord.y][coord.x] = ch; // Set the character at the specified position
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

/**
* @brief Checks if the x-coordinate is within the game bounds.
* @param x The x-coordinate to check.
* @return True if the x-coordinate is within the game bounds, false otherwise.
*/
bool Board::x_inbound(int x) {
    return (x >= 0 && x < Screen_dim::X); // Check if the x-coordinate is within the game bounds
}

/**
 * @brief Checks if the y-coordinate is within the game bounds.
 * @param y The y-coordinate to check.
 * @return True if the y-coordinate is within the game bounds, false otherwise.
 */
bool Board::y_inbound(int y) {
    return (y >= 0 && y < Screen_dim::Y); // Check if the y-coordinate is within the game bounds
}

/**
 * @brief Checks if the position is within the game bounds.
 * @param pos The coordinates to check.
 * @return True if the position is within the game bounds, false otherwise.
 */
bool Board::pos_inbound(Coordinates pos) {
    return (x_inbound(pos.x) && y_inbound(pos.y)); // Check if the position is within the game bounds
}

/*
// Layout of the game board, represented as a 2D array of characters
char Board::board_layout[Screen_dim::Y][Screen_dim::X + 1] = {
    // 01234567890123456789012345678901234567890123456789012345678901234567890123456789
      "             LIVES:                   LEVEL 1        POINTS : 00                ",// 0
      "================================================================================",// 1
      "                                                                                ",// 2
      "                                   $                                            ",// 3
      "     =============            ==========                                        ",// 4
      "        H                      H                                                ",// 5    
      "        H                      H   &                                            ",// 6 
      "==================>====== =======<<=>>===============  =======================  ",// 7
      "                                     H                                  H       ",// 8
      "                                     H                                  H       ",// 9
      "                          ============         ========================<<<==    ",// 10
      "                 ========                                      H                ",// 11
      "                        H             ======>>>                H                ",// 12
      "                        H               H                      H                ",// 13
      "                        H               H      ===========   ==========         ",// 14
      "         ==================             H                H         H            ",// 15
      "                H                       H                H         H            ",// 16
      "                H          =================<<<==============<<<   H            ",// 17
      "                H           H                                      H            ",// 18
      "                H           H                                      H            ",// 19
      "              >>>===============                        ==================      ",// 20
      "                              H                                                 ",// 21
      "                              H                                                 ",// 22
      "                              H                                                 ",// 23
      "=============================================================================<<<" // 24
};
*/