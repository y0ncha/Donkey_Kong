#include "Game_Base.h"
#include "Regular_Level.h"
#include "Visual_Level.h"
#include "Silent_Level.h"
#include "Save_Level.h"

/**
 * @brief Constructor for the Game_Base class.
 */
Game_Base::Game_Base(Game_Mode) :
	mode(mode),
    state(Game_State::IDLE),
    dif_lvl(Difficulty::EASY),
    level_ind(0),
	mario(nullptr), // Passing nullptr until the level is initialized
    display(Display::get_instance(this)), // Singleton pattern
    hall_of_fame(Hof::get_instance()), // Singleton pattern
    curr_level(nullptr),
    screens() { // Default initialization of std::list
    scan_for_screens(); // Scan for level files
}

/**
 * @brief Runs the Game_Base and saves the statistics. ( will be used to save a Game_Base in Ex.3)
 */
void Game_Base::run() {

    show_cursor(false); // Seed the random number generator
    srand(static_cast<unsigned int>(time(nullptr))); // Explicit cast to unsigned int
    
	if (!hall_of_fame.is_available()) { // Check if the hall of fame is online
		display.error_message("Hall of Fame isnt available - continue playing offline");
	}

	// Main Game_Base loop
    while (display.main_menu() != Display::Menu_Options::EXIT) {
		start();
        hall_of_fame.record_statistics(stats);
		reset();
    }
    // Display the exit message
    display.exit_message();
}

/**
 * @brief Starts the Game_Base loop and handles user input.
 * @return The Game_Base state after the Game_Base loop ends (FIN_SUC, FIN_FAIL, TERMINATE).
 */
void Game_Base::start() {

    // Dynamic allocation to ease the level incrementation and to initiate level only after all the needed data is available
	std::string screen = pop_screen();
	if (!set_level(screen)) return;

	// Start the timer
    auto start_t = start_timer();

	// Main Game_Base loop
    while (state != Game_State::TERMINATE) {
		// Main Game_Base loop mamging the different states of the Game_Base
        switch (state) {
        case Game_State::RUN: // Run the Game_Base
            state = curr_level->start();
            break;
        case Game_State::PAUSE: // Pause the Game_Base
            display.pause_menu();
            break;
        case Game_State::LVL_RESET: // Reset the level
            curr_level->reset_level();
            display.strike_message();
            state = Game_State::RUN;
            break;
        case Game_State::FIN_FAIL: // Finish the Game_Base unsuccessfully
            stats.time_played = stop_timer(start_t);
			save_statistics();
            display.failure_message();
            state = Game_State::TERMINATE;
            break;
        case Game_State::FIN_SUC: // Finish the Game_Base successfully
            if (++level_ind < screens.size()) { // Check if there are more levels
                advance_level();
                display.success_message(); 
                state = Game_State::RUN;
                set_level(pop_screen());
            }
            else { // If all the levels are finished, exit the Game_Base
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
 * @brief Resets the Game_Base to its initial fields.
 */
void Game_Base::reset() {
	stats = {}; // Reset the statistics
	level_ind = 0;

	dif_lvl = Difficulty::EASY;
	state = Game_State::IDLE;

	curr_level.reset(); // Free current level
	mario.factory_reset(); // Reset Mario to its initial feilds
}

/**
 * @brief Saves the Game_Base statistics.
 */
void Game_Base::save_statistics() {
	stats.score = mario.get_score();
	stats.difficulty = static_cast<int>(dif_lvl);
}

/**
 * @brief Gets the Game_Base's statisitcs
 */
const Hof::Statistics& Game_Base::get_statistics() const {
	return stats;
}

/**
 * @brief Advances to the next level.
 * @param screen The filename of the next level.
 */
void Game_Base::advance_level() {
    
	std::string screen = pop_screen();
	// Check if the level is valid
	if (!set_level(screen)) {
		state = Game_State::FIN_SUC;
		return;
	}

	std::vector errors = curr_level->get_errors();
	// Validate the level, while invalid keep advancing
	while (!errors.empty()) {

		display.error_message(errors);
		level_ind++;

		if (level_ind < screens.size()) {
            if (!set_level(screen)) break;
			errors = curr_level->get_errors();
		}
		else {
			state = Game_State::FIN_SUC;
			break;
		}
	}
}

/**
 * @brief Initializes the level.
 * @param screen The filename of the level to initialize.
 */
bool Game_Base::set_level(const std::string& screen) {

	curr_level.reset(); // Free current level

	// Check if the screen is empty
    if (screen.empty()) return false;
    
	// Set the level based on the game mode
    switch (mode) {
    case Game_Mode::REGULAR:
        curr_level = std::make_unique<Regular_Level>(screen, mario, dif_lvl);
        break;
    case Game_Mode::SAVE:
        curr_level = std::make_unique<Save_Level>(screen, mario, dif_lvl);
        break;
    case Game_Mode::LOAD:
        curr_level = std::make_unique<Visual_Level>(screen, mario, dif_lvl);
        break;
    case Game_Mode::SILENT:
        curr_level = std::make_unique<Silent_Level>(screen, mario, dif_lvl);
        break;
    default:
        curr_level = nullptr;
        break;
    }
	return curr_level != nullptr;
}

/**
 * @brief Validates and sets the Game_Base status.
 * @param stat The status to set.
 */
bool Game_Base::set_state(Game_State _state) {
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
        dif_lvl = dif;
        return true;
    default:
        return false;
    }
}

/**
 * @brief Gets the Game_Base difficulty.
 */
Difficulty Game_Base::get_difficulty() const {
    return dif_lvl;
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
const std::list<std::string>& Game_Base::get_fnames() const {
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
    if (i < 0 || i >= screens.size()) return "";

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