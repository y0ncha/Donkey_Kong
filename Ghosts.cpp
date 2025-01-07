#include "Ghosts.h"

/**
 * @brief Constructor for the Ghosts class.
 * @param pBoard Pointer to the game board.
 */
Ghosts::Ghosts(const Board* pBoard) : board(pBoard) {
    set_amount();
    set_all();
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
    check_ghosts_collision();
    for (auto& ghost : ghosts) {
        ghost->move();
        if (ghost->is_hit_mario()) {
            hit_mario = true;
        }
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
void Ghosts::set_all() {
    ghosts.reserve(amount);
    for (int i = 0; i < amount; i++) {
        auto temp = std::make_unique<Ghost>(board);
        temp->set(i);
        ghosts.emplace_back(std::move(temp));
    }
}

/**
 * @brief Method to set the amount of ghosts.
 */
void Ghosts::set_amount() {
    amount = board->get_entity_count(Board::GHOST);
}

/**
 * @brief Method to check collisions between ghosts.
 */
void Ghosts::check_ghosts_collision() const {

    for (size_t i = 0; i < ghosts.size(); ++i) {
        for (size_t j = i + 1; j < ghosts.size(); ++j) {
            if ((ghosts[i]->get_pos() + ghosts[i]->get_dir() == ghosts[j]->get_pos() + ghosts[j]->get_pos()) ||
                (ghosts[i]->get_pos() == ghosts[j]->get_pos()) ||
                (ghosts[i]->get_pos() == ghosts[j]->get_pos() + ghosts[j]->get_pos()) ||
                (ghosts[i]->get_pos() + ghosts[i]->get_dir() == ghosts[j]->get_pos())) {
                ghosts[i]->invert_dir();
                ghosts[j]->invert_dir();
            }
        }
    }
}

/**
 * @brief Method to check if Mario was hit by any ghost.
 * @return True if Mario was hit, false otherwise.
 */
bool Ghosts::hitted_mario() const {
    return hit_mario;
}