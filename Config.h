#pragma once

// Enum for the control keys
enum class Ctrl : char {
    DEF,         // Default control
    UP = 'w',    // Move up
    DOWN = 'x',  // Move down
    LEFT = 'a',  // Move left
    RIGHT = 'd', // Move right
    STAY = 's',  // Stay in place
    ESC = 27,    // Escape key
};

// Enum for game state
enum class Game_State {
	TERMINATE, // Game is terminated
    RUN, // Game is running
    PAUSE, // Game is paused
	LVL_RESET, // Level is reset
    FIN_FAIL, // Game finished unsuccessfully
    FIN_SUC, // Game finished successfully
	IDLE, // Game is idle
};

// Enum for the game levels
enum class Difficulty : char {
    EASY = '1',
    MEDIUM,
    HARD,
};

// Const to hold the screen dimensions
constexpr size_t SCREEN_WIDTH = 80; // Width of the screen
constexpr size_t SCREEN_HEIGHT = 25; // Height of the screen

