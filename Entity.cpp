#include "Entity.h"

/**
 * @brief Constructor for the Entity class, initializing the base Entity class with the given parameters.
 * Checks if the layout, board, and position are valid.
 * @param pBoard Pointer to the game board.
 * @param ch Character representing the entity.
 * @param init_pos Initial position of the entity.
 * @param init_dir Initial direction of the entity.
 */
Entity::Entity(const Board* pBoard, char ch, Coordinates init_pos, Coordinates init_dir)
    : board(pBoard), point(ch, init_pos), dir(init_dir) {
    if (board == nullptr) { // Validate
        clear_screen();
        handle_err("SYSTEM ERROR: board is not initialized!", __FILE__, __LINE__);
    }
}

/**
 * @brief Draws the entity at its current position.
 */
void Entity::set() const {
    point.draw(); // Draw the entity at the current position
}

/**
 * @brief Erases the entity from its current position.
 */
void Entity::vanish() const {
    point.erase(board->get_char(point.pos)); // Erase the entity from the current position
}

/**
 * @brief Sets the position of the entity using x and y coordinates.
 * @param _x The x-coordinate of the new position.
 * @param _y The y-coordinate of the new position.
 */
void Entity::set_pos(int _x, int _y) {
    point.pos = { _x, _y };
}

/**
 * @brief Sets the position of the entity using a Coordinates object.
 * @param coord The new position.
 */
void Entity::set_pos(Coordinates coord) {
    point.pos = coord;
}

/**
 * @brief Sets the direction of the entity using dx and dy values.
 * @param dx The x-direction value.
 * @param dy The y-direction value.
 */
void Entity::set_dir(int dx, int dy) {
    dir = { dx, dy };
}

/**
 * @brief Sets the direction of the entity using a Coordinates object.
 * @param coord The new direction.
 */
void Entity::set_dir(Coordinates coord) {
    dir = coord;
}

/**
 * @brief Moves the entity by one step.
 * Erases the entity from the current position, updates the position, and draws the entity at the new position.
 */
void Entity::step() {
    point.erase(behind_ch()); // Erase the entity from the current position

    if (handle_collision()) {
        ; // Handle collisions with other entities or obstacles
        point.pos += dir; // Move the entity by adding the direction to the position
        point.draw(); // Draw the entity at the new position
    }
}

/**
 * @brief Gets the character at the destination position.
 * @return The character at the destination position.
 */
char Entity::next_ch() const {
    return board->get_char(point.pos + dir);
}

/**
 * @brief Checks the character beneath the entity.
 * @return The character beneath the entity.
 */
char Entity::beneath_ch() const {
    return board->get_char(point.pos.x, point.pos.y + 1);
}

/**
 * @brief Checks the character above the entity.
 * @return The character above the entity.
 */
char Entity::above_ch() const {
    return board->get_char(point.pos.x, point.pos.y - 1);
}

/**
 * @brief Gets the character at the current position.
 * @return The character at the current position.
 */
char Entity::behind_ch() const {
    return board->get_char(point.pos);
}

/**
 * @brief Checks if the entity is off the ground.
 * @return True if the entity is off the ground, false otherwise.
 */
bool Entity::off_ground() const {
    char bellow = beneath_ch();
    return (bellow != Board::FLOOR && bellow != Board::FLOOR_L && bellow != Board::FLOOR_R);
}

/**
 * @brief Checks if the entity is on the ground.
 * @return True if the entity is on the ground, false otherwise.
 */
bool Entity::on_ground() const {
    return !off_ground();
}
