#include "Entity.h"

Entity::Entity(const Board* org_board, Board* curr_board, Coordinates _pos, char ch) : org_board(org_board), curr_board(curr_board), pos(_pos), icon(ch) {}
 

void Entity::draw() const {
    gotoxy(pos); // Move the cursor to the entity's position
	curr_board->set_char(pos, icon); // Set the character on the board
    std::cout << icon; // Print the entity's character at the position
}

void Entity::erase() const {
    gotoxy(pos); // Move the cursor to the entity's position
	curr_board->set_char(pos, org_board->get_char(pos));
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
