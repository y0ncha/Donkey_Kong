#include "Barrels.h"
#include "Level.h"

/**
 * @brief Constructor to initialize the Barrels class.
 * @param pBoard Pointer to the game board.
 * @param dif_lvl Difficulty level.
 */
Barrels::Barrels(const Board* pBoard, Difficulty dif_lvl)
    : board(pBoard),
    amount(difficulty.at(dif_lvl).first),
	interval(difficulty.at(dif_lvl).second) {

    // Initialize the barrels with the board pointer
    barrels.reserve(amount);
    for (size_t i = 0; i < static_cast<size_t>(amount); i++) {
        barrels.emplace_back(std::make_unique<Barrel>(board)); // Unique pointer used as a preparation for the next exercises
    }
}

/**
 * @brief Copy constructor for the Barrels class.
 * @param other The Barrels object to copy from.
 */

Barrels::Barrels(const Barrels& other)
    : board(other.board),
      interval(other.interval),
      amount(other.amount),
      hit_mario(other.hit_mario) {

    barrels.reserve(other.barrels.size());
    for (const auto& barrel : other.barrels) {
        barrels.emplace_back(std::make_unique<Barrel>(*barrel));
    }
}

/**
 * @brief Copy assignment operator for the Barrels class.
 * @param other The Barrels object to copy from.
 * @return A reference to this Barrels object.
 */
Barrels& Barrels::operator=(const Barrels& other) {
    if (this != &other) {
        board = other.board;
        interval = other.interval;
        amount = other.amount;
        hit_mario = other.hit_mario;

        barrels.clear();
        barrels.reserve(other.barrels.size());
        for (const auto& barrel : other.barrels) {
            barrels.emplace_back(std::make_unique<Barrel>(*barrel));
        }
    }
    return *this;
}

/**
 * @brief Moves all active barrels and returns if Mario was hit.
 * @param frames The current frame count.
 */
void Barrels::move_all(int frames) {
    bool spawn_flag = false; // Flag to indicate if a new barrel should be spawned

    for (auto& barrel : barrels) {
        if (barrel->is_active()) { // If the barrel is active, move it
            barrel->move();

            if (barrel->hitted_mario()) {
                hit_mario = true;
                break;
            }
        } else if (frames % interval == 0 && !spawn_flag) { // If the barrel is not active and the interval has passed
            spawn_flag = true;
            barrel->spawn();
        }
    }
}

/**
 * @brief Resets the barrels.
 */
void Barrels::reset_all() {
    hit_mario = false;

    for (auto& barrel : barrels) {
        barrel->reset();
    }
}

/**
 * @brief Checks if Mario was hit by a barrel.
 * @return True if Mario was hit, false otherwise.
 */
bool Barrels::hitted_mario() const {
    return hit_mario;
}

/**
* @brief Checks if a barrel is in  a given position
* vanishes the barrel if it is and return true, false otherwise.
* @param pos The position to check.
* @param dir The direction of the barrel.
* @return True if the barrel is in the given position, false otherwise.
*/
void Barrels::was_hit(Coordinates pos) {

    for (auto& barrel : barrels) {

        // If the barrel is inactive skip it
        if (!barrel->is_active()) continue;

        if (pos == barrel->get_pos()) {
            gotoxy(barrel->get_pos());
            std::cout << "*";
            Sleep(150);

            barrel->reset();
            break;
        };
    }
}
