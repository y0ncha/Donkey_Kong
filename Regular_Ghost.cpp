#include "Regular_Ghost.h"

//constructor for the Regular_Ghost class
Regular_Ghost::Regular_Ghost(const Board* pBoard) : Ghost_Base(pBoard, Board::Regular_Ghost, { -1, -1 }) {
}

//method to handle the movement logic of the Regular_Ghost
void Regular_Ghost::move() {
    update_dir();
    step();
}

// Clone method implementation
std::unique_ptr<Ghost_Base> Regular_Ghost::clone() const {
    return std::make_unique<Regular_Ghost>(*this);
}

