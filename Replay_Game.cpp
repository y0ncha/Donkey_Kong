#include "Replay_Game.h"

/**
 * @brief Loads the level from the specified file.
 * @param screen The filename of the level to load.
 * @return True if the level was loaded, false otherwise.
 */
bool Replay_Game::load_level(const std::string& screen) {

    curr_level.reset(); // Free current level

    // Set the level based on the game mode
    switch (mode) {
    case Game_Mode::REGULAR:
        //curr_level = std::make_unique<Regular_Level>(screen, mario, diff);
        break;
    case Game_Mode::SAVE:
        //curr_level = std::make_unique<Save_Level>(screen, mario, diff, seed);
        break;
    case Game_Mode::LOAD:
        //curr_level = std::make_unique<Visual_Level>(screen, mario, diff);
        break;
    case Game_Mode::SILENT:
        //curr_level = std::make_unique<Silent_Level>(screen, mario, diff);
        break;
    default:
        curr_level = nullptr;
        break;
    }
    return curr_level != nullptr;
}