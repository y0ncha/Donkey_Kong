#include "Level_Base.h"

/**
 * @brief Constructor for the Level_Base class.
 * @param screen The name of the file that holds the board layout.
 * @param mario Reference to the Mario object.
 * @param dif_lvl The difficulty Level_Base of the game.
 */
Level_Base::Level_Base(std::string screen, Mario& mario) : 
	diff(Difficulty::EASY),
    seed(static_cast<unsigned int>(time(nullptr))),
    board(screen),
    mario(mario),
    barrels(&board, diff), 
    ghosts(&board),
    legend(Board::LEGEND, board.get_pos(Board::LEGEND)),
    pauline(Board::PAULINE, board.get_pos(Board::PAULINE)),
    donkey_kong(Board::DONKEY_KONG, board.get_pos(Board::DONKEY_KONG)),
    hammer(Board::HAMMER, board.get_pos(Board::HAMMER)),
    screen(screen) {
	srand(seed);
    mario.set_board(&board);
    mario.reset();
}

/**
* @brief Move constructor for the Level_Base class.
* @param other The other Level_Base object to move from.
* @param screen The name of the file that holds the board layout.
*/
Level_Base::Level_Base(Level_Base&& other, std::string screen) noexcept
    : diff(other.diff),
    board(screen),
    mario(other.mario),
    barrels(&board, other.diff),
    ghosts(&board),
    legend(Board::LEGEND, board.get_pos(Board::LEGEND)),
    pauline(Board::PAULINE, board.get_pos(Board::PAULINE)),
    donkey_kong(Board::DONKEY_KONG, board.get_pos(Board::DONKEY_KONG)),
    hammer(Board::HAMMER, board.get_pos(Board::HAMMER))
    {
    mario.set_board(&board);
	retry_level();
}

/**
 * @brief Move assignment operator for the Level_Base class.
 * @param other The other Level_Base object to move from.
 * @return A reference to this Level_Base object.
 */
Level_Base& Level_Base::operator=(Level_Base&& other) noexcept {
    if (this != &other) {
        board = std::move(other.board);
        barrels = std::move(other.barrels);
		    barrels.reset_all();
        ghosts = std::move(other.ghosts);
		    ghosts.reset_all();
		    legend = std::move(other.legend);
        pauline = std::move(other.pauline);
        donkey_kong = std::move(other.donkey_kong);
		    hammer = std::move(other.hammer);
        frames = other.frames;
        mario.set_board(&board);
		    mario.reset();
    }
    return *this;
}

/**
 * @brief Resets the Level_Base and updates Mario's lives.
 */
void Level_Base::retry_level() {
	board.reset_hammer(); // Set the hammer on the board
    mario.reset(); // Draw Mario at its default position
    barrels.reset_all(); // Reset the barrels
	ghosts.reset_all(); // Reset the ghosts
}

/**
 * @brief Helper method to handle the hammer attack
 * @param pos The position to check for enemies.
 * @return True if an enemy was killed, false otherwise.
 */
void Level_Base::perform_attack() {

    Coordinates pos = mario.get_dest(); // Get the next position of Mario
	Coordinates dir = mario.get_dir(); // Get the direction of Mario
    bool hud_update_needed = false;
	Point enemy = is_enemy_hit(pos, dir);

	if (enemy.icon == Board::BARREL) {
		barrels.was_hit(enemy.pos);
        hud_update_needed = mario.update_score(Points::ENEMY_HIT);// Update the score by 10 points
	}
	else if (enemy.icon == Board::Regular_Ghost || enemy.icon == Board::SUPER_GHOST) {
		ghosts.was_hit(enemy.pos);
        hud_update_needed = mario.update_score(Points::ENEMY_HIT); // Update the score by 10 points
	}
    hud_update_needed ? render_hud() : print_score(); // Update the HUD if a bonus was given or print the score
}

/**
* @breif Helper method to check if an enemy is in the attack range.
* @param pos The position to check.
* @param dir The direction to check.
* @return The character of the enemy hit, if non returns '\0'.
*/
Point Level_Base::is_enemy_hit(Coordinates pos, Coordinates dir) {

    Point enemy('\0', { -1, -1 }); // Variable to hold the enemy hit

    for (int i = 0; i < Level_Base::ATTACK_RANGE; i++) {
		char ch = getch_console(pos);
        if (ch == Board::BARREL || ch == Board::Regular_Ghost || ch == Board::SUPER_GHOST) {
			enemy = Point(ch, pos);
            break;
        }
		else {
			pos += dir;
		}
    }
    return enemy;
}


/**
 * @brief Advances the entities in the game.
 */
Game_State Level_Base::advance_entities() {

    mario.move(); // Move Mario if he is on a floor element
    barrels.move_all(frames); // Move the barrels
	ghosts.move_all(); // Move the ghosts

	// If Mario is armed and remove the hammer from the board
    if (mario.is_armed()) board.remove_hammer();
	return calc_state(); // Calculate the game state
}

/**
 * @brief Calculates the game state.
 * @return The game state.
 */
Game_State Level_Base::calc_state() const {
	
	Game_State state = Game_State::RUN; // Variable to hold the result state
	// Check if Mario was hit by a barrel or a Regular_Ghost
	if (mario.is_hit() || barrels.hitted_mario() || ghosts.hitted_mario()) {
		mario.lose_lives(); // Decrease the number of lives Mario has
		state = mario.get_lives() > 0 ? Game_State::RETRY : Game_State::FAIL; // Reset the Level_Base if Mario has more lives, else finish the game
	}
	// Check if Mario has rescued Pauline
	else if (mario.has_rescued_pauline()) {
		mario.update_score(Points::PAULINE_RESCUED); // Update the score by 100 points
		state = Game_State::SUCCESS; // Finish the game successfully
	}
	return state;
}

/**
 * @brief Getter for the board.
 */
const Board& Level_Base::get_board() const {
	return board;
}

/**
* @brief Renders the HUD (Heads Up Display) with the number of lives.
*/
void Level_Base::render_hud() const {

	int hearts_x = legend.pos.x + 6, hearts_y = legend.pos.y; // Set the x-coordinate for the lives display

	int n = mario.get_lives(); // Get the number of lives Mario has left

    // Print the lives in the legend
    gotoxy(hearts_x, hearts_y); // Move the cursor to the position where lives are displayed
    for (int i = 0; i < n; ++i) {
        std::cout << "<3 ";
    }
	print_score(); // Print the points Mario has collected
}

/**
* @brief Prints the points Mario has collected.
*/
void Level_Base::print_score() const {
    int points_x = legend.pos.x + 6, points_y = legend.pos.y + 1; // Set the x-coordinate for the points display
	gotoxy(points_x, points_y); // Move the cursor to the position where points are displayed
    mario.get_score();
    std::cout << "Score: " << mario.get_score(); // Print the points Mario has collected
}

/**
* @brief Renders the Level_Base by drawing the board, Mario, and the HUD.
*/
void Level_Base::render_level() {
    board.print(); // Draw the game board
    mario.set(); // Draw Mario
	ghosts.set_all(); // Draw the ghosts
    render_hud(); // Update the lives display
}

/**
 * @brief Getter for the errors from the board validation.
 * @return A vector of error codes.
 */
const std::vector<Board::Err_Code>& Level_Base::get_errors() {
	return board.get_errors();
}

/**
 * @brief Determines if an action is required in the result file.
 * @param state The game state.
 * @return True if an action is required, false otherwise.
 */
bool Level_Base::is_result_action_required(Game_State state)
{
    return (state == Game_State::SUCCESS || state == Game_State::FAIL || state==Game_State::RETRY);
}

/**
 * @brief Pushes an error to the error vector.
 * @param err The error code to push.
 */
void Level_Base::push_error(Board::Err_Code err) {
	board.push_error(err);
}

/**
 * @brief Gets the file name for the save file.
 * @param type The type of the file.
 * @return The file name.
 */
const std::string Level_Base::generate_fname(const std::string& type) {

    std::string fname = screen;

    fname = remove_ext(fname, ".screen.txt");
    fname += "." + type + ".txt";

    return fname;
}