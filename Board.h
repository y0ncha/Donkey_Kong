#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Coord.h"
#include "Config.h"
#include "Utils.h"

/**
 * @class Board
 * Represents the game board and its functionalities.
 */
class Board {

public:

	// Constructor for the Board class
    Board(std::string fname);

	// Enum for game elements (no use of enum class due to Icon being scoped in Board class and to alllow easy conversions to char)
    enum Icon {
        MARIO = '@', // Character representing Mario
        DONKEY_KONG = '&', // Character representing Donkey Kong
        BARREL = 'O', // Character representing a barrel
        PAULINE = '$', // Character representing Pauline
		HAMMER = 'p', // Character representing a hammer
		GHOST = 'x', // Character representing a ghost

		LEGEND = 'L', // Character representing the legend
		WALL = 'Q', // Character representing a wall
        LADDER = 'H', // Character representing a ladder
        AIR = ' ',  // Representation of air (empty space)

        FLOOR = '=', // Character representing a floor
        FLOOR_L = '<', // Character representing a left-sloping floor
        FLOOR_R = '>', // Character representing a right-sloping floor

        ERR = '\0', // Error character

        HRTS_DISP_X = 20, // Initial x-coordinate for the hearts display
        HRTS_DISP_Y = 0, // Initial y-coordinate for the hearts display
    };

    // Enum for error codes
    enum class Err_Code {
        NO_ERR,
        MISSING_MARIO,
        MISSING_PAULINE,
		FILE_NOT_FOUND,
    };

	// Checks if the board is valid
    Err_Code is_valid_board() const;
    
    // Prints the board on the console
    void print(int lives_left = 3) const;

    // Retrieves the character from the board at given coordinates
    char get_char(Coordinates coord) const;
    char get_char(int x, int y) const;

    // Sets the character at the given coordinates
    void set_char(Coordinates coord, char ch);
    void set_char(int x, int y, char ch);

    // Checks if the character at the given coordinates is a floor element
    bool is_floor(Coordinates coord) const;
    bool is_floor(char ch) const;

    // Checks if the path is clear
    bool path_clear(Coordinates coord) const;
    bool path_clear(int x, int y) const;

	// Retrieves the position of the entity
    Coordinates get_pos(Icon icon, size_t ind = 0) const;

    // Checks if the x-coordinate is within the game bounds
    static bool y_inbound(int y);

    // Checks if the y-coordinate is within the game bounds
    static bool x_inbound(int x);

    // Checks if the position is within the game bounds
    static bool pos_inbound(Coordinates pos);

	// Returns the number of entities of a given type
	size_t get_entity_count(Icon icon) const;


private:

    // Loads the board from a givven file
    bool load(std::string fname);

    // Handles the input character while loading the board
    bool is_valid_ch(Icon icon) const;
     
	// Maps the icon to its position on the board
	Icon map_icon(Icon icon, Coordinates pos);

	// Handles the input character while loading the board
	void handle_input(std::string, int y);

    // Layout of the game board, represented as a 2D array of characters
    char board_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];

    // Map to store the positions of entities
    mutable std::unordered_map <Icon, std::vector<Coordinates>> map;
};

