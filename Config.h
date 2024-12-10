#pragma once

/*
* General game Configurations
*/
enum CTRL { // Character controls
    UP = 'w', // Move up
    DOWN = 'x', // Move down
    LEFT = 'a', // Move left
    RIGHT = 'd', // Move right
    STAY = 's', // Stay in place
    ESC = 27 // Escape key
};

enum SCRN_DIM {
	MAX_X = 80, // Maximum width of the game area
	MAX_Y = 25 // Maximum height of the game area
};
