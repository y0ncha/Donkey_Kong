#include "Mario.h"

// Constructor for the Mario class, initializing the base Entity class with the given parameters
Mario::Mario(const Board* pBoard) : Entity(pBoard, Board::MARIO, {Board::MARIO_X0, Board::MARIO_Y0}) {}

/**
 * Updates Mario's direction based on the key input.
 */
void Mario::update_dir(char key) {

	// Convert key to direction (ignore non-defined keys)
    switch (std::tolower(key)) {

    case Ctrl::UP:
        dir.y = -1; // move up
        break;

    case Ctrl::DOWN:
        dir.y = 1; // move down
        break;

    case Ctrl::LEFT:
        dir.x = -1; // move left
        break;

    case Ctrl::RIGHT:
        dir.x = 1; // move right
        break;

    case Ctrl::STAY:
        dir = {0, 0}; // Stay in place
        break;
	} 
}

/**
 * Moves Mario based on the current direction and game state.
 */
void Mario::move() {

    switch (status) {
    case Status::JUMPING: // If Mario is JUMPING
        handle_jumping();
        break;

    case Status::CLIMBING: // If Mario is CLIMBING
        handle_climbing();
        break;

    case Status::FALLING: // If Mario is FALLING
        handle_falling();
        break;

    case Status::IDLE: // If Mario is IDLE
        handle_idle();
		break;
	default:
		break;
    }
}

/**
 * Handles Mario's JUMPING logic.
 */
void Mario::handle_jumping() {

    status = Status::JUMPING;
    jump(); // Make Mario jump

    // If Mario is on the ground
    if (on_ground()) {
        status = Status::IDLE;
        dir.y = 0;
        jump_ascend = jump_descend = 0;
		fall_count = 0; // Reset the fall count
    }
}

/**
 * Handles Mario's CLIMBING logic.
 */
void Mario::handle_climbing() {

    if (dir.y == -1) {

        status = Status::CLIMBING;
        climb_up(); // Continue CLIMBING up

        // If Mario reaches the top of the ladder
        if (curr_ch() == Board::AIR) {
            status = Status::IDLE;
            dir.y = 0;
        }
    } 
    else {

		// todo add check for this condition "can_climb" 
        status = Status::CLIMBING;
        climb_down(); // Continue CLIMBING down
       
        // If Mario reaches the floor
        if (board->is_floor(pos + dir)) {
            status = Status::IDLE;
            dir.y = 0;
        }
    }
}

/**
 * Handles Mario's FALLING logic.
 */
void Mario::handle_falling() {

    status = Status::FALLING;

    fall(); // Make Mario fall if not on the ground

    // If Mario is on the ground
    if (on_ground()) {

        if (fall_count >= MAX_FALL_H) { 
			mario_hit = true; // Set Mario as hit
        }
        else {
			fall_count = 0;
            status = Status::IDLE;
			dir = { last_dx, 0 };
        }
    }
}

/**
 * Handles Mario's IDLE logic.
 */
void Mario::handle_idle() {

    if (off_ground()) {
        handle_falling();
    } 

    else switch (dir.y) {

	case -1: // If Mario is moving up
		if (can_climb()) { // If Mario can climb
            handle_climbing();
        } 
		else { // If Mario can't climb
            handle_jumping();
        }
        break;  

	case 1: // If Mario is moving down
		if (can_climb()) { // If Mario can climb
			handle_climbing();
		}
        break;

	default: // If Mario is on the ground
        last_dx = dir.x; // Save the last direction
        step(); // move Mario one step
		break;
    }
}

/**
 * Makes Mario jump.
 */
void Mario::jump() {

	if (jump_ascend < JMP_H && board->path_clear(pos + dir)) { // If Mario is ascending
        jump_ascend++;
        dir.y = -1;
        step();
    } 
	else if (jump_descend < JMP_H && off_ground()) { // If Mario is descending
        jump_descend++;
        dir.y = 1;
        step();
    }
	else { // If Mario finish the jump and starts FALLING
		fall_count = jump_descend; // Start the fall from the height of the jump
        jump_ascend = jump_descend = 0;
		handle_falling(); // An extra step is being done here intentionally, it makes the fall look smoother and dosnt seems to make the barrels lag.
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

/**
 * Checks if Mario can climb.
 */ 
bool Mario::can_climb() {
	return (dir.y == -1 && curr_ch() == Board::LADDER) || (dir.y == 1 && board->get_char(pos.x, pos.y + 2) == Board::LADDER); // todo add is LADDER function
}

/**
 * Checks if Mario hits something and returns the type of object he hits.
 */
char Mario::handle_collision() {

	char obst = getch_console(pos + dir);

    switch (obst) {

	case Board::BARREL: // If Mario hits a barrel
		mario_hit = true; // Set Mario as hit
        break;

	case Board::PAULINE: // If Mario hits Pauline
		rescued_pauline = true; // Set Mario as saved Pauline
        break;

	case Board::ERR: // If Mario's next step is out of bounds
        dir.x = -dir.x; // Reverse direction if path is not clear
		obst = Board::AIR; // Return air to allow Mario to move
		break;
 
    default:
		break;
    }
    return obst; // Return the type of object the mario hits (optional for next exercises)
}

/**
 * Gets the number of lives Mario has left.
 */
int Mario::get_lives() const {
	return lives_left;
}

/*
* Reset Mario to its initial feilds.
 */ 
void Mario::reset() {

    lives_left--;

    pos = { Board::MARIO_X0, Board::MARIO_Y0 };

	mario_hit = false;

    status = Status::IDLE;

    fall_count = 0;
    jump_ascend = 0;
    jump_descend = 0;

    dir = { 0, 0 };
    last_dx = 0;
    draw();
}

/**
 * Checks if Mario is hit.
 */ 
bool Mario::is_hit() const {
	return mario_hit;
}

/**
 * Checks if Mario saved Pauline.
 */
bool Mario::is_rescued_pauline() const {
	return rescued_pauline;
}

