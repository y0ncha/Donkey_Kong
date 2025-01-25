#include "Game.h"

/**
 * @brief Constructs a 'Base_Game' object according to the specified Game_Mode.
 */
Game::Game(Game_Mode mode) noexcept : mode(mode) {
    configure_game();
}

/**
 * @brief Destructor for the Game class.
 */
Game::~Game() {

    if (mode != Game_Mode::INVALID) {
        delete pGame;
    }
}

/**
 * @brief Move constructor for the Game class.
 * @param other The Game object to move.
 */
Game::Game(Game&& other) noexcept : pGame(other.pGame), mode(other.mode) {
    other.pGame = nullptr;
    other.mode = Game_Mode::INVALID;
}

/**
 * @brief Move assignment operator for the Game class.
 * @param other The Game object to move.
 * @return A reference to the assigned Game object.
 */
Game& Game::operator=(Game&& other) noexcept {
    if (this != &other) {
        delete pGame; // Release the current resource
        pGame = other.pGame; // Transfer ownership
        mode = other.mode; // Transfer Game_Mode
        other.pGame = nullptr; // Leave the moved-from object in a valid state
        other.mode = Game_Mode::INVALID; // Leave the moved-from object in a valid state
    }
    return *this;
}

/**
 * @brief Create the matching Game_Mode object and set it to the game pointer.
 * @param Game_Mode The Game_Mode to set.
 * @return True if the Game_Mode was set successfully, false if the Game_Mode is invalid.
 */
void Game::configure_game() {

    if (mode == Game_Mode::REGULAR || mode == Game_Mode::SAVE) {
        pGame = new Play_Game(mode);
    }
    else if (mode == Game_Mode::LOAD || mode == Game_Mode::SILENT) {
        pGame = new Replay_Game(mode);
    }
    else {
        pGame = nullptr;
    }
}