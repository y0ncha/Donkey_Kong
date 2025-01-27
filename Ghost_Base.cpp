#include "Ghost_Base.h"

/**
 * @brief Constructor for the Ghost_Base class.
 * @param pBoard Pointer to the game board.
 * @param icon Character representing the Regular_Ghost entity.
 * @param init_pos Initial position of the Regular_Ghost entity.
 */
Ghost_Base::Ghost_Base(const Board* pBoard, char icon, Coordinates init_pos)
    : Entity(pBoard, icon, init_pos) {
    init_dir();
    set_last_dx(get_dx());
    active = true;
}

/**
 * @brief Checks if the Regular_Ghost's next move is valid.
 * @return True if the move is valid, false otherwise.
 */
bool Ghost_Base::valid_move() {

    // Get the character of the next position floor
    char next_floor = board->get_char(get_pos() + get_dir() + Coordinates{ 0, 1 });

    // Check if the next move is above floor and if is inbound
    return board->is_floor(next_floor) && board->path_clear(get_pos() + get_dir());
}

/**
 * @brief Initializes the direction of the Regular_Ghost.
 * @return The initial direction of the Regular_Ghost.
 */
Coordinates Ghost_Base::init_dir() {

    int dx = rand() % 2 ? 1 : -1;
    Entity::set_dir(dx, 0);

    if (!valid_move()) {
        invert_dir();
    }
    return get_dir();
}

/**
 * @brief Updates the direction of the Regular_Ghost based on probability.
 *        The Regular_Ghost has a small chance to change direction randomly.
 */
bool Ghost_Base::update_dir(char key) {

    int probability = rand() % 100;

    // Small chance to change direction
    if (probability < 5) {
        invert_dir();
    }

    // Ensure the new direction is valid
    if (!valid_move()) {
        invert_dir();
    }
    return true;
}

/**
 * @brief Resets the Regular_Ghost to its initial state.
 */
void Ghost_Base::reset() {
    Entity::reset();
    init_dir();
    active = true;
}

/**
 * @brief Kills the Regular_Ghost by making it vanish and setting it to inactive.
 */
void Ghost_Base::kill() {
    Entity::reset();
    active = false;
}

/**
 * @note Empty implemantation of handle_falling.
 */
void Ghost_Base::handle_falling() {}

/**
 * @note Empty implemantation of handle_collision.
 */
char Ghost_Base::handle_collision() { return ' '; }

/**
 * @brief Sets the direction of the Regular_Ghost.
 * @param coord The new direction coordinates.
 */
void Ghost_Base::set_dir(Coordinates coord) {
    Entity::set_dir(coord);
}

/**
 * @brief Checks if the Regular_Ghost has hit Mario.
 * @return True if the Regular_Ghost has hit Mario, false otherwise.
 */
bool Ghost_Base::is_hit_mario() const {
    char current = getch_console(get_pos());
    char next = getch_console(get_pos() + get_dir());

    return (current == Board::MARIO || current == Board::SUPER_MARIO ||
        next == Board::MARIO || next == Board::SUPER_MARIO);
}

/**
 * @brief Checks if the Regular_Ghost is active.
 * @return True if the Regular_Ghost is active, false otherwise.
 */
bool Ghost_Base::is_active() const {
    return active;
}

/**
 * @brief Activates the Regular_Ghost.
 */
void Ghost_Base::activate() {
    active = true;
}