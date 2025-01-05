#include "Ghost.h"

Ghost::Ghost(const Board* pBoard) : Entity(pBoard, Board::GHOST, { -1, -1 }) {
	dir = init_dir();
	last_dx = dir.x;
	active = true;
	
}

void Ghost::set_board(const Board* pBoard) {
	board = pBoard;
}

bool Ghost::valid_move()
{
	if ((board->is_floor(point.pos + dir + Coordinates{0,1})) && (board->pos_inbound(point.pos + dir)))
		return true;
	else {
		return false;
	}
}
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

void Ghost::update_dirc()
{
	int probability= rand() % 100;
	if (probability < 5)
	{
		dir.x = -dir.x;
		if (!valid_move())
		{
			dir.x = -dir.x;
		}
	}
	else
	{
		if (!valid_move())
		{
			dir.x = -dir.x;
		}
	}
	last_dx = dir.x;
}

void Ghost::move() {
	update_dirc();
	step();	
}

// Implementation of reset
void Ghost::reset() {
	vanish();
	dir = init_dir();
	active = true;
}

void Ghost::handle_falling() {
	// Implementation of handle_falling
}

char Ghost::handle_collision() {
	// Implementation of handle_collision
	return ' ';
}

void Ghost::update_dir(char key) 
{

}

void Ghost::set_dir(Coordinates coord)
{
	dir = coord;
}

void Ghost::invert_dir(){
	dir.x = -dir.x;
	last_dx = dir.x;
}

bool Ghost::is_hit_mario() const
{
	return (getch_console(point.pos) == Board::MARIO || getch_console(point.pos + dir) == Board::MARIO);
}

bool Ghost::is_active() const {
	if (active)
		return true;
	else
		return false;
}

void Ghost::activate() {
	active = true;
}