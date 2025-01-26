#include "Play_Game.h"

/**
 * @brief Sets the level.
 * @param screen The level file name.
 * @return True if the level was set, false otherwise.
 */
bool Play_Game::load_level(const std::string& screen) {
	// Free the current level
	curr_level.reset();

	// Check if the screen is empty
	if (screen.empty()) return false;

	if (mode == Game_Mode::REGULAR) {
		curr_level = std::make_unique<Regular_Level>(screen, mario, diff);
	}
	else if (mode == Game_Mode::SAVE) {
		curr_level = std::make_unique<Save_Level>(screen, mario, diff, seed);
	}
	// If non of the above or the allocation failed return false
	return curr_level != nullptr;
}
