#pragma once

/**  
* Defines constants for game area dimensions, character controls,  
* game characters, and game elements.  
*/

// Enum for game area dimensions
enum DIM {
    MAX_X = 80, // Maximum width of the game area
    MAX_Y = 25  // Maximum height of the game area
};

// Enum for initial positions of characters
enum POS { 
    MARIO_X0 = 40, // Default Mario's position on the x-axis
    MARIO_Y0 = 23, // Default Mario's position on the y-axis
    
    DKONG_X0 = 40, // Default Donkey Kong's position on the x-axis
    DKONG_Y0 = 3   // Default Donkey Kong's position on the y-axis
};

// Enum for general game settings
enum GEN {
    ERR = '\0', // Error character
    JMP_H = 2, // Height of the jump
    LIVES = 3, // Number of lives
    AIR = ' '  // Representation of air (empty space)
};

// Enum for game characters
enum CHARS {
    MARIO = '@', // Character representing Mario
    DONKEY_KONG = '&', // Character representing Donkey Kong
    PAULINE = '$' // Character representing Pauline
};

// Enum for game elements
enum ELMNT {
    LADDER = 'H', // Character representing a ladder
    BARREL = 'O' // Character representing a barrel
};

// Enum for floor elements
enum FLR {
    FLOOR = '=', // Character representing a floor
    FLOOR_L = '<', // Character representing a left-sloping floor
    FLOOR_R = '>' // Character representing a right-sloping floor
};

enum ENTRY_MENU
{
    START = '1',
    KEYS = '8',
    EXIT = '9'

};

// Character controls
static constexpr char
UP = 'w', // Move up
DOWN = 'x', // Move down
LEFT = 'a', // Move left
RIGHT = 'd', // Move right
STAY = 's', // Stay in place
ESC = 27; // Escape key
