#include "Ghost.h"

/**
 * @brief Constructor for the Ghost class.
 * @param pBoard Pointer to the game board.
 */
Ghost::Ghost(const Board* pBoard) : Entity(pBoard, Board::GHOST, { -1, -1 }) {
    init_dir();
	set_last_dx(get_dx());
    active = true;
}

/**
 * @brief Checks if the ghost's next move is valid.
 * @return True if the move is valid, false otherwise.
 */
bool Ghost::valid_move() {

	// Get the character of the next position floor
	char next_floor = board->get_char(get_pos() + get_dir() + Coordinates{0, 1});

	// Check if the next move is above floor and if is inbound
	return board->is_floor(next_floor) && board->path_clear(get_pos() + get_dir());
}

/**
 * @brief Initializes the direction of the ghost.
 * @return The initial direction of the ghost.
 */
Coordinates Ghost::init_dir() {

    int dx = rand() % 2 ? 1 : -1;
	Entity::set_dir(dx, 0);

	if (!valid_move()) {
		invert_dir();
	}
    return get_dir();
}

/**
 * @brief Updates the direction of the ghost based on probability.
 *        The ghost has a small chance to change direction randomly.
 */
bool Ghost::update_dir(char key) {

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
 * @brief Moves the ghost by updating its direction and stepping.
 */
void Ghost::move() {
    update_dir();
    step();
}

/**
 * @brief Resets the ghost to its initial state.
 */
void Ghost::reset() {
	Entity::reset();
    init_dir();
    active = true;
}

/**
 * @brief Kills the ghost by making it vanish and setting it to inactive.
 */
void Ghost::kill(){
	Entity::reset();
	active = false;

}

/**
 * @note Empty implemantation of handle_falling.
 */
void Ghost::handle_falling() {}

/**
 * @note Empty implemantation of handle_collision.
 */
char Ghost::handle_collision() { return ' '; }

/**
 * @brief Sets the direction of the ghost.
 * @param coord The new direction coordinates.
 */
void Ghost::set_dir(Coordinates coord) {
	Entity::set_dir(coord);
}

/**
 * @brief Checks if the ghost has hit Mario.
 * @return True if the ghost has hit Mario, false otherwise.
 */
bool Ghost::is_hit_mario() const {
    char current = getch_console(get_pos());
    char next = getch_console(get_pos() + get_dir());

    return (current == Board::MARIO || current == Board::SUPER_MARIO ||
        next == Board::MARIO || next == Board::SUPER_MARIO);
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
