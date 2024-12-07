#pragma once

#include "Coord.h"
/**  
* Defines constants for game area dimensions, character controls etc.  
*/

enum CTRL{ // Character controls
    UP = 'w', // Move up
    DOWN = 'x', // Move down
    LEFT = 'a', // Move left
    RIGHT = 'd', // Move right
    STAY = 's', // Stay in place
    ESC = 27 // Escape key
};

enum DIM {
    MAX_X = 80, // Maximum x-coordinate
    MAX_Y = 25  // Maximum y-coordinate
};