#include "Master_Ghost.h"

/**
 * @brief Constructor for the Master_Ghost class.
 * @param pBoard Pointer to the game board.
 */
Master_Ghost::Master_Ghost(const Board* pBoard, const Mario& mario) :
    Ghost_Base(pBoard, Board::SUPER_GHOST, { -1, -1 }), state(State::IDLE),
    mario(mario) {}

/**
 * @brief Moves the Master_Ghost by updating its direction and stepping.
 */
void Master_Ghost::move() {
    
	if (state == State::CLIMBING) {
        handle_climbing();
	}
    else if (seek_mario()) {
		state = State::CHASING;
        chase();
    }
    else {
	    random_move();
    }
}

/**
 * @brief Chasing mario according to the bias
 */
void Master_Ghost::chase() {

    if (can_climb_down() && bias.second == Bias::DOWN) {
		set_dy(1);
		state = State::CLIMBING;
		handle_climbing();
	}
	else if (can_climb_up() && bias.second == Bias::UP) {
		set_dy(-1);
		state = State::CLIMBING;
		handle_climbing();
	}
	else {
		update_dir();
		step();
	}
}

/**
 * @brief Checks if target is in the chase range.
 */
bool Master_Ghost::in_range(Coordinates target) const {
	Coordinates pos = get_pos();
	return (abs(pos.x - target.x) <= CHASE_RANGE && abs(pos.y - target.y) <= CHASE_RANGE);
}

/**
 * @brief Seek for mario to chase.
 */
bool Master_Ghost::seek_mario() {

    Coordinates target = mario.get_pos();
	Coordinates pos = get_pos();

	// If mario is not in the chase range, reset the bias
    if (!in_range(target)) {
        bias = { Bias::DEF, Bias::DEF };
        return false;
    }

	// If mario is in the chase range, set the bias according to mario's position
    if (pos.x == target.x) {
		bias.first = Bias::DEF;
    }
    else {
        bias.first = (pos.x < target.x) ? Bias::RIGHT : Bias::LEFT;
    }

	// If mario is in the same row, reset the bias
	if (pos.y == target.y) {
		bias.second = Bias::DEF;
	}
    else {
        bias.second = (pos.y < target.y) ? Bias::DOWN : Bias::UP;
        find_ladder();
    }

	// If the bias is set, return true
	return (bias != std::pair{ Bias::DEF, Bias::DEF });
}

/**
 * @brief Seek for ladder to go up or down.
 */
void Master_Ghost::find_ladder() {

    Coordinates pos = get_pos();
    int y = (bias.second == Bias::DOWN) ? pos.y + 2 : pos.y;
    int r_payh, l_path;

	// If the Master_Ghost is on a ladder, reset the bias
    if (board->get_char(pos.x, y) == Board::LADDER) {
		bias.first = Bias::DEF;
		return;
	}
	l_path = search_left(y);
	r_payh = search_right(y);
    
    // If there is no ladder, reset the bias
    if (l_path == 100 && r_payh == 100) {
        bias = { Bias::DEF, Bias::DEF };
    }
    else {
        // Set the direction to the nearest ladder
        bias.first = (l_path <= r_payh) ? Bias::LEFT : Bias::RIGHT;
    }

}

/**
 * @brief Search for a ladder to the left.
 */
int Master_Ghost::search_left(int y) const {

    Coordinates pos = get_pos();

    int l = pos.x - 1;

    while (board->x_inbound(l) && board->is_floor({ l, pos.y + 1 })) {
        if (board->get_char(l, y) == Board::LADDER) {
            return pos.x - l;
        }
        l--;
    }
    return 100;
}


/**
 * @brief Search for a ladder to the right.
 */
int Master_Ghost::search_right(int y) const {

    Coordinates pos = get_pos();

    int r = pos.x + 1;

    while (board->x_inbound(r) && board->is_floor({ r, pos.y + 1 })) {
        if (board->get_char(r, y) == Board::LADDER) {
            return r - pos.x;
        }
        r++;
    }
    return 100;
}


/**
 * @brief Moves the Master_Ghost by updating its direction and stepping.
 */
void Master_Ghost::random_move() {

    int probability = rand() % 100;

    if (state == State::CLIMBING) {
        handle_climbing();
    }

	if (state == State::CHASING) {
		state = State::IDLE;
		set_dx(1);
	}

    else if (probability < 40 && state == State::IDLE && can_start_climb()) {

        if (can_climb_up()) {
            set_dy(-1);
            state = State::CLIMBING;
            handle_climbing();
        }
        else if (can_climb_down()) {
            set_dy(1);
            state = State::CLIMBING;
            handle_climbing();
        }
    }
    else {
        Ghost_Base::update_dir();
        step();
    }
}

// Makes Master_Ghost climb, up or down based on direction
void Master_Ghost::climb() {
    set_dx(0);
    step();
}

// Checks if Master_Ghost can climb down
bool Master_Ghost::can_climb_down() const {
    Coordinates pos = get_pos();
    return (board->get_char(pos.x, pos.y + 2) == Board::LADDER);
}

// Checks if Master_Ghost can climb up
bool Master_Ghost::can_climb_up() const {
    Coordinates pos = get_pos();
    bool res = (behind_ch() == Board::LADDER);
    return res;
}

// Checks if Master_Ghost can climb
bool Master_Ghost::can_start_climb() const {
    return (can_climb_down() || can_climb_up());
}

void Master_Ghost::handle_climbing() {
    if (get_dy() == -1) {
        state = State::CLIMBING;
        climb(); // Continue CLIMBING up

        // If Master_Ghost reaches the top of the ladder
        if (behind_ch() == Board::AIR) {
            state = State::IDLE;
            set_dir({ get_lastdx(), 0 });
        }
    }
    else {
        state = State::CLIMBING;
        climb(); // Continue CLIMBING down

        // If Master_Ghost reaches the floor
        if (board->is_floor(get_pos() + get_dir())) {
            state = State::IDLE;
            set_dir({ get_lastdx(), 0 });
        }
    }
}

// Checks if Master_Ghost can continue climbing
bool Master_Ghost::can_climb() const {
    Coordinates pos = get_pos();
    return (get_dy() == -1 && behind_ch() == Board::LADDER) || (get_dy() == 1 && board->get_char(pos.x, pos.y + 2) == Board::LADDER);
}

/**
 * @brief Deactivates the Master_Ghost.
 */
std::unique_ptr<Ghost_Base> Master_Ghost::clone() const {
    return std::make_unique<Master_Ghost>(*this);
}

// method to reset the Master_Ghost
void Master_Ghost::reset() {
	Ghost_Base::reset();
	state = State::IDLE;
}

bool Master_Ghost::update_dir() {
    
	// If the bias is set, update the direction according to the bias
	if (bias.first == Bias::RIGHT) {
		set_dx(1);
	}
	else if (bias.first == Bias::LEFT) {
		set_dx(-1);
	}
	// If the move is not valid, stop
	if (!valid_move()) {
        set_dx(0);
	}
	return true;

}