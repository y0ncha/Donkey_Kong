#include "Mario.h"

// Constructor for the Mario class, initializing the base Entity class with the given parameters
Mario::Mario(const Board* org_board, Board* curr_board) : Entity(org_board, curr_board, Board::MARIO) {}

/**
 * Updates Mario's direction based on the key input.
 */
void Mario::update_dir(char key) {
    switch (std::tolower(key)) {
    case UP:
        dir.y = -1; // Move up
        break;
    case DOWN:
        dir.y = 1; // Move down
        break;
    case LEFT:
        dir.x = -1; // Move left
        break;
    case RIGHT:
        dir.x = 1; // Move right
        break;
    case STAY:
        dir = {0, 0}; // Stay in place
        break;
    default:
        break; // Ignore other keys
    }
}

/**
 * Moves Mario based on the current direction and game state.
 */
void Mario::move() {

    if (jumping) { // If Mario is jumping, continue the jump
        jump();
    } 
    else if (climbing) { // If Mario is climbing, continue the climb
        if (dir.y == -1) climb_up();
        else climb_down();
    } 
    else if (!on_ground()) { // If Mario is not on the ground, make him fall
        fall();
    } 
    else if (dir.y == -1) { // If Mario is moving up, check if he can ascend
        if (curr_ch() == Board::LADDER) { // If Mario is on a ladder, make him climb
            climb_up();
        } else { // If Mario is not on a ladder, make him jump
            jump();
        }
    } 
    else if (dir.y == 1 && org_board->get_char(pos.x, pos.y + 2) == Board::LADDER) { // If Mario is moving down and there is a ladder below him, make him climb down
        climb_down();
    } 
    else { // If Mario is not jumping, climbing, or falling, move horizontally
        dir.y = 0;
        dir.x = org_board->path_clear(pos + dir) ? dir.x : -dir.x; // Check if Mario is within the game bounds
        last_dx = dir.x; // Save the last direction
        step(); // Move Mario one step
    }
}

/**
 * Makes Mario jump.
 */
void Mario::jump() {

    jumping = true;

    if (jump_ascend < JMP_H && org_board->path_clear(pos + dir)) {
        jump_ascend++;
        dir.y = -1;
        step();
    } else if (jump_descend < JMP_H && !on_ground()) {
        jump_descend++;
        dir.y = 1;
        step();
    } else {
        jumping = false;
        jump_ascend = jump_descend = 0;
    }

    if (on_ground()) {
        jumping = false;
        dir.y = 0;
        jump_ascend = jump_descend = 0;
    }
}

/**
 * Makes Mario fall.
 */
void Mario::fall() {

    falling = true;
    fall_count++;

    dir.x = 0;
    dir.y = 1;

    step();

    if (on_ground()) {

        died = (fall_count >= MAX_FALL_H);

        falling = false;
        fall_count = 0;
        dir.x = last_dx;
        dir.y = 0;
    }
}

/**
 * Makes Mario climb up.
 */
void Mario::climb_up() {
    climbing = true;
    dir.x = 0;

    step();

    if (curr_ch() == Board::AIR) {
        climbing = false;
        dir.y = 0;
    }
}

/**
 * Makes Mario climb down.
 */
void Mario::climb_down() {
    climbing = true;
    dir.x = 0;

    step();

    if (org_board->is_floor(dest_ch())) {
        climbing = false;
        dir.y = 0;
    }
}

/**
 * Gets the character at the destination position.
 */
char Mario::dest_ch() const {
    return org_board->get_char(pos + dir);
}

/**
 * Gets the character at the current position.
 */
char Mario::curr_ch() const {
    return org_board->get_char(pos);
}

/**
 * Checks if Mario is on the ground.
 */
bool Mario::on_ground() const {
    return (org_board->is_floor(org_board->get_char(pos.x, pos.y + 1)));
}

/**
 * Checks if Mario is dead.
 */
bool Mario::is_dead() const {
	return died;
}
