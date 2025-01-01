#include "Board.h"

/**
* @brief Default constructor for the Board class.
* Initializes the map with the valid entities and their corresponding characters.
* Initializes the board layout with empty characters.
*/
Board::Board(std::string fname) : map{
    {MARIO, {}},
    {DONKEY_KONG, {}},
    {PAULINE, {}},
    {HAMMER, {}},
    {GHOST, {}},
    {LEGEND, {}},
} {
    load(fname); // Load the board from the given file
}

/**
* @brief Loads the board layout from a given file while validating the input.
* Reads the file line by line and stores the layout in the board_layout vector.
* Throws an error if the file could not be opened.
* @param fname The name of the file to load the board layout from.
*/
void Board::load(std::string fname) {

	std::string buffer; // Buffer to store each line of the file
	std::ifstream file(fname); // Open the file with the given filename for reading

	if (file.is_open()) { // Check if the file is open
		for (int y = 0; y_inbound(y); y++) {
			std::getline(file, buffer); // Read each line of the file into the buffer
			handle_input(buffer, y); // Handle the input line
		}
	}
	else {
		throw std::runtime_error("Error: Could not open file " + fname); // Throw an error if the file could not be opened
	}

}

/**
 * @brief Draws the game board by printing each row of the layout.
 * Loops through all rows (from 0 to Screen_Dim::Y-1) and prints each line to the console.
 * @param lives_left The number of lives left (default is 3).
 */
void Board::print(int lives_left) const {
    gotoxy(0, 0); // Move the cursor to the top-left corner of the console

    // Print the rest of the layout
    for (int i = 0; i < Screen_Dim::Y - 1; i++) {
        std::cout << board_layout[i] << std::endl; // Print each row of the preset board
    }
    std::cout << board_layout[Screen_Dim::Y - 1]; // Print the last row without a newline
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
    return (x >= 0 && x < Screen_Dim::X); // Check if the x-coordinate is within the game bounds
}

/**
 * @brief Checks if the y-coordinate is within the game bounds.
 * @param y The y-coordinate to check.
 * @return True if the y-coordinate is within the game bounds, false otherwise.
 */
bool Board::y_inbound(int y) {
    return (y >= 0 && y < Screen_Dim::Y); // Check if the y-coordinate is within the game bounds
}

/**
 * @brief Checks if the position is within the game bounds.
 * @param pos The coordinates to check.
 * @return True if the position is within the game bounds, false otherwise.
 */
bool Board::pos_inbound(Coordinates pos) {
    return (x_inbound(pos.x) && y_inbound(pos.y)); // Check if the position is within the game bounds
}

/**
* @brief Retrieves the position of the specified entity.
* @param icon The character representing the entity.
* @param ind The index of the entity in the map.
* @return The position of the entity (if failed, returns {-1, -1}).
*/
Coordinates Board::get_pos(Icon icon, size_t ind) const {

	auto it = map.find(icon);

	if (it != map.end() && ind < map[icon].size()) {
        return map[icon][ind];
	}
    else {
        return { -1, -1 };
    }
}

/**
* @brief Checks if the character is valid.
* @param icon The character to check.
* @return True if the character is valid, false otherwise.
*/
bool Board::is_valid(Icon icon) {

    switch (icon) {
    case MARIO:
    case DONKEY_KONG:
    case PAULINE:
    case HAMMER:
    case GHOST:
    case LEGEND:
    case WALL:
    case LADDER:
    case BARREL:
    case AIR:
    case FLOOR:
    case FLOOR_L:
    case FLOOR_R:
        return true;
        break;
    default:
        return false;
        break;
    }
}

/**
* @brief Handles the input character while loading the board.
* @param icon The character to handle.
* @param pos The position of the character.
*/
Board::Icon Board::map_icon(Icon icon, Coordinates pos) {
    
    if (map.find(icon) != map.end()) {

        if (icon == GHOST || map[icon].empty()) {
            map[icon].push_back(pos);
        }
        return AIR;
    }
	return icon;
}

/**
* @brief Handles the input character while loading the board.
* @param line The line to handle.
* @param i The row index of the line.
*/
void Board::handle_input(std::string line, int y) {

    // Loop through each character in the line
    int x = 0;

    while (x_inbound(x) && x < line.size()) {

        Icon icon = static_cast<Icon>(line[x]);

        if (is_valid(icon)) { // Check if the character is valid

            board_layout[y][x] = map_icon(icon, { x, y });
        }
        else { // Set the character to AIR if it is invalid
            board_layout[y][x] = AIR;
        }
        x++;
    }
    // Fill the rest of the row with AIR if the line is shorter than Screen_Dim::X
    while (x_inbound(x)) {
        board_layout[y][x++] = AIR;
    }
}


