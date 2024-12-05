#include "Board.h"


/**
 * Draws the game board by printing each row of the layout.
 * Loops through all rows (from 0 to MAX_Y-1) and prints each line to the console.
 */
void Board::print() const {

    gotoxy(0, 0);

    for (int i = 0; i < MAX_Y -1; i++) {
        std::cout << layout[i] << std::endl; // Prints each row of the preset board
    }
    std::cout << layout[MAX_Y -1];
}

/**
 * Retrieves the character at the specified position on the board.
 * Returns '\0' if the position is out of bounds.
 */
char Board::get_char(Coordinates coord) const {

    if (coord.x < 0 || coord.x >= MAX_X || coord.y < 0 || coord.y >= MAX_Y)
        return ERR;  // Return null character if out of bounds

    return layout[coord.y][coord.x];  // Return the character at the specified position
}
char Board::get_char(int x, int y) const {

    if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y)
        return ERR;  // Return null character if out of bounds

    return layout[y][x];  // Return the character at the specified position
}

void Board::set_char(Coordinates coord, char ch) {
    if (pos_inbound(coord)) { // Check if the position is within the game bounds
        layout[coord.y][coord.x] = ch; // Set the character at the specified position
    }
}
void Board::set_char(int _x, int _y, char ch) {
    if (pos_inbound({ _x, _y })) { // Check if the position is within the game bounds
        layout[_y][_x] = ch; // Set the character at the specified position
    }
}

bool Board::is_floor(Coordinates coord) const {

	char ch = get_char(coord);  // Get the character at the specified position
	return (ch == FLOOR || ch == FLOOR_L || ch == FLOOR_R);  // Return true if the character is a floor element
}

bool Board::path_clear(Coordinates coord) const{
	char ch = get_char(coord); // Get the character at the specified position
	return (ch == AIR || ch == LADDER); // Check if the path is clear
}
bool Board::path_clear(int x, int y) const {
	return path_clear({ x, y }); // Check if the path is clear
}



//test