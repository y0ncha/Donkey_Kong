#include "Barrel.h"

/**
 * @brief Constructor for the Barrel class.
 * @param pBoard Pointer to the game board.
 */
Barrel::Barrel(const Board* pBoard) 
    : Entity(pBoard, Board::BARREL, {-1, -1}) { 
	init_pos();
}

/**
 * @brief Method to handle the movement logic of the barrel.
 */
void Barrel::move() {
    char beneath = beneath_ch();

    if (state == State::FALLING) {
        handle_falling();
    } else {
        update_dir(beneath);
        step();
    }
}

/**
 * @brief Method to handle the direction change when the barrel is on different types of floors.
 * @param beneath The character beneath the barrel.
 */
void Barrel::update_dir(char beneath) {
    switch (beneath) {
        case Board::FLOOR_L:
            last_dx = dir.x = -1; // Move left
            break;
        case Board::FLOOR_R:
            last_dx = dir.x = 1; // Move right
            break;
        case Board::AIR:
            state = State::FALLING; // Set the State to FALLING
            dir = {0, 1}; // Move down
            fall_count++;
            break;
        default:
            break;
    }
}

/**
 * @brief Method to handle the falling of the barrel.
 */
void Barrel::handle_falling() {
    fall_count++;
    dir = {0, 1}; // Set the direction to fall and step
    step();

    if (on_ground() && !hitted_mario()) {
        if (fall_count >= MAX_FALL_H) {
            explode();
        } else {
            dir = {last_dx, 0};
            state = State::IDLE;
            fall_count = 0;
        }
    }
}

/**
 * @brief Method to handle the explosion of the barrel.
 */
void Barrel::explode() {
    reset();

    for (int i = 0; i <= EXPLOSION_RADIUS; i++) {
        print_explosion_phase(i);
        clear_explosion_phase(i - 1);
        Sleep(EXPLOSSION_DELAY);
    }
    clear_explosion_phase(EXPLOSION_RADIUS);
}

/**
 * @brief Method to print the explosion phase within a given radius.
 * @param radius The radius of the explosion phase.
 */
void Barrel::print_explosion_phase(int radius) {
    if (radius == 0) {
        gotoxy(point.pos);
        if (getch_console(point.pos) == Board::MARIO) {
            state = State::HIT_MARIO;
        }
        std::cout << "*";
    } else {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                if (getch_console({point.pos.x + i, point.pos.y + j}) == Board::MARIO) {
                    state = State::HIT_MARIO;
                }
                gotoxy(point.pos.x + i, point.pos.y + j);
                std::cout << "*";
            }
        }
    }
}

/**
 * @brief Method to clear the explosion phase within a given radius.
 * @param radius The radius of the explosion phase to clear.
 */
void Barrel::clear_explosion_phase(int radius) {
    if (radius == -1) {
        gotoxy(point.pos);
        std::cout << board->get_char(point.pos);
    } else {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                gotoxy(point.pos.x + i, point.pos.y + j);
                std::cout << board->get_char(point.pos.x + i, point.pos.y + j);
            }
        }
    }
}

/**
 * @brief Checks if the barrel is active.
 * @return True if the barrel is active, false otherwise.
 */
bool Barrel::is_active() const {
    return active;
}

/**
 * @brief Returns and sets the initial position of the barrel randomly to the left or right of Donkey Kong.
 * @return The initial position of the barrel.
 */
Coordinates Barrel::init_pos() {
    // Get the potion of Donkey Kong
	Coordinates pos_l, pos_r, pos = board->get_pos(Board::DONKEY_KONG);

	pos_r = board->x_inbound(pos.x + 1) ? pos + Coordinates{ 1, 0 } : pos;
	pos_l = board->x_inbound(pos.x - 1) ? pos + Coordinates{ -1, 0 } : pos;

    return set_pos((rand() % 2 == 0) ? pos_r : pos_l);
}

/**
 * @brief Sets the original and current board for the barrel.
 * @param pBoard Pointer to the game board.
 */
void Barrel::set_board(const Board* pBoard) {
    board = pBoard;
}

/**
 * @brief Spawns the barrel at the initial position and activates it.
 */
void Barrel::spawn() {
    init_pos();
    active = true;
    set();
}

/**
 * @brief Handles collision logic for the barrel.
 * @return The type of object the barrel collides with.
 */
char Barrel::handle_collision() {
    char obst = getch_console(point.pos + dir);

    switch (obst) {
        case Board::MARIO:
            state = State::HIT_MARIO;
            break;
        case Board::ERR:
            reset();
            break;
    }
    return obst;
}

/**
 * @brief Resets the barrel state and direction.
 */
void Barrel::reset() {
    vanish();
    dir = {0, 0};
    state = State::IDLE;
    fall_count = 0;
    active = false;
}

/**
 * @brief Checks if the barrel hit Mario.
 * @return True if the barrel hit Mario, false otherwise.
 */
bool Barrel::hitted_mario() const {
    return (state == State::HIT_MARIO);
}
