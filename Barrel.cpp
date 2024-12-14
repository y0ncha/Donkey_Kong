#include "Barrel.h"

/**
* Constructor for the Barrel class.
* @warning This constructor does not initialize the barrel's position and pointer.
*/
Barrel::Barrel(const Board* pBoard) : Entity(pBoard, Board::BARREL, init_pos()) {}

/**
 * Method to handle the movement logic of the barrel.
 */
void Barrel::move() { // @ decide what happens if barrel is off bound
    // If the barrel has been FALLING for 8 or more steps, it should explode

    char beneath = beneath_ch();

	if (status == Status::FALLING) { // If the barrel is falling
        handle_falling();
    }
	else { // If the barrel is not falling
		update_dir(beneath);
		step();
    }
}

/**
 * Method to handle the direction change when the barrel is on different types of floors.
 */
void Barrel::update_dir(char beneath) {

    switch (beneath) {
    case Board::FLOOR_L: // If the barrel is on a left-sloping floor
        last_dx = dir.x = -1; // move left
        break;

    case Board::FLOOR_R: // If the barrel is on a right-sloping floor
        last_dx = dir.x = 1; // move right
        break;

	case Board::AIR: // If the barrel is in the air
        status = Status::FALLING; // Set the status to FALLING
		dir = { 0, 1 }; // move down
        fall_count++;

    default: // If the barrel is on a flat floor keep moving in the same direction
        break;
    }
}

/*
* Method to handle the FALLING of the barrel.
*/
void Barrel::handle_falling() { // todo make virtual

	fall_count++;

	// Set the direction to fall and step
	dir = { 0, 1 };
    step();
	
	// If the barrel hits the groud (and did not fell right on Mario)
	if (on_ground() && !hit_mario) {
		if (fall_count >= MAX_FALL_H) { // If the barrel has been falling for 8 or more chars
			explode();
        }
		else { // If the barrel has not been falling for 8 or more chars
            dir = { last_dx, 0 };
			status = Status::IDLE;
            fall_count = 0;
        }
	}
}

void Barrel::explode() {
	reset(); // Reset the barrel

    for (int i = 0; i <= Barrel::EXPLOSION_RADIUS; i++) {
        print_explosion_phase(i);
		clear_explosion_phase(i -1);
		Sleep(EXPLOSION_DELAY);
    }
	clear_explosion_phase(Barrel::EXPLOSION_RADIUS);
}

/*
* Method to print the explosion phase within a given radius.
*/
void Barrel::print_explosion_phase(int radius) {

	if (radius == 0) {
        gotoxy(point.pos); // Move the cursor to the position of the barrel
		if (getch_console(point.pos) == Board::MARIO) {
			hit_mario = true;
		}
        std::cout << "*"; // Print the explosion message
	}
    else {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (getch_console({ point.pos.x + i, point.pos.y + j }) == Board::MARIO) {
                    hit_mario = true;
                }
                gotoxy(point.pos.x + i, point.pos.y + j);
                std::cout << "*"; // Print the explosion
            }
        }
    }

}

/*
*  Method to clear the explosion phase within a given radius.
*/
void Barrel::clear_explosion_phase(int radius) {

	if (radius == -1) {
		gotoxy(point.pos); // Move the cursor to the position of the barrel
		std::cout << board->get_char(point.pos); // Clear the explosion
	}
    else {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                gotoxy(point.pos.x + i, point.pos.y + j); // Move the cursor to the position of the barrel
                std::cout << board->get_char(point.pos.x + i, point.pos.y + j); // Clear the explosion
            }
        }
    }
}

/**
 * Checks if the barrel is active.
 */
bool Barrel::is_active() const {
    return active;
}

/**
 * Returns and sets the initial position of the barrel.
 */
Coordinates Barrel::init_pos() { 
    return (point.pos = {(rand() % 2 == 0) ? Board::DKONG_X0 + 1 : Board::DKONG_X0 - 1, Board::DKONG_Y0});
}

/**
 * Sets the original and current board for the barrel.
 */
void Barrel::set_board(const Board* pBoard) {
	board = pBoard;
}

/**
 * Spawns the barrel at the initial position and activates it.
 */
void Barrel::spawn() {
	init_pos();
    active = true;
    draw();
}

/**
 * Handles collision logic for the barrel.
 */
char Barrel::handle_collision() {

    char obst = getch_console(point.pos + dir);

    switch (obst) {
    case Board::MARIO: // If the barrel hits Mario
        hit_mario = true;
        break;

    case Board::ERR: // If the barrel is out of bounds
        reset();
        break;
    }
    return obst;
}
/*
* Resets the barrel status and direction.
*/
void Barrel::reset() {
    erase();
    dir = { 0,0 };
	status = Status::IDLE;
    fall_count = 0;
	hit_mario = false;
    active = false;
}

/*
* Checks if the barrel hitted Mario.
*/
bool Barrel::hitted_mario() const {
        return hit_mario;
}
