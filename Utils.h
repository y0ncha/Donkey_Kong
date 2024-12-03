#pragma once

#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Config.h"
#include "Coord.h"


void gotoxy(Coordinates pos);

void gotoxy(int x, int y);

void ShowConsoleCursor(bool showFlag);

bool is_floor(char ch);

bool x_inbound(int _x); // Check if the x-Coordinates is within the game bounds

bool y_inbound(int _y); //  Check if the y-Coordinates is within the game bounds

bool pos_inbound(Coordinates pos); //    Check if the position is within the game bounds
