#include "Entity.h"

/**
 * Constructor for the Entity class, initializing the base Entity class with the given parameters.
 * Checks if the layout, board, and position are valid.
 */
Entity::Entity(char ch, const Board* pBoard, Coordinates init_pos, Coordinates init_dir)
    : icon(ch), board(pBoard), pos(init_pos), dir(init_dir) {
    if (!pos_inbound(init_pos)) { // Validate
        clear_screen();
        handle_err("Error: position is out of bound!", __FILE__, __LINE__);
    }
}

/**
 * Draws the entity at its current position.
 */
void Entity::draw() const {
    gotoxy(pos); // Move the cursor to the entity's position
    std::cout << icon; // Print the entity's character at the position
}

/**
 * Erases the entity from its current position.
 */
void Entity::erase() const {
    gotoxy(pos); // Move the cursor to the entity's position
    std::cout << board->get_char(pos); // Restore the character from the board
}

/**
 * Sets the position of the entity using x and y coordinates.
 */
void Entity::set_pos(int _x, int _y) {
	pos = { _x, _y };
}
void Entity::set_pos(Coordinates coord) {
    pos = coord;
}

/**
 * Sets the direction of the entity using dx and dy values.
 */
void Entity::set_dir(int dx, int dy) {
	dir = { dx, dy };
}
void Entity::set_dir(Coordinates coord) {
    dir = coord;
}

/**
 * Moves the entity by one step.
 * Erases the entity from the current position, updates the position, and draws the entity at the new position.
 */
void Entity::step() {
    erase(); // Erase the entity from the current position
    handle_collision(); // Handle collisions with other entities or obstacles

    pos += dir; // Move the entity by adding the direction to the position
    draw(); // Draw the entity at the new position
}

/**
 * Gets the character at the destination position.
 */
char Entity::next_ch() const {
    return board->get_char(pos + dir);
}

/**
 * Checks the char beneath mario.
 */
char Entity::beneath_ch() const {
    return board->get_char(pos.x, pos.y + 1);
}

/**
 * Checks the char above mario.
 */
char Entity::above_ch() const {
	return board->get_char(pos.x, pos.y - 1);
}

/**
 * Gets the character at the current position.
 */
char Entity::curr_ch() const {
    return board->get_char(pos);
}