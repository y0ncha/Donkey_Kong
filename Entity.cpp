#include "Entity.h"

/**
 * Constructor for the Entity class, initializing the base Entity class with the given parameters.
 * Checks if the layout, board, and position are valid.
 */
Entity::Entity(const Board* pBoard, char ch, Coordinates init_pos, Coordinates init_dir)
    : board(pBoard), point(ch, init_pos), dir(init_dir) {
    
	if (board == nullptr) { // Validate
		clear_screen();
		handle_err("SYSTEM ERROR: board is not initialized!", __FILE__, __LINE__);
	}
}

/**
 * Draws the entity at its current position.
 */
void Entity::draw() const {
	point.draw(); // Draw the entity at the current position    
}

/**
 * Erases the entity from its current position.
 */
void Entity::erase() const {
	point.erase(board->get_char(point.pos)); // Erase the entity from the current position
}

/**
 * Sets the position of the entity using x and y coordinates.
 */
void Entity::set_pos(int _x, int _y) {
	point.pos = { _x, _y };
}
void Entity::set_pos(Coordinates coord) {
    point.pos = coord;
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

    if (handle_collision()) {
        ; // Handle collisions with other entities or obstacles
        point.pos += dir; // move the entity by adding the direction to the position
        draw(); // Draw the entity at the new position
    }
}

/**
 * Gets the character at the destination position.
 */
char Entity::next_ch() const {
    return board->get_char(point.pos + dir);
}

/**
 * Checks the char beneath mario.
 */
char Entity::beneath_ch() const {
    return board->get_char(point.pos.x, point.pos.y + 1);
}

/**
 * Checks the char above mario.
 */
char Entity::above_ch() const {
	return board->get_char(point.pos.x, point.pos.y - 1);
}

/**
 * Gets the character at the current position.
 */
char Entity::behind_ch() const {
    return board->get_char(point.pos);
}

/**
 * Checks if Entity is on the ground.
 */
bool Entity::off_ground() const {
    char bellow = beneath_ch();
    return (bellow != Board::FLOOR && bellow != Board::FLOOR_L && bellow != Board::FLOOR_R);
}

/**
 * Checks if Entity is on the ground.
 */
bool Entity::on_ground() const {
    return !off_ground();
}
