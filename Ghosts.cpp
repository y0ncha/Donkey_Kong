#include "Ghosts.h"

// Constructor for the Ghosts class
Ghosts::Ghosts(const Board* pBoard) : board(pBoard) {
    set_amount();
	set_all();
}

// Copy constructor for the Ghosts class
Ghosts::Ghosts(const Ghosts& other) : board(other.board), amount(other.amount), hit_mario(other.hit_mario) {
    ghosts.reserve(amount);
    for (const auto& ghost : other.ghosts) {
        ghosts.emplace_back(std::make_unique<Ghost>(*ghost));
    }
}

// Copy assignment operator for the Ghosts class
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

// Method to move all ghosts
void Ghosts::move_all() {
    check_ghosts_collision();
    for (auto& ghost : ghosts) {
		ghost->move();
		if (ghost->is_hit_mario()) {
			hit_mario = true;
		}
    }
}
// Method to reset all ghosts
void Ghosts::reset_all() {
	hit_mario = false;
	for (auto& ghost : ghosts) {
		ghost->reset();
	}
}
// Method to initialize all ghosts at the beginning of the level
void Ghosts::set_all()
{
    ghosts.reserve(amount);
    for (int i = 0; i < amount; i++) {
        auto temp = std::make_unique<Ghost>(board);
        temp->set(i);
        ghosts.emplace_back(std::move(temp));
    }
}

// Method to set amount of ghosts
void Ghosts::set_amount() {
    amount = board->icon_size(Board::GHOST);
}

// Method to check ghosts collision
void Ghosts::check_ghosts_collision() const {

    for (size_t i = 0; i < ghosts.size(); ++i) {
        for (size_t j = i + 1; j < ghosts.size(); ++j) {
            if ((ghosts[i]->get_pos() + ghosts[i]->get_dir() == ghosts[j]->get_pos() + ghosts[j]->get_pos()) ||
                (ghosts[i]->get_pos() == ghosts[j]->get_pos()) ||
                (ghosts[i]->get_pos() == ghosts[j]->get_pos() + ghosts[j]->get_pos()) ||
                (ghosts[i]->get_pos() + ghosts[i]->get_dir() == ghosts[j]->get_pos()))
            {
                ghosts[i]->invert_dir();
                ghosts[j]->invert_dir();
            }
        }
    }
}
// Method to check if Mario was hit
bool Ghosts::hitted_mario() const{
    return hit_mario;
}