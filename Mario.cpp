#include "Mario.h"

/**
 * @brief Constructor for the Mario class, initializing the base Entity class with the given parameters.
 * @param pBoard Pointer to the game board.
 */
Mario::Mario(const Board* pBoard) 
    : Entity(pBoard, Board::MARIO, { -1, -1}) {}


/**
 * @brief Updates Mario's direction based on the key input.
 * @param key The key input to determine the direction.
 */
void Mario::update_dir(char key) {

	// Convert key to lowercase Ctrl type
    Ctrl ctrl = static_cast<Ctrl>(std::tolower(key));

    // Convert key to direction (ignore non-defined keys)
    switch (ctrl) {
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

// @brief Updates Mario's score and check if he deserves a bonus life 
bool Mario::update_score(Points points) {
	score += static_cast<int>(points);// Add the points to the score
    if (score < 0) { score = 0; } // If the score is negative, set it to 0
    return check_for_bonus();
}

/**
 * @brief Checks for bonus life eligibility.
 *'bonus_tracker' tracks the number of bonuses granted to Mario,
 * ensuring that every time Mario's score reaches a multiple of 15 points, he is granted an extra life.
 * @return True if a bonus life was granted, false otherwise.
 */
bool Mario::check_for_bonus()
{
    // If the score is a multiple of the bonus life threshold
    // And Mario doesn't have a maximum life.
    if (score >= static_cast<int>(Points::BONUS_LIFE_THRESHOLD) * bonus_tracker
        && lives_left < MAX_LIVES)
    {
        lives_left++; // Increase the number of lives
        bonus_tracker++; // Increment the bonus tracker
        return true; // Return true if a bonus was given
    }

    return false;
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
		set_dy(0);
        jump_ascend = jump_descend = 0;
        fall_count = 0; // Reset the fall count
    }
}

/**
 * @brief Handles Mario's CLIMBING logic.
 */
void Mario::handle_climbing() {
    if (get_dy() == -1) {
        state = State::CLIMBING;
        climb_up(); // Continue CLIMBING up

        // If Mario reaches the top of the ladder
        if (behind_ch() == Board::AIR) {
            state = State::IDLE;
            set_dy(0);
        }
    }
    else {
        state = State::CLIMBING;
        climb_down(); // Continue CLIMBING down

        // If Mario reaches the floor
        if (board->is_floor(get_pos() + get_dir())) {
            state = State::IDLE;
            set_dy(0);
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
            set_dir(get_lastdx(), 0);
        }
    }
}

/**
 * @brief Handles Mario's IDLE logic.
 */
void Mario::handle_idle() {
    if (off_ground()) {
		set_last_dx(get_dx());
        handle_falling();
    }
    else {
        switch (get_dy()) {
        case -1: // If Mario is moving up
            if (can_climb()) { // If Mario can climb
                handle_climbing();
            }
			else if (can_jump()) { // If Mario can't climb check if he can jump
                handle_jumping();
            }
            else {
				set_dy(0); // If Mario can't climb or jump, reset the vertcal direction
            }
            break;
        case 1: // If Mario is moving down
            if (can_climb()) { // If Mario can climb
                handle_climbing();
            }
			else {
				set_dy(0); // If Mario can't climb, reset the vertical direction
			}
            break;
        default: // If Mario is on the ground  
            step(); // move Mario one step
            break;
        }
    }
}

/**
 * @brief Makes Mario jump.
 */
void Mario::jump() {
    if (jump_ascend < JMP_H && board->path_clear(get_pos() + get_dir())) { // If Mario is ascending
        jump_ascend++;
		set_dy(-1);
        step();
    }
    else if (jump_descend < JMP_H && off_ground()) { // If Mario is descending
        jump_descend++;
		set_dy(1);
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
	set_dir(0, 1); // Set the direction to fall
    step();
}

/**
 * @brief Makes Mario climb up.
 */
void Mario::climb_up() {
	set_dx(0);
    step();
}

/**
 * @brief Makes Mario climb down.
 */
void Mario::climb_down() {
    set_dx(0);
    step();
}

/**
 * @brief Checks if Mario can climb.
 * @return True if Mario can climb, false otherwise.
 */
bool Mario::can_climb() const {
    Coordinates pos = get_pos();
    return (get_dy() == -1 && behind_ch() == Board::LADDER) || (get_dy() == 1 && board->get_char(pos.x, pos.y + 2) == Board::LADDER);
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
    char obst = getch_console(get_pos() + get_dir());

    switch (obst) {
    case Board::BARREL: // If Mario hits a barrel
        mario_hit = true; // Set Mario as hit
        break;
	case Board::GHOST: // If Mario hits a ghost
		mario_hit = true; // Set Mario as hit
		break;
    case Board::HAMMER: // If Mario hits a hammer
        armed = true;// Set Mario as having a hammer
        set_icon(Board::SUPER_MARIO); // Change Mario's icon to Mario with a hammer
        break;
    case Board::PAULINE: // If Mario hits Pauline
        update_score(Points::PAULINE_RESCUED);
        rescued_pauline = true; // Set Mario as saved Pauline
        break;
    case Board::ERR: // If Mario's next step is out of bounds
        invert_dir(); // Reverse direction if path is not clear
        obst = Board::AIR; // Return air to allow Mario to move
        break;
	default: // If Mario hits a wall or floor
        if (board->is_floor(obst) || obst == Board::WALL) {
			invert_dir(); // Reverse direction if path is not clear
			obst = Board::AIR;
        }
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
	update_score(Points::LIFE_LOST);
}

/**
* @brief Gets the number of points Mario has.
* @return The number of points.
*/
int Mario::get_score() const {
	return score;
}

/**
 * @brief Resets Mario to its initial fields.
 */
void Mario::fatory_reset() {
    score = 0;
    bonus_tracker = 1;
    lives_left = MAX_LIVES;
    reset();
}

/**
 * @brief Resets Mario to the next level
 */
void Mario::reset() {

	Entity::reset();
	set_icon(Board::MARIO);

    mario_hit = false;
    rescued_pauline = false;
    armed = false;
    state = State::IDLE;

    fall_count = 0;
    jump_ascend = 0;
    jump_descend = 0;
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
bool Mario::has_rescued_pauline() const {
    return rescued_pauline;
}

/**
 * @brief Checks if Mario picked up the hammer.
 * @return true if he picked up the hammer, false otherwise
 */
bool Mario::is_armed() const {
    return armed;
}