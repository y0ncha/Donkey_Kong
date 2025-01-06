#include "Ghost.h"

/**
 * @brief Constructor for the Ghost class.
 * @param pBoard Pointer to the game board.
 */
Ghost::Ghost(const Board* pBoard) : Entity(pBoard, Board::GHOST, { -1, -1 }) {
    dir = init_dir();
    last_dx = dir.x;
    active = true;
}

/**
 * @brief Sets the game board for the ghost.
 * @param pBoard Pointer to the game board.
 */
void Ghost::set_board(const Board* pBoard) {
    board = pBoard;
}

/**
 * @brief Checks if the ghost's next move is valid.
 * @return True if the move is valid, false otherwise.
 */
bool Ghost::valid_move() {
    if ((board->is_floor(point.pos + dir + Coordinates{0, 1})) && (Board::pos_inbound(point.pos + dir)))
        return true;
    else {
        return false;
    }
}

/**
 * @brief Initializes the direction of the ghost.
 * @return The initial direction of the ghost.
 */
Coordinates Ghost::init_dir() {
    int dx = rand() % 2 ? 1 : -1;
    dir = {dx, 0};
    if (valid_move())
        dir = { dx, 0 };
    else
        dir = { -dx, 0 };
    last_dx = dir.x;
    return dir;
}

/**
 * @brief Updates the direction of the ghost based on probability.
 */
void Ghost::update_dirc() {
    int probability = rand() % 100;
    if (probability < 5) {
        dir.x = -dir.x;
        if (!valid_move()) {
            dir.x = -dir.x;
        }
    } else {
        if (!valid_move()) {
            dir.x = -dir.x;
        }
    }
    last_dx = dir.x;
}

/**
 * @brief Moves the ghost by updating its direction and stepping.
 */
void Ghost::move() {
    update_dirc();
    step();
}

/**
 * @brief Resets the ghost to its initial state.
 */
void Ghost::reset() {
    vanish();
    dir = init_dir();
    active = true;
}

/**
 * @brief Handles the falling logic for the ghost.
 */
void Ghost::handle_falling() {
    // Implementation of handle_falling
}

/**
 * @brief Handles collision logic for the ghost.
 * @return The type of object the ghost collides with.
 */
char Ghost::handle_collision() {
    // Implementation of handle_collision
    return ' ';
}

/**
 * @brief Updates the direction of the ghost based on a key input.
 * @param key The key input to update the direction.
 */
void Ghost::update_dir(char key) {
    // Implementation of update_dir
}

/**
 * @brief Sets the direction of the ghost.
 * @param coord The new direction coordinates.
 */
void Ghost::set_dir(Coordinates coord) {
    dir = coord;
}

/**
 * @brief Inverts the direction of the ghost.
 */
void Ghost::invert_dir() {
    dir.x = -dir.x;
    last_dx = dir.x;
}

/**
 * @brief Checks if the ghost has hit Mario.
 * @return True if the ghost has hit Mario, false otherwise.
 */
bool Ghost::is_hit_mario() const {
    return (getch_console(point.pos) == Board::MARIO || getch_console(point.pos + dir) == Board::MARIO);
}

/**
 * @brief Checks if the ghost is active.
 * @return True if the ghost is active, false otherwise.
 */
bool Ghost::is_active() const {
    return active;
}

/**
 * @brief Activates the ghost.
 */
void Ghost::activate() {
    active = true;
}