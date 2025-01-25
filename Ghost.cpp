#include "Ghost.h"

//constructor for the Ghost class
Ghost::Ghost(const Board* pBoard) : GhostEntity(pBoard, Board::GHOST, { -1, -1 }) {
}

//method to handle the movement logic of the ghost
void Ghost::move() {
    update_dir();
    step();
}

// Clone method implementation
std::unique_ptr<GhostEntity> Ghost::clone() const {
    return std::make_unique<Ghost>(*this);
}

