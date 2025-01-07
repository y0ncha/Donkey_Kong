#include "Game.h"

/**
 * @brief Constructor for the Game class.
 */
Game::Game() 
    : mario(nullptr), display(Display::get_instance(this)) {}

/**
 * @brief Starts the game loop and handles user input.
 * @return The game state after the game loop ends (FIN_SUC, FIN_FAIL, TERMINATE).
 */
Game_State Game::start() {

    show_cursor(false); // Hide the console cursor for better visuals
	scan_for_fnames(); // Scan for level files in the specified directory
    display.main_menu();

    // Dynamic allocation to ease the level incrementation and to initiate level only after all the needed data is available
    curr_level = std::make_unique<Level>(pop_fname(lvl_ind), mario, dif_lvl);

    while (state != TERMINATE) {
		// Main game loop mamging the different states of the game
        switch (state) {
		case RUN: // Run the game
            state = curr_level->start();
            break;
		case PAUSE: // Pause the game
            display.pause_menu();
            break;
		case LVL_RESET: // Reset the level
			curr_level->reset_level();
            display.strike_messege();
			state = RUN;
            break;
		case FIN_FAIL: // Finish the game unsuccessfully
            curr_level->reset_level();
            display.failure_messege();
            state = TERMINATE;
            break;
		case FIN_SUC: // Finish the game successfully
            lvl_ind++;
            if (lvl_ind < level_fnames.size()) { // Check if there are more levels
                display.success_messege(); // todo change to fin game and fin level
                state = RUN;
				advance_level(pop_fname(lvl_ind));
			}
			else { // If all the levels are finished, exit the game
                display.success_messege(); // todo change to fin game and fin level
                state = TERMINATE;
            }
            break;
        }
    }
    display.exit_messege();
	return state;
}

/**
 * @brief Advances to the next level.
 * @param fname The filename of the next level.
 */
void Game::advance_level(const std::string& fname) {
    // Using move constructor to pass the current level to avoid memory reaclocation
    curr_level->reset_level();
    curr_level = std::make_unique<Level>(std::move(*curr_level), fname);
 }

/**
 * @brief Validates and sets the game status.
 * @param stat The status to set.
 */
bool Game::set_state(Game_State _state) {
    switch (_state) {
    case TERMINATE:
    case RUN:
    case PAUSE:
    case LVL_RESET:
    case FIN_FAIL:
    case FIN_SUC:
    case IDLE:
        state = _state;
        return true;
    default:
        return false;
    }
}

/**
 * @brief Gets the game status.
 */
Game_State Game::get_state() const {
    return state;
}

/**
 * @brief Validate and sets the game difficulty.
 * @param dif The difficulty to set.
 */
bool Game::set_difficulty(Difficulty dif) {

    switch (dif) {
    case EASY:
    case MEDIUM:
    case HARD:
        dif_lvl = dif;
        return true;
    default:
        return false;
    }
}

/**
 * @brief Gets the game difficulty.
 */
Difficulty Game::get_difficulty() const {
    return dif_lvl;
}

/**
 * @brief Validate and sets the level index.
 * @param ind The indemenagifull name for x to set.
 */
bool Game::set_level(short ind) {
    if (0 <= ind && ind < NOF_LEVELS) {
        lvl_ind = ind;
        return true;
    }
    return false;
}

/**
 * @brief Gets the number of lives Mario has left.
 * @return The number of lives left.
 */
int Game::get_mario_lives() const {
    return mario.get_lives();
}

/**
 * @brief Adds a filename to the list of level files in alphabetical order if it doesn't already exist.
 * @param fname The filename to add.
 * @return True if the filename was added, false if it already exists.
 */
bool Game::push_fname(const std::string& fname) {
    // Find the position where the filename should be inserted to keep the list sorted
    auto it = std::lower_bound(level_fnames.begin(), level_fnames.end(), fname);

	// Check if the filename already exists in the list and if the list is not full
    if (it != level_fnames.end() && *it == fname) {
        return false; // File already exists in the list
    }
    else {
        // Insert the filename at the correct position
        level_fnames.insert(it, fname);
        return true;
    }
}

/**
* @brief Gets the list of level filenames.
* @return The list of level filenames.
*/
const std::list<std::string>& Game::get_fnames() const {
    return level_fnames;
}

/**
 * @brief Scans for level files in the specified directory that match the template "dkong_$number.screen".
 * @param directory The directory to scan for level files.
 */
void Game::scan_for_fnames(const std::string& directory) {

    std::regex pattern(R"(dkong_[a-zA-Z0-9]+\.screen(\.txt)?)");
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (std::regex_match(filename, pattern)) {
                push_fname(filename);
            }
        }
    }
}

/**
* @brief Pops the level filename at the specified index.
 * @param i The index of the filename to pop.
 * @return The filename at the specified index.
 */
const std::string& Game::pop_fname(int i) {
	auto it = level_fnames.begin();
	std::advance(it, i);
	return *it;
}

/**
 * @brief Gets the number of levels.
 * @return The number of levels.
 */
int Game::get_nof_levels() const {
    return (int)level_fnames.size();
}

