#include "Utils.h"

/**
 * @brief Moves the console cursor to the specified position.
 * @param pos The coordinates to move the cursor to.
 * @note Created by Amir Kirsh
 */
void gotoxy(Coordinates pos) {
    std::cout.flush();
    COORD coord; // Create a COORD structure
    coord.X = pos.x;
    coord.Y = pos.y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // move the cursor
}

/**
 * @brief Moves the console cursor to the specified position.
 * @param x The x-coordinate to move the cursor to.
 * @param y The y-coordinate to move the cursor to.
 * @note Created by Amir Kirsh
 */
void gotoxy(int x, int y) {
    std::cout.flush();
    COORD coord = { (short)x, (short)y }; // Create a COORD structure
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); // move the cursor
}

/**
 * @brief Shows or hides the console cursor based on the flag parameter.
 * @param flag If true, the cursor is shown; if false, the cursor is hidden.
 * @note Created by Amir Kirsh
 */
void show_cursor(bool flag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = flag; // Set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo); // Set the cursor info
}

/**
 * @brief Gets a character from a specific console screen buffer location.
 * @param pos The coordinates to get the character from.
 * @return The character at the specified position, or Board::ERR if an error occurs.
 * @note Created by copilot
 */
char getch_console(Coordinates pos) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        return Board::ERR;
    }

    CHAR_INFO charInfo;
    COORD coord = { (SHORT)pos.x, (SHORT)pos.y };
    SMALL_RECT readRegion = { (SHORT)pos.x, (SHORT)pos.y, (SHORT)pos.x, (SHORT)pos.y };
    COORD bufferSize = { 1, 1 };

    if (!ReadConsoleOutput(hConsole, &charInfo, bufferSize, { 0, 0 }, &readRegion) || !pos_inbound(pos)) {
        return Board::ERR;
    }

    return charInfo.Char.AsciiChar;
}

/**
 * @brief Clears the console screen.
 * @note Created by copilot
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
 * @brief Checks if the x-coordinate is within the game bounds.
 * @param x The x-coordinate to check.
 * @return True if the x-coordinate is within the game bounds, false otherwise.
 */
bool x_inbound(int x) {
    return (x >= 0 && x < Screen_dim::X); // Check if the x-coordinate is within the game bounds
}

/**
 * @brief Checks if the y-coordinate is within the game bounds.
 * @param y The y-coordinate to check.
 * @return True if the y-coordinate is within the game bounds, false otherwise.
 */
bool y_inbound(int y) {
    return (y >= 0 && y < Screen_dim::Y); // Check if the y-coordinate is within the game bounds
}

/**
 * @brief Checks if the position is within the game bounds.
 * @param pos The coordinates to check.
 * @return True if the position is within the game bounds, false otherwise.
 */
bool pos_inbound(Coordinates pos) {
    return (x_inbound(pos.x) && y_inbound(pos.y)); // Check if the position is within the game bounds
}


