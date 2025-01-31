#pragma once
#include "Coord.h"

// Enum for the control keys
enum class Ctrl : char {
    DEF,         // Default control
    UP = 'w',    // Move up
    DOWN = 'x',  // Move down
    LEFT = 'a',  // Move left
    RIGHT = 'd', // Move right
    STAY = 's',  // Stay in place
    HIT = 'p',     //Hit with hammer
    ESC = 27,    // Escape key
};

// Enum for game state
enum class Game_State {
	TERMINATE, // Game is terminated
	EXIT, // Exit mid-game
    RUN, // Game is running
    PAUSE, // Game is paused
	RETRY, // Level is reset
    FAIL, // Game finished unsuccessfully
    SUCCESS = 6,// Game finished successfully
    NOT_OPEN = 6,// level file not open
	IDLE, // Game is idle
};

// Enum for the game levels
enum class Difficulty : char {
    EASY = '1',
    MEDIUM,
    HARD,
};

// Enum for the score formula
enum class Points {
    ENEMY_HIT = 2, // Points gained when hitting an enemy
    PAULINE_RESCUED = 10, // Points gained when rescuing Pauline
    LIFE_LOST = -5, // Points lost when losing a life
    BONUS_LIFE_THRESHOLD = 15,  // Points threshold for gaining an extra life
	GAME_COMPLETE = 20, // Points gained when completing the game
};

// Enum for the game modes
enum class Game_Mode {
	REGULAR, // Regular game mode
	SAVE, // Save game mode
	LOAD, // Load game mode
	SILENT, // Silent load game mode
	INVALID, // Invalid game mode
};

// Enum for the result types
enum class Result_Type {
	LIFE_LOST = 'L',// Mario lost life 
	FINISH_SCREEN = 'F',// Mario finished the screen
    SCORE_GAINED = 'S',// How much score mario gained
};

enum class File_Type {
	RES, // Pair for the result
	STEPS, // Pair for the steps
};

// Const to hold the screen dimensions
constexpr size_t SCREEN_WIDTH = 80; // Width of the screen
constexpr size_t SCREEN_HEIGHT = 25; // Height of the screen

// Const to hold standart values for invalid pos
static const Coordinates INVALID(-1, -1);