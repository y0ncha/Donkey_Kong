#pragma once

#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Coord.h"
#include "Board.h"

// Moves the console cursor to the specified position
void gotoxy(Coordinates pos);
void gotoxy(int x, int y);

// Clears the console screen
void clear_screen();

// Gets a character from a specific console screen buffer location
char getch_console(Coordinates pos);

// Shows or hides the console cursor based on the showFlag parameter
void show_cursor(bool showFlag);

// Checks if the x-coordinate is within the game bounds
bool x_inbound(int _x);

// Checks if the y-coordinate is within the game bounds
bool y_inbound(int _y);

// Checks if the position is within the game bounds
bool pos_inbound(Coordinates pos);

// Function to handle errors by throwing an exception with the file and line number
inline void handle_err(const std::string& message, const char* file, int line) {
    throw std::runtime_error(message + " in file " + file + " at line " + std::to_string(line));
}
