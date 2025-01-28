#pragma once

#include <windows.h>
#include <iostream>
#include <stdexcept>
#include <string>
#include "Config.h"
#include <chrono>
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
std::string remove_ext(const std::string& filename);
std::string remove_ext(const std::string& filename, const std::string& toremove);

/**
 * @brief Starts the timer.
 * @return The start time.
 */
inline std::chrono::steady_clock::time_point start_timer() {
    return std::chrono::high_resolution_clock::now();
}

/**
 * @brief Stops the timer and returns the duration in minutes and seconds.
 * @param start_time The start time.
 * @return The duration in minutes and seconds.
 */
inline std::pair<int, int> stop_timer(auto start_time) {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end_time - start_time).count();

    int minutes = static_cast<int>(duration) / 60;
    int seconds = static_cast<int>(duration) % 60;
    return { minutes, seconds };
}

/**
 * @brief Overloads the extraction operator for the Difficulty enum class.
 * @param in The input stream.
 * @param diff The Difficulty enum class.
 * @return The input stream.
 */
inline std::istream& operator>>(std::istream& in, Difficulty& diff) {
    int value;
    if (in >> value) {
        diff = static_cast<Difficulty>(value);
    }
    return in;
}

/**
 * @brief Empty string to use as a default value.
 */
static std::string empty = "";

// Current screen layout
extern char current_screen[SCREEN_HEIGHT][SCREEN_WIDTH + 1];

// Flag to display the screen layout
extern bool display_flag;

/**
 * @brief Overloads the insertion operator for the Difficulty enum class.
 * @param out The output stream.
 * @param diff The Difficulty enum class.
 * @return The output stream.
 */
inline std::ostream& operator<<(std::ostream& os, const char array[][SCREEN_WIDTH + 1]) {
    for (size_t i = 0; i < SCREEN_HEIGHT; ++i) {
        os << array[i] << std::endl;
    }
    return os;
}

/**
 * @brief Overloads the comparison operators for the Ctrl enum class.
 * @param lhs The character to compare.
 * @param rhs The Ctrl enum class to compare.
 */
bool operator!=(const char& lhs, const Ctrl& rhs);
bool operator!=(const Ctrl& lhs, const char& rhs);
bool operator==(const char& lhs, const Ctrl& rhs);
bool operator==(const Ctrl& lhs, const char& rhs);
bool operator<(const char& lhs, const Ctrl& rhs);
bool operator<(const Ctrl& lhs, const char& rhs);
bool operator>(const char& lhs, const Ctrl& rhs);
bool operator>(const Ctrl& lhs, const char& rhs);
bool operator<=(const char& lhs, const Ctrl& rhs);
bool operator<=(const Ctrl& lhs, const char& rhs);
bool operator>=(const char& lhs, const Ctrl& rhs);
bool operator>=(const Ctrl& lhs, const char& rhs);
