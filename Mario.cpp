#include "Mario.h"

/**
 * @brief Constructor for the Mario class, initializing the base Entity class with the given parameters.
 * @param pBoard Pointer to the game board.
 */
Mario::Mario(const Board* pBoard) 
    : Entity(pBoard, Board::MARIO, { -1, -1}) {}

/**
* @brief Sets mario's board pointer.
* @param pBoard The board pointer to set.
*/
void Mario::set_board(const Board* pBoard) {
	board = pBoard;
}

/**
 * @brief Updates Mario's direction based on the key input.
 * @param key The key input to determine the direction.
 */
void Mario::update_dir(char key) {

    // Convert key to direction (ignore non-defined keys)
    switch (std::tolower(key)) {
    case Ctrl::UP:
        set_dy(-1); // move up
        break;
    case Ctrl::DOWN:
        set_dy(1); // move down
        break;
    case Ctrl::LEFT:
        set_dx(-1); // move left
        break;
    case Ctrl::RIGHT:
        set_dx(1); // move right
        break;
    case Ctrl::STAY:
        set_dir(0,0); // Stay in place
        break;
    }
}

/**
 * @brief Moves Mario based on the current direction and game state.
 */
void Mario::move() {

    switch (state) {
    case State::JUMPING:
        handle_jumping();
        break;
    case State::CLIMBING:
        handle_climbing();
        break;
    case State::FALLING:
        handle_falling();
        break;
    case State::IDLE:
        handle_idle();
        break;
    default:
        break;
    }
}

/**
 * @brief Handles Mario's JUMPING logic.
 */
void Mario::handle_jumping() {
    state = State::JUMPING;
    jump(); // Make Mario jump

    // If Mario is on the ground
    if (on_ground()) {
        state = State::IDLE;
        dir.y = 0;
        jump_ascend = jump_descend = 0;
        fall_count = 0; // Reset the fall count
    }
}

/**
 * @brief Handles Mario's CLIMBING logic.
 */
void Mario::handle_climbing() {
    if (dir.y == -1) {
        state = State::CLIMBING;
        climb_up(); // Continue CLIMBING up

        // If Mario reaches the top of the ladder
        if (behind_ch() == Board::AIR) {
            state = State::IDLE;
            dir.y = 0;
        }
    }
    else {
        state = State::CLIMBING;
        climb_down(); // Continue CLIMBING down

        // If Mario reaches the floor
        if (board->is_floor(point.pos + dir)) {
            state = State::IDLE;
            dir.y = 0;
        }
    }
}

/**
 * @brief Handles Mario's FALLING logic.
 */
void Mario::handle_falling() {
    state = State::FALLING;
    fall(); // Make Mario fall if not on the ground

    if (on_ground()) {
        if (fall_count >= MAX_FALL_H) {
            mario_hit = true; // Set Mario as hit
        }
        else {
            fall_count = 0;
            state = State::IDLE;
            dir = { last_dx, 0 };
        }
    }
}

/**
 * @brief Handles Mario's IDLE logic.
 */
void Mario::handle_idle() {
    if (off_ground()) {
        handle_falling();
    }
    else {
        switch (dir.y) {
        case -1: // If Mario is moving up
            if (can_climb()) { // If Mario can climb
                handle_climbing();
            }
			else if (can_jump()) { // If Mario can't climb check if he can jump
                handle_jumping();
            }
            else {
				dir.y = 0; // If Mario can't climb or jump, reset the vertcal direction
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
}

/**
 * @brief Makes Mario jump.
 */
void Mario::jump() {
    if (jump_ascend < JMP_H && board->path_clear(point.pos + dir)) { // If Mario is ascending
        jump_ascend++;
        dir.y = -1;
        step();
    }
    else if (jump_descend < JMP_H && off_ground()) { // If Mario is descending
        jump_descend++;
        dir.y = 1;
        step();
    }
    else { // If Mario finishes the jump and starts FALLING
        fall_count = jump_descend; // Start the fall from the height of the jump
        jump_ascend = jump_descend = 0;
        handle_falling(); // An extra step is being done here intentionally, it makes the fall look smoother and doesn't seem to make the barrels lag.
    }
}

/**
 * @brief Makes Mario fall.
 */
void Mario::fall() {
    fall_count++;
    dir = { 0, 1 };
    step();
}

/**
 * @brief Makes Mario climb up.
 */
void Mario::climb_up() {
    dir.x = 0;
    step();
}

/**
 * @brief Makes Mario climb down.
 */
void Mario::climb_down() {
    dir.x = 0;
    step();
}

/**
 * @brief Checks if Mario can climb.
 * @return True if Mario can climb, false otherwise.
 */
bool Mario::can_climb() const {
    return (dir.y == -1 && behind_ch() == Board::LADDER) || (dir.y == 1 && board->get_char(point.pos.x, point.pos.y + 2) == Board::LADDER);
}

/**
 * @brief Checks if Mario can jump.
 * @return True if Mario can jump, false otherwise.
 */
bool Mario::can_jump() const {
    return (!board->is_floor(above_ch()) && on_ground());
}

/**
 * @brief Checks if Mario hits something and returns the type of object he hits.
 * @return The type of object Mario hits.
 */
char Mario::handle_collision() {
    char obst = getch_console(point.pos + dir);

    switch (obst) {
    case Board::BARREL: // If Mario hits a barrel
        mario_hit = true; // Set Mario as hit
        break;
	case Board::GHOST: // If Mario hits a ghost
		mario_hit = true; // Set Mario as hit
		break;
    case Board::HAMMER: // If Mario hits a hammer
        has_hammer = true;// Set Mario as having a hammer
        point.icon = Board::SUPER_MARIO; // Change Mario's icon to Mario with a hammer
        break;
    case Board::PAULINE: // If Mario hits Pauline
        rescued_pauline = true; // Set Mario as saved Pauline
        break;
	case Board::WALL: // If Mario hits a wall
		dir.x = -dir.x; // Reverse direction if path is not clear
		obst = Board::AIR; // Return air to allow Mario to move
		break;
    case Board::ERR: // If Mario's next step is out of bounds
        dir.x = -dir.x; // Reverse direction if path is not clear
        obst = Board::AIR; // Return air to allow Mario to move
        break;
    default: // If a barrel is about to collide with a floor from the side, stop it
        if (board->is_floor(obst)) dir.x = -dir.x;
        break;
    }

    // If Mario falls out of the screen
    if (beneath_ch() == Board::ERR) {
		set_dir(0, 0); // Stop Mario
        mario_hit = true; // Set Mario as hit
    }

    return obst; // Return the type of object Mario hits (optional for next exercises)
}

/**
 * @brief Gets the number of lives Mario has left.
 * @return The number of lives left.
 */
int Mario::get_lives() const {
    return lives_left;
}

/**
* @brief Decreases the number of lives Mario has left.
*/
void Mario::lose_lives() {
	lives_left--;
}


/**
 * @brief Resets Mario to its initial fields.
 */
void Mario::reset() {

    mario_hit = false;
    rescued_pauline = false;
    has_hammer = false;

    point.icon=Board::MARIO;
    point.pos = board->get_pos(Board::MARIO);
    state = State::IDLE;

    fall_count = 0;
    jump_ascend = 0;
    jump_descend = 0;
    dir = { 0, 0 };
    last_dx = 0;
}

/**
 * @brief Checks if Mario is hit.
 * @return True if Mario is hit, false otherwise.
 */
bool Mario::is_hit() const {
    return mario_hit;
}

/**
 * @brief Checks if Mario saved Pauline.
 * @return True if Mario saved Pauline, false otherwise.
 */
bool Mario::is_rescued_pauline() const {
    return rescued_pauline;
}

/**
 * @brief Checks if Mario picked up the hammer.
 * @return true if he picked up the hammer, false otherwise
 */
bool Mario::get_hammer() const
{
    return has_hammer;
}