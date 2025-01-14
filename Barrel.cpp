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
    update_dir(beneath);

    if (state == State::FALLING) {
        handle_falling();
    }
    else {
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
            set_dx(-1); // Move left
            break;
        case Board::FLOOR_R:
			set_dx(1); // Move right
            break;
        case Board::AIR:
            state = State::FALLING; // Set the State to FALLING
            break;
        case Board::ERR:
            reset();
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
    set_dir(0, 1); // Set the direction to fall and step
    step();

	// If the barrel falls out of the screen
	if (beneath_ch() == Board::ERR) {
        reset();
        return;
	}

    if (on_ground() && !hitted_mario()) {
        if (fall_count >= MAX_FALL_H) {
            explode();
        } 
        else {
            set_dir(get_lastdx(), 0);
            state = State::IDLE;
            fall_count = 0;
        }
    }
}

/**
 * @brief Method to handle the explosion of the barrel.
 */
void Barrel::explode() {
    Coordinates pos = get_pos();
    reset();
    for (int i = 0; i <= EXPLOSION_RADIUS; i++) {
        print_explosion_phase(i, pos);
        clear_explosion_phase(i - 1, pos);
        Sleep(EXPLOSSION_DELAY);
    }
    clear_explosion_phase(EXPLOSION_RADIUS, pos);
}

/**
 * @brief Method to print the explosion phase within a given radius.
 * @param radius The radius of the explosion phase.
 */
void Barrel::print_explosion_phase(int radius, Coordinates pos) {

    if (radius == 0) {
        gotoxy(pos);
        char atPos = getch_console(pos);
        if (atPos == Board::MARIO || atPos == Board::SUPER_MARIO) {
            state = State::HIT_MARIO;
        }
        std::cout << "*";
    } 
    else {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
				Coordinates dest = { pos.x + i, pos.y + j };
				if (board->pos_inbound(dest)) {
					gotoxy(dest);
                    char atDest = getch_console(dest);
                    if (atDest == Board::MARIO || atDest == Board::SUPER_MARIO) {
						state = State::HIT_MARIO;
					}
					std::cout << "*";
				}
            }
        }
    }
}

/**
 * @brief Method to clear the explosion phase within a given radius.
 * @param radius The radius of the explosion phase to clear.
 */
void Barrel::clear_explosion_phase(int radius, Coordinates pos) {
    if (radius == -1) {
        gotoxy(pos);
        std::cout << board->get_char(pos);
    } else {
        for (int i = -radius; i <= radius; i++) {
            for (int j = -radius; j <= radius; j++) {
                gotoxy(pos.x + i,pos.y + j);
                std::cout << board->get_char(pos.x + i, pos.y + j);
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
    // Get the position of Donkey Kong
    Coordinates pos = board->get_pos(Board::DONKEY_KONG);
    Coordinates pos_l = { pos.x - 1, pos.y };
    Coordinates pos_r = { pos.x + 1, pos.y };

    // Validate positions
    bool valid_l = board->pos_inbound(pos_l) && board->path_clear(pos_l);
    bool valid_r = board->pos_inbound(pos_r) && board->path_clear(pos_r);

    // If one side is invalid, set it to the other side
	if (valid_r && valid_l) {
        // Set the barrel's position randomly to either pos_l or pos_r
        return set_pos((rand() % 2 == 0) ? pos_r : pos_l);
	}
    else if (!valid_l && valid_r) {
        // Set the barrel's position randomly to either pos_l or pos_r
        return set_pos(pos_r);
	}
	else if (!valid_r && valid_l) {
		// Set the barrel's position randomly to either pos_l or pos_r
		return set_pos(pos_l);
	}
    else {
		return set_pos(-1, -1);
    }
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
    char obst = getch_console(get_pos() + get_dir());

    switch (obst) {
	    case Board::MARIO: // If the barrel hits Mario
        case Board::SUPER_MARIO:
            state = State::HIT_MARIO;
            break;
		case Board::WALL: // If the barrel hits a wall
			reset();
			break;
		case Board::ERR: // If the barrel is out of bounds
            reset();
            break;
        default: // If a barrel is about to collide with a floor from the side, stop it
			if (board->is_floor(obst)) invert_dir();
            break;
    }
    return obst;
}

/**
 * @brief Resets the barrel state and direction.
 */
void Barrel::reset() {
	Entity::reset();
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
