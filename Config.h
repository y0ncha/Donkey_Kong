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

// Enum for the menu options
enum ENTRY_MENU {
    START = '1',// Start the game
    KEYS = '8',// Show the keys
    EXIT = '9'// Exit the game
};

// Enum for the menu types
enum MENU_TYPES{
    START_MENU = 0,//Show the start menu
    PAUSE_MENU = 1//Show the pause menu
};
