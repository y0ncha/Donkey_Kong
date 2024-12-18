#pragma once

#include <iostream>
#include "Utils.h"
#include "Coord.h"
#include "Config.h"

/**
 * @class Board
 * Represents the game board and its functionalities.
 */
class Board {

public:
    // Enum for game elements
    enum Consts {
        MARIO = '@', // Character representing Mario
        DONKEY_KONG = '&', // Character representing Donkey Kong
        PAULINE = '$', // Character representing Pauline

        LADDER = 'H', // Character representing a ladder
        BARREL = 'O', // Character representing a barrel
        AIR = ' ',  // Representation of air (empty space)

        FLOOR = '=', // Character representing a floor
        FLOOR_L = '<', // Character representing a left-sloping floor
        FLOOR_R = '>', // Character representing a right-sloping floor

        ERR = '\0', // Error character

        MARIO_X0 = 40, // Default Mario's position on the x-axis
        MARIO_Y0 = 23, // Default Mario's position on the y-axis

        DKONG_X0 = 35, // Default Donkey Kong's position on the x-axis
        DKONG_Y0 = 6,   // Default Donkey Kong's position on the y-axis

        HRTS_DISP_X = 20, // Initial x-coordinate for the hearts display
        HRTS_DISP_Y = 0, // Initial y-coordinate for the hearts display
    };

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

    // Checks if the x-coordinate is within the game bounds
    static bool y_inbound(int y);

    // Checks if the y-coordinate is within the game bounds
    static bool x_inbound(int x);

    // Checks if the position is within the game bounds
    static bool pos_inbound(Coordinates pos);

private:
    // Layout of the game board, represented as a 2D array of characters
    static char board_layout[Screen_dim::Y][Screen_dim::X + 1];
};


