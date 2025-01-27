#include "Master_Ghost.h"

/**
 * @brief Constructor for the Regular_Ghost class.
 * @param pBoard Pointer to the game board.
 */
Master_Ghost::Master_Ghost(const Board* pBoard) : Ghost_Base(pBoard, Board::SUPER_GHOST, { -1, -1 }), state(State::IDLE) {}

/**
 * @brief Moves the Regular_Ghost by updating its direction and stepping.
 */
void Master_Ghost::move() {
    int probability = rand() % 100;
    if (state == State::CLIMBING) {
        handle_climbing();
    }
    else if (probability < 30 && state == State::IDLE && can_start_climb()) {
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
        update_dir();
        step();
    }
}
// Makes Regular_Ghost climb, up or down based on direction
void Master_Ghost::climb() {
    set_dx(0);
    step();
}

// Checks if Regular_Ghost can climb down
bool Master_Ghost::can_climb_down() const {
    Coordinates pos = get_pos();
    return (board->get_char(pos.x, pos.y + 2) == Board::LADDER);
}

// Checks if Regular_Ghost can climb up
bool Master_Ghost::can_climb_up() const {
    Coordinates pos = get_pos();
    return (behind_ch() == Board::LADDER);
}

// Checks if Regular_Ghost can climb
bool Master_Ghost::can_start_climb() const {
    return (can_climb_down() || can_climb_up());
}

void Master_Ghost::handle_climbing() {
    if (get_dy() == -1) {
        state = State::CLIMBING;
        climb(); // Continue CLIMBING up

        // If Regular_Ghost reaches the top of the ladder
        if (behind_ch() == Board::AIR) {
            state = State::IDLE;
            set_dir({ get_lastdx(), 0 });
        }
    }
    else {
        state = State::CLIMBING;
        climb(); // Continue CLIMBING down

        // If Regular_Ghost reaches the floor
        if (board->is_floor(get_pos() + get_dir())) {
            state = State::IDLE;
            set_dir({ get_lastdx(), 0 });
        }
    }
}

// Checks if Regular_Ghost can continue climbing
bool Master_Ghost::can_climb() const {
    Coordinates pos = get_pos();
    return (get_dy() == -1 && behind_ch() == Board::LADDER) || (get_dy() == 1 && board->get_char(pos.x, pos.y + 2) == Board::LADDER);
}

/**
 * @brief Deactivates the Regular_Ghost.
 */
std::unique_ptr<Ghost_Base> Master_Ghost::clone() const {
    return std::make_unique<Master_Ghost>(*this);
}