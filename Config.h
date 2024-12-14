#pragma once

/**
 * @enum Ctrl
 * Represents character controls for the game.
 */
enum Ctrl {
    UP = 'w',    // Move up
    DOWN = 'x',  // Move down
    LEFT = 'a',  // Move left
    RIGHT = 'd', // Move right
    STAY = 's',  // Stay in place
    ESC = 27,    // Escape key
    DEF = '\0'   // Default control
};

/**
 * @enum Screen_dim
 * Represents the dimensions of the game screen.
 */
enum Screen_dim {
    X = 80, // Maximum width of the game area
    Y = 25  // Maximum height of the game area
};
