#pragma once

#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Coord.h"
#include "Board.h"

/**
 * @brief Moves the console cursor to the specified position.
 * @param pos The coordinates to move the cursor to.
 */
void gotoxy(Coordinates pos);

/**
 * @brief Moves the console cursor to the specified position.
 * @param x The x-coordinate to move the cursor to.
 * @param y The y-coordinate to move the cursor to.
 */
void gotoxy(int x, int y);

/**
 * @brief Clears the console screen.
 */
void clear_screen();

/**
 * @brief Gets a character from a specific console screen buffer location.
 * @param pos The coordinates to get the character from.
 * @return The character at the specified position, or Board::ERR if an error occurs.
 */
char getch_console(Coordinates pos);

/**
 * @brief Shows or hides the console cursor based on the showFlag parameter.
 * @param showFlag If true, the cursor is shown; if false, the cursor is hidden.
 */
void show_cursor(bool showFlag);

/**
 * @brief Handles errors by throwing an exception with the file and line number.
 * @param message The error message.
 * @param file The file where the error occurred.
 * @param line The line number where the error occurred.
 */
inline void handle_err(const std::string& message, const char* file, int line) {
    throw std::runtime_error(message + " in file " + file + " at line " + std::to_string(line));
}

/**
 * @brief Removes the ".txt" extension from a filename.
 * @param filename The filename to remove the extension from.
 * @return The filename without the ".txt" extension.
 */
std::string remove_txt_ext(const std::string& filename);

/**
 * @brief Overloads the compersion operators for the Ctrl enum class.
 * @param lhs The character to compare.
 * @param rhs The Ctrl enum class to compare.
 */
bool operator!=(const char& lhs, const Ctrl& rhs);
bool operator!=(const Ctrl& lhs, const char& rhs);
bool operator==(const char& lhs, const Ctrl& rhs);
bool operator==(const Ctrl& lhs, const char& rhs);
bool operator<(const char& lhs, const Ctrl& rhs);
bool operator<(const Ctrl & lhs, const char& rhs);
bool operator>(const char& lhs, const Ctrl& rhs);
bool operator>(const Ctrl& lhs, const char& rhs);
bool operator<=(const char& lhs, const Ctrl& rhs);
bool operator<=(const Ctrl& lhs, const char& rhs);
bool operator>=(const char& lhs, const Ctrl& rhs);
bool operator>=(const Ctrl& lhs, const char& rhs);
