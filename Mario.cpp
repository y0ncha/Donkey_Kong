#include "Mario.h"

// Constructor for the Mario class, initializing the base Entity class with the given parameters
Mario::Mario(const Board* pBoard) : Entity(Board::MARIO, pBoard) {}

/**
 * Updates Mario's direction based on the key input.
 */
void Mario::update_dir(char key) {
    switch (std::tolower(key)) {
    case Ctrl::UP:
        dir.y = -1; // Move up
        break;
    case Ctrl::DOWN:
        dir.y = 1; // Move down
        break;
    case Ctrl::LEFT:
        dir.x = -1; // Move left
        break;
    case Ctrl::RIGHT:
        dir.x = 1; // Move right
        break;
    case Ctrl::STAY:
        dir = {0, 0}; // Stay in place
        break;
    default:
        break; // Ignore other keys
    }
}

/**
 * Moves Mario based on the current direction and game state.
 */
void Mario::Move() {
    switch (status) {
    case Status::Jumping:
        handle_jumping();
        break;
    case Status::Climbing:
        handle_climbing();
        break;
    case Status::Falling:
        handle_falling();
        break;
    case Status::Idle:
    default:
        handle_idle();
        break;
    }
}

/**
 * Handles Mario's jumping logic.
 */
void Mario::handle_jumping() {

    status = Status::Jumping;
    jump(); // Make Mario jump

    // If Mario is on the ground
    if (on_ground()) {
        status = Status::Idle;
        dir.y = 0;
        jump_ascend = jump_descend = 0;
    }
}

/**
 * Handles Mario's climbing logic.
 */
void Mario::handle_climbing() {

    if (dir.y == -1) {

        status = Status::Climbing;
        climb_up(); // Continue climbing up

        // If Mario reaches the top of the ladder
        if (curr_ch() == Board::AIR) {
            status = Status::Idle;
            dir.y = 0;
        }
    } 
    else {

		// todo add check for this condition "can_climb" 
        status = Status::Climbing;
        climb_down(); // Continue climbing down
       
        // If Mario reaches the floor
        if (board->is_floor(pos + dir)) {
            status = Status::Idle;
            dir.y = 0;
        }
    }
}

/**
 * Handles Mario's falling logic.
 */
void Mario::handle_falling() {

    status = Status::Falling;

    fall(); // Make Mario fall if not on the ground

    // If Mario is on the ground
    if (on_ground()) {
        died = (fall_count >= MAX_FALL_H);
        status = Status::Idle;
        fall_count = 0;
        dir.x = last_dx;
        dir.y = 0;
    }
}

/**
 * Handles Mario's idle logic.
 */
void Mario::handle_idle() {

    if (off_ground()) {
        handle_falling();
    } 

    else switch (dir.y) {

    case -1:
        if (can_climb()) {
            handle_climbing();
        } 
        else {
            handle_jumping();
        }
        break;  

	case 1:
        if (can_climb()) {
			handle_climbing();
		}
        break;

    default:
        last_dx = dir.x; // Save the last direction
        step(); // Move Mario one step
		break;
    }
}

/**
 * Makes Mario jump.
 */
void Mario::jump() {

    if (jump_ascend < JMP_H && board->path_clear(pos + dir)) {
        jump_ascend++;
        dir.y = -1;
        step();
    } 
    else if (jump_descend < JMP_H && off_ground()) {
        jump_descend++;
        dir.y = 1;
        step();
    }
    else {
        status = Status::Falling;
        dir.y = 0;
        jump_ascend = jump_descend = 0;
        fall_count++;
    }
}

/**
 * Makes Mario fall.
 */
void Mario::fall() {

    fall_count++;

	dir = { 0, 1 };
    step();
}

/**
 * Makes Mario climb up.
 */
void Mario::climb_up() {

    dir.x = 0;
    step();
}

/**
 * Makes Mario climb down.
 */
void Mario::climb_down() {

    dir.x = 0;
    step();
}

bool Mario::can_climb() {
	return (dir.y == -1 && curr_ch() == Board::LADDER) || (dir.y == 1 && board->get_char(pos.x, pos.y + 2) == Board::LADDER); // todo add is LADDER function
}

/**
 * Checks if Mario is on the ground.
 */
bool Mario::off_ground() const {
	char bellow = beneath_ch();
	return (bellow != Board::FLOOR && bellow != Board::FLOOR_L && bellow != Board::FLOOR_R);
}

/**
 * Checks if Mario is on the ground.
 */
bool Mario::on_ground() const {
	return !off_ground();
}

/**
 * Checks if Mario is dead.
 */
bool Mario::is_dead() const {
    return died;
}

/**
 * Decreases Mario's lives by one.
 */
void Mario::kill() {
    lives_left--;
    died = true;
}

/**
 * Checks if Mario hits something and returns the type of object he hits.
 */
void Mario::handle_collision() {

	char obst = getch_console(pos + dir);

    switch (obst) {

    case Board::BARREL:
        kill();
        break;

    case Board::DONKEY_KONG:
        // todo add DK logic
        break;

    case Board::PAULINE:
        // todo add Pauline logic
        break;

    case Board::ERR:

        dir.x = -dir.x; // Reverse direction if path is not clear
        break;

    default:
        break;
    }
}

int Mario::get_lives() const {
	return lives_left;
}
