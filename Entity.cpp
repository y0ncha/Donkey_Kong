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
    : board(pBoard),
    point(ch, init_pos),
    dir(init_dir) {
}

/**
 * @brief Draws the entity at its current position.
 * Get the position of the entity if it is not initialized.
 * If initial potion is off ground move the entity down until it is on the ground.
 */
void Entity::set(size_t i) const {

	// initialized the position of the entity if needed
	if (get_pos() == Coordinates {-1, -1}) {

        Coordinates pos = board->get_pos((point.icon), i);
		set_pos(pos); // Set the position of the entity

		while (off_ground()) { // Check if the entity is off the ground
			pos.y++; // Move the entity down
			set_pos(pos); // Set the new position
		}
	}
	point.draw(); // Draw the entity at the current position
}

/**
* @brief Getter for the last horizontal direction.
* @return The last horizontal direction.
*/
int Entity::get_lastdx() const {
	return last_dx;
}

/**
 * @brief Inverts the direction of the entity.
 */
void Entity::invert_dir() {
    last_dx = dir.x;
	dir.x = -dir.x;
}

/**
 * @brief Resets the entity to its initial state.
 */
void Entity::reset() {
	vanish();
	set_pos({ -1, -1 });
	dir = { 0, 0 };
	last_dx = 0;
}

/**
 * @brief Setter for the board pointer.
 * @param pBoard The board pointer to set.
 */
bool Entity::set_board(const Board* pBoard) {

	if (pBoard == nullptr) return false; // Check if the board pointer is valid
	
    board = pBoard;
	return true;
}

/**
 * @brief Setter for the last_dx.
 */
void Entity::set_last_dx(int dx) {
	last_dx = dx;
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
 * @return True if the position is valid, false otherwise.
 */
Coordinates Entity::set_pos(int _x, int _y) const {
	return set_pos({ _x, _y });
}

/**
 * @brief Sets the position of the entity using a Coordinates object.
 * @param coord The new position.
 * @return True if the position is valid, false otherwise.
 */
Coordinates Entity::set_pos(Coordinates coord) const {
    if (board->pos_inbound(coord) || coord == Coordinates{-1,-1}) {
        return point.pos = coord;
    }
	else {
        return { -1, -1 };
	}
}

/**
 * @brief Sets the direction of the entity using dx and dy values.
 * @param dx The x-direction value.
 * @param dy The y-direction value.
 */
bool Entity::set_dir(int dx, int dy) {

    if (-1 <= dx && dx <= 1 && -1 <= dy && dy <= 1) { // Check if the direction is valid
		if (dir.x != 0) last_dx = dir.x;
        dir = { dx, dy };
        return true;
    }
	else return false; // Return false if the direction is invalid
}

/**
 * @brief Sets the direction of the entity using a Coordinates object.
 * @param coord The new direction.
 */
bool Entity::set_dir(Coordinates coord) {
	return set_dir(coord.x, coord.y);
}

/**
 * @brief Moves the entity by one step.
 * Erases the entity from the current position, updates the position, and draws the entity at the new position.
 */
void Entity::step() {

	// Check if the current position is inbound
    if (!board->pos_inbound(point.pos)) return;

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
* @brief Gets the character to the left of the entity.
* @return The character to the left of the entity.
*/
char Entity::left_ch() const {
	return board->get_char(point.pos.x - 1, point.pos.y);
}

/**
* @brief Gets the character to the right of the entity.
* @return The character to the right of the entity.
*/
char Entity::right_ch() const {
	return board->get_char(point.pos.x + 1, point.pos.y);
}

/**
 * @brief Checks if the entity is off the ground.
 * @return True if the entity is off the ground, false otherwise.
 */
bool Entity::off_ground() const {
    char bellow = beneath_ch();
	if (bellow == Board::ERR) { // Check if the character beneath the entity is out of bound
        return false;
    }
	else { // Check if the character beneath the entity is not a floor element
        return !board->is_floor(bellow);
    }
}

/**
 * @brief Checks if the entity is on the ground.
 * @return True if the entity is on the ground, false otherwise.
 */
bool Entity::on_ground() const {
    return !off_ground();
}

/**
 * @brief Sets the dx value of the entity.
 * @param dx The new dx value.
 */
bool Entity::set_dy(int dy) {
    return set_dir(dir.x, dy);
}

/**
 * @brief Sets the dy value of the entity.
 * @param dy The new dy value.
 */
bool Entity::set_dx(int dx) {
	if (dx != 0) last_dx = dir.x;
	return set_dir(dx, dir.y);
}

/*
* @brief Gets the destination position of the ghost.
* @return The destination position of the ghost.
*/
Coordinates Entity::get_dest() const {
    return point.pos + dir;
}

/**
 * @brief Sets the icon of the entity.
 * @param ch The new icon.
 * @return True if the icon is valid, false otherwise.
 */
bool Entity::set_icon(Board::Icon icon) {
	if (board->is_valid_ch(icon)) {
		point.icon = icon;
		return true;
	}
    return false;
}