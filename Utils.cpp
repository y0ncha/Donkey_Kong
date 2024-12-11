#include "Utils.h"

/**
 * ---Created by Amir Kirsh--- 
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
 * ---Created by Amir Kirsh---
 * Moves the console cursor to the specified position.
 */
void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord = { (short)x, (short)y }; // Create a COORD structure
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // Move the cursor
}

/**
 * ---Created by Amir Kirsh---
 * Shows or hides the console cursor based on the showFlag parameter.
 */
void show_cursor(bool flag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = flag; // Set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo); // Set the cursor info
}

/**
* ---Created by copilot---
* Function to get a character from a specific console screen buffer location
*/
char getch_console(Coordinates pos) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return '\0';
    }

    CHAR_INFO charInfo;
    COORD coord = { (SHORT)pos.x, (SHORT)pos.y };
    SMALL_RECT readRegion = { (SHORT)pos.x, (SHORT)pos.y, (SHORT)pos.x, (SHORT)pos.y };
    COORD bufferSize = { 1, 1 };

    if (!ReadConsoleOutput(hConsole, &charInfo, bufferSize, { 0, 0 }, &readRegion) || !pos_inbound(pos)) {
        return '\0';
    }

    return charInfo.Char.AsciiChar;
}

/**
 * ---Created by copilot---
 * Clears the console screen.
 */
void clear_screen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return;
    }

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, homeCoords, &count)) {
        return;
    }

    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count)) {
        return;
    }

    SetConsoleCursorPosition(hConsole, homeCoords);
}

/**
 * Checks if the x-coordinate is within the game bounds.
 */
bool x_inbound(int x) {
    return (x >= 0 && x < Screen_dim::X); // Check if the x-coordinate is within the game bounds
}

/**
 * Checks if the y-coordinate is within the game bounds.
 */
bool y_inbound(int y) {
    return (y >= 0 && y < Screen_dim::Y); // Check if the y-coordinate is within the game bounds
}

/**
 * Checks if the position is within the game bounds.
 */
bool pos_inbound(Coordinates pos) {
    return (x_inbound(pos.x) && y_inbound(pos.y)); // Check if the position is within the game bounds
}
