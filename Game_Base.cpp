#include "Game_Base.h"
#include "Regular_Level.h"
#include "Visual_Level.h"
#include "Silent_Level.h"
#include "Save_Level.h"

/**
 * @brief Constructor for the Game_Base class.
 */
Game_Base::Game_Base(Game_Mode mode) :
	mode(mode),
    state(Game_State::IDLE),
    diff(Difficulty::EASY),
    level_ind(0),
	mario(nullptr), // Passing nullptr until the level is initialized
    display(Display::get_instance(this)), // Singleton pattern
    hall_of_fame(Hof::get_instance()), // Singleton pattern
    curr_level(nullptr),
    screens(),
    seed(0) { // Default initialization of std::list
    scan_for_screens(); // Scan for level files
}

/**
 * @brief Resets the Game_Base to its initial fields.
 */
void Game_Base::reset() {
	stats = {}; // Reset the statistics
	level_ind = 0;

	diff = Difficulty::EASY;
	state = Game_State::IDLE;

	curr_level.reset(); // Free current level
	mario.factory_reset(); // Reset Mario to its initial feilds
}

/**
 * @brief Saves the Game_Base statistics.
 */
void Game_Base::update_statistics() {
	stats.score = mario.get_score();
	stats.difficulty = static_cast<int>(diff);
}

/**
 * @brief Gets the Game_Base's statisitcs
 */
const Hof::Statistics& Game_Base::get_statistics() const {
	return stats;
}

/**
 * @brief Sets the current level.
 * @param screen The filename of the level to set.
 * @return A vector of error codes.
 */
std::vector<Board::Err_Code> Game_Base::set_level(const std::string& screen) {
	
    std::vector<Board::Err_Code> errors;

	// Check if the level was loaded propely
	if (!load_level(screen)) {
		errors.push_back(Board::Err_Code::SCREEN_FAIL);
	}
	else {
		errors = curr_level->get_errors();
	}
	return errors;
}

/**
 * @brief Validates and sets the Game_Base status.
 * @param stat The status to set.
 */
bool Game_Base::set_state(Game_State _state) {
    switch (_state) {
    case Game_State::TERMINATE:
    case Game_State::EXIT:
    case Game_State::RUN:
    case Game_State::PAUSE:
    case Game_State::RETRY:
    case Game_State::FAIL:
    case Game_State::SUCCESS:
    case Game_State::IDLE:
        state = _state;
        return true;
    default:
        return false;
    }
}

/**
 * @brief Gets the Game_Base status.
 */
Game_State Game_Base::get_state() const {
    return state;
}

/**
 * @brief Validate and sets the Game_Base difficulty.
 * @param dif The difficulty to set.
 */
bool Game_Base::set_difficulty(Difficulty dif) {

    switch (dif) {
    case Difficulty::EASY:
    case Difficulty::MEDIUM:
    case Difficulty::HARD:
        diff = dif;
        return true;
    default:
        return false;
    }
}

/**
 * @brief Gets the Game_Base difficulty.
 */
Difficulty Game_Base::get_difficulty() const {
    return diff;
}

/**
 * @brief Validate and sets the level index.
 * @param ind The indemenagifull name for x to set.
 */
bool Game_Base::set_index(short ind) {
    if (0 <= ind && ind < get_nof_screens()) {
        level_ind = ind;
        return true;
    }
    return false;
}

/**
 * @brief Gets the number of lives Mario has left.
 * @return The number of lives left.
 */
int Game_Base::get_mario_lives() const {
    return mario.get_lives();
}

/**
 * @brief Adds a filename to the list of level files in alphabetical order if it doesn't already exist.
 * @param screen The filename to add.
 * @return True if the filename was added, false if it already exists.
 */
bool Game_Base::push_screen(const std::string& screen) {
    // Find the position where the filename should be inserted to keep the list sorted
    auto it = std::lower_bound(screens.begin(), screens.end(), screen);

	// Check if the filename already exists in the list and if the list is not full
    if (it != screens.end() && *it == screen) {
        return false; // File already exists in the list
    }
    else {
        // Insert the filename at the correct position
        screens.insert(it, screen);
        return true;
    }
}

/**
* @brief Gets the list of level filenames.
* @return The list of level filenames.
*/
const std::list<std::string>& Game_Base::get_screens() const {
    return screens;
}

/**
 * @brief Scans for level files in the specified directory that match the template "dkong_$number.screen".
 * @param directory The directory to scan for level files.
 */
void Game_Base::scan_for_screens(const std::string& directory) {

    std::regex pattern(R"(dkong_[a-zA-Z0-9]+\.screen(\.txt)?)");
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (std::regex_match(filename, pattern)) {
                push_screen(filename);
            }
        }
    }
}

/**
 * @brief Pops the level filename at the specified index.
 * @param i The index of the filename to pop.
 * @return The filename at the specified index.
 */
const std::string& Game_Base::pop_screen(int i) const {

	// If the index is -1, set it to the current level index
    if (i == -1) i = level_ind;

	// Check if the index is out of bounds
    if (i < 0 || i >= screens.size()) return empty;

	// Get the filename at the specified index
	auto it = screens.begin();
	std::advance(it, i);
	return *it;
}

/**
 * @brief Gets the number of levels.
 * @return The number of levels.
 */
int Game_Base::get_nof_screens() const {
    return (int)screens.size();
}

/**
 * @brief Sets the nickname of the player.
 * @param name The nickname to set.
 * @note The nickname is limited to 6 characters.
 */
void Game_Base::set_nickname(const std::string& name) {
    strcpy_s(stats.player_name, sizeof(stats.player_name), name.c_str());
}

/**
 * @brief Gets the hall of fame list.
 * @return The hall of fame list.
 */
const std::list<Hof::Statistics>& Game_Base::get_hof() const {
    return hall_of_fame.get_list();
}