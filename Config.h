#pragma once


// Enum for the control keys
enum Ctrl {
    UP = 'w',    // Move up
    DOWN = 'x',  // Move down
    LEFT = 'a',  // Move left
    RIGHT = 'd', // Move right
    STAY = 's',  // Stay in place
    ESC = 27,    // Escape key
    DEF = '\0'   // Default control
};

// Enum for game state
enum Game_State {
	TERMINATE, // Game is terminated
    RUN, // Game is running
    PAUSE, // Game is paused
	LVL_RESET, // Level is reset
    FIN_FAIL, // Game finished unsuccessfully
    FIN_SUC, // Game finished successfully
	IDLE, // Game is idle
};

// Enum for the game levels
enum Difficulty {
    EASY = '1',
    MEDIUM = '2',
    HARD = '3'
};

// Enum for the game levels
enum Screen_dim {
    X = 80, // Maximum width of the game area
    Y = 25  // Maximum height of the game area
};

