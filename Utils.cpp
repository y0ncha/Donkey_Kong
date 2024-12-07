#include "Utils.h"
#include "Config.h"
#include "Coord.h"

/*---Created by Amir Kirsh--- */
/**
 * Moves the console cursor to the specified position.
 */
void gotoxy(Coordinates pos) {
    std::cout.flush();
    COORD coord; // Create a COORD structure
    coord.X = pos.x;
    coord.Y = pos.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor
}

/**
 * Moves the console cursor to the specified position.
 */
void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord = { x, y }; // Create a COORD structure
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor
}

/*---Created by Amir Kirsh--- */
/**
 * Shows or hides the console cursor based on the showFlag parameter.
 */
void ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // Set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

/**
 * Checks if the x-coordinate is within the game bounds.
 */
bool x_inbound(int _x) {
    return (_x >= 0 && _x < MAX_X); // Check if the x-coordinate is within the game bounds
}

/**
 * Checks if the y-coordinate is within the game bounds.
 */
bool y_inbound(int _y) {
    return (_y >= 0 && _y < MAX_Y); // Check if the y-coordinate is within the game bounds
}

/**
 * Checks if the position is within the game bounds.
 */
bool pos_inbound(Coordinates pos) {
    return (x_inbound(pos.x) && y_inbound(pos.y)); // Check if the position is within the game bounds
}
