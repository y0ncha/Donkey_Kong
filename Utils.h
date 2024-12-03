#pragma once

#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Config.h"
#include "Coord.h"

// Moves the console cursor to the specified position
void gotoxy(Coordinates pos);

// Moves the console cursor to the specified position
void gotoxy(int x, int y);

// Shows or hides the console cursor based on the showFlag parameter
void ShowConsoleCursor(bool showFlag);

// Checks if the character is a floor element
bool is_floor(char ch);

// Checks if the x-coordinate is within the game bounds
bool x_inbound(int _x);

// Checks if the y-coordinate is within the game bounds
bool y_inbound(int _y);

// Checks if the position is within the game bounds
bool pos_inbound(Coordinates pos);
