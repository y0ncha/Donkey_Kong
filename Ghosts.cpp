#include "Ghosts.h"
#include "Level.h"
/**
 * @brief Constructor for the Ghosts class.
 * @param pBoard Pointer to the game board.
 */
Ghosts::Ghosts(const Board* pBoard) : board(pBoard) {
    set_amount();
    ghosts.reserve(amount);

    for (int i = 0; i < amount; i++) {
        auto temp = std::make_unique<Ghost>(board);
        ghosts.emplace_back(std::move(temp));
    }
}

/**
 * @brief Copy constructor for the Ghosts class.
 * @param other The other Ghosts object to copy from.
 */
Ghosts::Ghosts(const Ghosts& other) : board(other.board), amount(other.amount), hit_mario(other.hit_mario) {
    ghosts.reserve(amount);
    for (const auto& ghost : other.ghosts) {
        ghosts.emplace_back(std::make_unique<Ghost>(*ghost));
    }
}

/**
 * @brief Copy assignment operator for the Ghosts class.
 * @param other The other Ghosts object to assign from.
 * @return Reference to the assigned Ghosts object.
 */
Ghosts& Ghosts::operator=(const Ghosts& other) {
    if (this != &other) {
        board = other.board;
        hit_mario = other.hit_mario;
        amount = other.amount;
        ghosts.clear();
        ghosts.reserve(amount);
        for (const auto& ghost : other.ghosts) {
            ghosts.emplace_back(std::make_unique<Ghost>(*ghost));
        }
    }
    return *this;
}

/**
 * @brief Method to move all ghosts.
 */
void Ghosts::move_all() {
    handle_colisions();
    for (auto& ghost : ghosts) {
        if (ghost->is_hit_mario()) {
            hit_mario = true;
        }
        ghost->move();
    }
}

/**
 * @brief Method to reset all ghosts.
 */
void Ghosts::reset_all() {
    hit_mario = false;
    for (auto& ghost : ghosts) {
        ghost->reset();
    }
}

/**
 * @brief Method to initialize all ghosts at the beginning of the level.
 */
void Ghosts::set_all() const {
    for (int i = 0; i < amount; i++) {
        ghosts[i]->set(i);
    }

}

/**
 * @brief Method to set the amount of ghosts.
 */
void Ghosts::set_amount() {
    amount = board->count_entity(Board::GHOST);
}

/**
 * @brief Method to check collisions between ghosts.
 */
void Ghosts::handle_colisions() {

    for (int i = 0; i < amount; i++) {
        for (int j = i + 1; j < amount; j++) {
            if (colide(ghosts[i], ghosts[j])) {
                ghosts[i]->invert_dir();
                ghosts[j]->invert_dir();
            }
        }
    }
}


/**
* @brief Checks if a ghost is in a given position
* vanishes the ghost if it is and return true, false otherwise.
* @param pos The position to check.
* */
void Ghosts::was_hit(Coordinates pos) {

    for (auto& ghost : ghosts) {

        // If the barrel is inactive skip it
        if (!ghost->is_active()) continue;

        if (pos == ghost->get_pos()) {
            gotoxy(ghost->get_pos());
            std::cout << "*";
            Sleep(150);

            ghost->reset();
            break;
        };
    }
}

/**
 * @brief Method to check if any ghost hit Mario.
 * @param g1 ghost by const ref.
 * @param g2 ghost by const ref.
 * @return True if Mario was hit, false otherwise.
 */
bool Ghosts::colide(const std::unique_ptr<Ghost>& g1, const std::unique_ptr<Ghost>& g2) const {

	return (g1->get_dest() == g2->get_dest() ||
		g1->get_pos() == g2->get_pos() ||
		g1->get_pos() == g2->get_dest() ||
		g1->get_dest() == g2->get_pos());
}
/**
 * @brief Method to check if Mario was hit by any ghost.
 * @return True if Mario was hit, false otherwise.
 */
bool Ghosts::hitted_mario() const {
    return hit_mario;
}