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
        SUPER_MARIO = '8', // Character representing Mario with a hammer
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
    };

    // Enum for error codes
    enum class Err_Code {
        NO_ERR,
        MISSING_MARIO,
        MISSING_PAULINE,
        MARIO_OUTBOUND,
		PAULINE_OUTBOUND,
		SCREEN_FAIL,
		STEPS_FAIL,
		RESULT_FAIL,
    };

	// Checks if the board is valid
    const std::vector<Err_Code>& get_errors();

	// Pushes an error to the error vector
	void push_error(Err_Code err);
    
    // Prints the board on the console
    void print(int lives_left = 3) const;

    // Retrieves the character from the board at given coordinates
    char get_char(Coordinates coord) const;
    char get_char(int x, int y) const;

    // Checks if the character at the given coordinates is a floor element
    bool is_floor(Coordinates coord) const;
    bool is_floor(char ch) const;

    // Checks if the path is clear
    bool path_clear(Coordinates coord) const;
    bool path_clear(int x, int y) const;

	// Remove the hammer when picked up
    void remove_hammer();

	// Set the hammer on the board
    void reset_hammer();

    // Returns the number of entities of a given type
    size_t count_entity(Icon icon) const;

	// Retrieves the position of the entity
    Coordinates get_pos(Icon icon, size_t ind = 0) const;

    // Checks if the x-coordinate is within the game bounds
    static bool y_inbound(int y);

    // Checks if the y-coordinate is within the game bounds
    static bool x_inbound(int x);

    // Checks if the position is within the game bounds
    static bool pos_inbound(Coordinates pos);

    // Handles the input character while loading the board
    static bool is_valid_ch(Icon icon);

	// Consts for the width of the legend
	static constexpr int LEGEND_WIDTH = 20; // Width of the game board
	static constexpr int LEGEND_HEIGHT = 3; // Height of the game board

private:

    // Layout of the game board, represented as a 2D array of characters
    char board_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1];

    // Map to store the positions of entities
    mutable std::unordered_map <Icon, std::vector<Coordinates>> map;

	// Error code for the board
	std::vector<Err_Code>errors;

    // Sets the character at the given coordinates
    void set_char(Coordinates coord, char ch);
    void set_char(int x, int y, char ch);

    // Loads the board from a givven file
    void load(std::string fname);

	// Sets the legend on the board
	void set_legend();
     
	// Maps the icon to its position on the board
	Icon map_icon(Icon icon, Coordinates pos);

	// Handles the input character while loading the board
	void handle_input(std::string, int y);
};

