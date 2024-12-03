#include "Utils.h"
#include "Config.h"
#include "Coord.h"

/*---Created by Amir Kirsh--- */
void gotoxy(Coordinates pos) {

    std::cout.flush();
    COORD coord; // Create a COORD structure 
    coord.X = pos.x;
	coord.Y = pos.y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

void gotoxy(int x, int y) {

    std::cout.flush();
	COORD coord = { x, y }; // Create a COORD structure

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor 
}

/*---Created by Amir Kirsh--- */
void ShowConsoleCursor(bool showFlag) {

    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

bool is_floor(char ch) {
    return (ch == FLOOR || ch == FLOOR_L || ch == FLOOR_R); // Checks if the character is a floor element
}

bool x_inbound(int _x) {

    return (_x >= 0 && _x < MAX_X); // Check if the x-Coordinates is within the game bounds
}

bool y_inbound(int _y) {
    return (_y >= 0 && _y < MAX_Y); // Check if the y-Coordinates is within the game bounds
}

bool pos_inbound(Coordinates pos) {
    return (x_inbound(pos.x) && y_inbound(pos.y)); // Check if the position is within the game bounds
}

