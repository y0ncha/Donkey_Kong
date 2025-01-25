#include "GhostMaster.h"

/**
 * @brief Constructor for the Ghost class.
 * @param pBoard Pointer to the game board.
 */
GhostMaster::GhostMaster(const Board* pBoard) : GhostEntity(pBoard, Board::SUPER_GHOST, { -1, -1 }), state(State::IDLE) {}

/**
 * @brief Moves the ghost by updating its direction and stepping.
 */
void GhostMaster::move() {
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
// Makes Ghost climb, up or down based on direction
void GhostMaster::climb() {
    set_dx(0);
    step();
}

// Checks if Ghost can climb down
bool GhostMaster::can_climb_down() const {
    Coordinates pos = get_pos();
    return (board->get_char(pos.x, pos.y + 2) == Board::LADDER);
}

// Checks if Ghost can climb up
bool GhostMaster::can_climb_up() const {
    Coordinates pos = get_pos();
    return (behind_ch() == Board::LADDER);
}

// Checks if Ghost can climb
bool GhostMaster::can_start_climb() const {
    return (can_climb_down() || can_climb_up());
}

void GhostMaster::handle_climbing() {
    if (get_dy() == -1) {
        state = State::CLIMBING;
        climb(); // Continue CLIMBING up

        // If Ghost reaches the top of the ladder
        if (behind_ch() == Board::AIR) {
            state = State::IDLE;
            set_dir({ get_lastdx(), 0 });
        }
    }
    else {
        state = State::CLIMBING;
        climb(); // Continue CLIMBING down

        // If Ghost reaches the floor
        if (board->is_floor(get_pos() + get_dir())) {
            state = State::IDLE;
            set_dir({ get_lastdx(), 0 });
        }
    }
}

// Checks if Ghost can continue climbing
bool GhostMaster::can_climb() const {
    Coordinates pos = get_pos();
    return (get_dy() == -1 && behind_ch() == Board::LADDER) || (get_dy() == 1 && board->get_char(pos.x, pos.y + 2) == Board::LADDER);
}

/**
 * @brief Deactivates the ghost.
 */
std::unique_ptr<GhostEntity> GhostMaster::clone() const {
    return std::make_unique<GhostMaster>(*this);
}