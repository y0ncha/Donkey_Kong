#include "Entity.h"

Entity::Entity(const Board* layout, Board* board, Coordinates init_pos, char ch) : org_board(layout), curr_board(board), pos(init_pos), icon(ch) {
	if (layout == nullptr || board == nullptr || !pos_inbound(init_pos)) { // Check if the layout, board, and position are valid
		exit(1);
	}
}
Entity::Entity(Coordinates init_pos, char ch) : pos(init_pos), icon(ch) {
	if (!pos_inbound(init_pos)) { // Check if the position is within the game bounds
		exit(1);
	}
}
 
void Entity::draw() const {
    gotoxy(pos); // Move the cursor to the entity's position
	curr_board->set_char(pos, icon); // Set the character on the board
    std::cout << icon; // Print the entity's character at the position
}

void Entity::erase() const {
    gotoxy(pos); // Move the cursor to the entity's position
    std::cout << org_board->get_char(pos); // Restore the character from the board
}

void Entity::set_pos(int _x, int _y) {
	pos.x = _x;
	pos.y = _y;
}

void Entity::set_dir(int dx, int dy) {
	dir.x = dx;
	dir.y = dy;
}

void Entity::set_pos(Coordinates coord) {
	dir = coord;
}

void Entity::set_dir(Coordinates coord) {
	dir = coord;
}

void Entity::step() {

    erase(); // Erase the entity from the current position

    pos += dir; // Move the entity by adding the direction to the position

    draw(); // Draw the entity at the new position
}
