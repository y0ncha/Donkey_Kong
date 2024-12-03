#pragma once

/**  
* Defines constants for game area dimensions, character controls,  
* game characters, and game elements.  
*/

enum DIM {
    MAX_X = 80, // Maximum width of the game area
    MAX_Y = 25  // Maximum height of the game area
};

enum POS { // @ change
    //DEF_X = 40, // Default Mario's position on the x-axis
    //DEF_Y = 23  // Defualt Mario's position on the y-axis
    DEF_X = 63,
    DEF_Y = 17
};

enum GEN {
    ERR = '\0',
    JMP_H = 2, // Height of the jump
    LIVES = 3,  // Number of lives
    AIR = ' '
};

enum CHARS {
    MARIO = '@',
    DONKEY_KONG = '&', 
    PAULINE = '$'
};

enum ELMNT {
    LADDER = 'H',
    BARREL = 'O'
};

enum FLR {
    FLOOR = '=', 
    FLOOR_L = '<', 
    FLOOR_R = '>'
};

static constexpr char
UP = 'w',
DOWN = 'x',
LEFT = 'a',
RIGHT = 'd',
STAY = 's',
ESC = 27;
