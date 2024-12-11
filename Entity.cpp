#include "Entity.h"

/**
 * Constructor for the Entity class, initializing the base Entity class with the given parameters.
 * Checks if the layout, board, and position are valid.
 */
Entity::Entity(const Board* layout, Board* board, char ch, Coordinates init_pos, Coordinates init_dir) : icon(ch), org_board(layout), curr_board(board), pos(init_pos), dir(init_dir) {
    if (layout == nullptr || board == nullptr || !pos_inbound(init_pos)) { // Check if the layout, board, and position are valid
        exit(1);
    }
}
Entity::Entity(char ch, Coordinates init_pos , Coordinates init_dir) : icon(ch), pos(init_pos), dir(init_dir) {
    if (!pos_inbound(init_pos)) { // Check if the position is within the game bounds
        exit(1);
    }
}

/**
 * Draws the entity at its current position.
 */
void Entity::draw() const {
    gotoxy(pos); // Move the cursor to the entity's position
    curr_board->set_char(pos, icon); // Set the character on the board
    std::cout << icon; // Print the entity's character at the position
}

/**
 * Erases the entity from its current position.
 */
void Entity::erase() const {
    gotoxy(pos); // Move the cursor to the entity's position
	curr_board->set_char(pos, org_board->get_char(pos));
    std::cout << org_board->get_char(pos); // Restore the character from the board
}

/**
 * Sets the position of the entity using x and y coordinates.
 */
void Entity::set_pos(int _x, int _y) {
    pos.x = _x;
    pos.y = _y;
}

/**
 * Sets the direction of the entity using dx and dy values.
 */
void Entity::set_dir(int dx, int dy) {
    dir.x = dx;
    dir.y = dy;
}

/**
 * Sets the position of the entity using a Coordinates object.
 */
void Entity::set_pos(Coordinates coord) {
    pos = coord;
}

/**
 * Sets the direction of the entity using a Coordinates object.
 */
void Entity::set_dir(Coordinates coord) {
    dir = coord;
}

/**
 * Moves the entity by one step.
 * Erases the entity from the current position, updates the position, and draws the entity at the new position.
 */
bool Entity::step(char obst) {

    if (curr_board->get_char(pos + dir) == obst) {
		return false;
    }
    else {
        erase(); // Erase the entity from the current position
        pos += dir; // Move the entity by adding the direction to the position
        draw(); // Draw the entity at the new position
    }
	return true;
}

/**
 * Gets the character at the destination position.
 */
char Entity::org_dest() const {
    return org_board->get_char(pos + dir);
}

/**
 * Gets the character at the destination position.
 */
char Entity::curr_dest() const {
    return curr_board->get_char(pos + dir);
}
