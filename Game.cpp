#include "Game.h"

/**
 * @brief Constructor for the Game class.
 */
Game::Game()
    : state(Game_State::IDLE),
      dif_lvl(Difficulty::EASY),
      lvl_ind(0),
	  mario(nullptr), // Passing nullptr until the level is initialized
      display(Display::get_instance(this)), // Singleton pattern
      hall_of_fame(Hof::get_instance()), // Singleton pattern
      curr_level(nullptr), // Initialize unique_ptr with nullptr
      level_fnames() { // Default initialization of std::list
    scan_for_fnames(); // Scan for level files
}

/**
 * @brief Runs the game and saves the statistics. ( will be used to save a game in Ex.3)
 */
void Game::run() {

    show_cursor(false); // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr))); // Explicit cast to unsigned int
    
	if (!hall_of_fame.is_available()) { // Check if the hall of fame is online
		display.error_message("Hall of Fame isnt available - continue playing offline");
	}

	// Main game loop
    while (display.main_menu() != Display::Menu_Options::EXIT) {
		start();
        hall_of_fame.record_statistics(stats);
		reset();
    }
    // Display the exit message
    display.exit_message();
}

/**
 * @brief Starts the game loop and handles user input.
 * @return The game state after the game loop ends (FIN_SUC, FIN_FAIL, TERMINATE).
 */
void Game::start() {

    // Dynamic allocation to ease the level incrementation and to initiate level only after all the needed data is available
	set_level(pop_fname());

	// Start the timer
    auto start_t = start_timer();

	// Main game loop
    while (state != Game_State::TERMINATE) {
		// Main game loop mamging the different states of the game
        switch (state) {
        case Game_State::RUN: // Run the game
            state = curr_level->start();
            break;
        case Game_State::PAUSE: // Pause the game
            display.pause_menu();
            break;
        case Game_State::LVL_RESET: // Reset the level
            curr_level->reset_level();
            display.strike_message();
            state = Game_State::RUN;
            break;
        case Game_State::FIN_FAIL: // Finish the game unsuccessfully
            stats.time_played = stop_timer(start_t);
			save_statistics();
            curr_level->reset_level();
            display.failure_message();
            state = Game_State::TERMINATE;
            break;
        case Game_State::FIN_SUC: // Finish the game successfully
            lvl_ind++; // Advance to the next level
            if (lvl_ind < level_fnames.size()) { // Check if there are more levels
                display.success_message(); 
                state = Game_State::RUN;
                set_level(pop_fname());
            }
            else { // If all the levels are finished, exit the game
                stats.time_played = stop_timer(start_t);
				mario.update_score(Points::GAME_COMPLETE);
                save_statistics();
                display.winning_message();
                state = Game_State::TERMINATE;
            }
            break;
        default: // Do nothing if the state is not valid
            break;
        }
    }
	//In any case, save the statistics (even if they are already saved)
	save_statistics();
}

/**
 * @brief Resets the game to its initial fields.
 */
void Game::reset() {
	stats = {}; // Reset the statistics
	lvl_ind = 0;

	dif_lvl = Difficulty::EASY;
	state = Game_State::IDLE;

	curr_level.reset(); // Free current level
	mario.fatory_reset(); // Reset Mario to its initial feilds
}

/**
 * @brief Saves the game statistics.
 */
void Game::save_statistics() {
	stats.score = mario.get_score();
	stats.difficulty = static_cast<int>(dif_lvl);
}

/**
 * @brief Gets the game's statisitcs
 */
const Hof::Statistics& Game::get_statistics() const {
	return stats;
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
 * @brief Initializes the level.
 * @param fname The filename of the level to initialize.
 */
void Game::set_level(const std::string& fname) {

	if (state == Game_State::TERMINATE) return; // If the game is terminated, do nothing

	if (curr_level == nullptr) { // If the current level is null, use the constructor
        curr_level = std::make_unique<Level>(fname, mario, dif_lvl);
	}
	else { // If the current level is already initialized, use the move constructor
		curr_level = std::make_unique<Level>(std::move(*curr_level), fname);
    }

	// Validate the level, while invalid keep advancing to the next level
	while (display.error_message(curr_level->get_errors())) {

		lvl_ind++; // Advance to the next level

		if (lvl_ind < level_fnames.size()) { // If there are more levels, advance to the next one
			advance_level(pop_fname());
		}
		else { // If all the levels are finished, exit the game
            state = Game_State::FIN_SUC;
            break;
		}
	}
}

/**
 * @brief Validates and sets the game status.
 * @param stat The status to set.
 */
bool Game::set_state(Game_State _state) {
    switch (_state) {
    case Game_State::TERMINATE:
    case Game_State::RUN:
    case Game_State::PAUSE:
    case Game_State::LVL_RESET:
    case Game_State::FIN_FAIL:
    case Game_State::FIN_SUC:
    case Game_State::IDLE:
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
    case Difficulty::EASY:
    case Difficulty::MEDIUM:
    case Difficulty::HARD:
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
    if (0 <= ind && ind < get_nof_levels()) {
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
const std::string& Game::pop_fname(int i) const {

	static const std::string empty_str = "";

	// If the index is -1, set it to the current level index
    if (i == -1) i = lvl_ind;

	// Check if the index is out of bounds
	if (i < 0 || i >= level_fnames.size()) {
		return empty_str;
	}

	// Get the filename at the specified index
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

/**
 * @brief Sets the nickname of the player.
 * @param name The nickname to set.
 * @note The nickname is limited to 6 characters.
 */
void Game::set_nickname(const std::string& name) {
    strcpy_s(stats.player_name, sizeof(stats.player_name), name.c_str());
}

/**
 * @brief Gets the hall of fame list.
 * @return The hall of fame list.
 */
const std::list<Hof::Statistics>& Game::get_hof() const {
    return hall_of_fame.get_list();
}