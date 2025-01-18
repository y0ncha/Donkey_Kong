#include "Level.h"

/**
 * @brief Constructor for the Level class.
 * @param fname The name of the file that holds the board layout.
 * @param mario Reference to the Mario object.
 * @param dif_lvl The difficulty level of the game.
 */
Level::Level(std::string fname, Mario& mario, Difficulty dif_lvl)
    : dif_lvl(dif_lvl),
    board(fname),
    mario(mario),
    barrels(&board, dif_lvl), 
    ghosts(&board),
    legend(Board::LEGEND, board.get_pos(Board::LEGEND)),
    pauline(Board::PAULINE, board.get_pos(Board::PAULINE)),
    donkey_kong(Board::DONKEY_KONG, board.get_pos(Board::DONKEY_KONG)),
    hammer(Board::HAMMER, board.get_pos(Board::HAMMER)) {
    mario.set_board(&board);
    mario.reset();
}

/**
* @brief Move constructor for the Level class.
* @param other The other Level object to move from.
* @param fname The name of the file that holds the board layout.
*/
Level::Level(Level&& other, std::string fname) noexcept
    : dif_lvl(other.dif_lvl),
    board(fname),
    mario(other.mario),
    barrels(&board, other.dif_lvl),
    ghosts(&board),
    legend(Board::LEGEND, board.get_pos(Board::LEGEND)),
    pauline(Board::PAULINE, board.get_pos(Board::PAULINE)),
    donkey_kong(Board::DONKEY_KONG, board.get_pos(Board::DONKEY_KONG)),
    hammer(Board::HAMMER, board.get_pos(Board::HAMMER))
    {
    mario.set_board(&board);
	reset_level();
}

/**
 * @brief Move assignment operator for the Level class.
 * @param other The other Level object to move from.
 * @return A reference to this Level object.
 */
Level& Level::operator=(Level&& other) noexcept {
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
 * @brief Starts the level loop.
 */
Game_State Level::start() {

	Game_State state = Game_State::RUN; // Variable to hold the game state
	char input; // Variable to hold the user input
	Ctrl key; // Variable to hold the key input

    render_level(); // Update the game screen

    while (state == Game_State::RUN) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            input = _getch();
			key = static_cast<Ctrl>(input);

            switch (key) {
            case Ctrl::ESC:  // If the key is ESC, open the pause menu
                return Game_State::PAUSE;
                break;
            case Ctrl::HIT: // If the key is HIT, handle the hammer attack
                if (mario.is_armed())
                    perform_attack();
                break;
            default: // If any other key is pressed
                mario.update_dir(input); // Update Mario's direction based on the key input
                break;
			}
        }
        state = advance_entities(); // Advance all the entities in the game
        Sleep(DEF_DELAY); // Delay for 100 milliseconds
        frames++; // Increment the frame counter
    }
	return state;
}

/**
 * @brief Resets the level and updates Mario's lives.
 */
void Level::reset_level() {
	board.reset_hammer(); // Set the hammer on the board
    mario.reset(); // Draw Mario at its default position
    barrels.reset_all(); // Reset the barrels
	ghosts.reset_all(); // Reset the ghosts
    frames = 0;
}

/**
 * @brief Helper method to handle the hammer attack
 * @param pos The position to check for enemies.
 * @return True if an enemy was killed, false otherwise.
 */
void Level::perform_attack() {

    Coordinates pos = mario.get_dest(); // Get the next position of Mario
	Coordinates dir = mario.get_dir(); // Get the direction of Mario
    bool hud_update_needed = false;
	Point enemy = is_enemy_hit(pos, dir);

	if (enemy.icon == Board::BARREL) {
		barrels.was_hit(enemy.pos);
        hud_update_needed = mario.update_score(Points::ENEMY_HIT);// Update the score by 10 points
	}
	else if (enemy.icon == Board::GHOST) {
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
Point Level::is_enemy_hit(Coordinates pos, Coordinates dir) {

    Point enemy('\0', { -1, -1 }); // Variable to hold the enemy hit

    for (int i = 0; i < Level::ATTACK_RANGE; i++) {
		char ch = getch_console(pos);
        if (ch == Board::BARREL || ch == Board::GHOST) {
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
Game_State Level::advance_entities() {

    mario.move(); // Move Mario if he is on a floor element
    barrels.move_all(frames); // Move the barrels
	ghosts.move_all(); // Move the ghosts
    
  	Game_State state = Game_State::RUN; // Variable to hold the result state

	// If Mario is armed and remove the hammer from the board
    if (mario.is_armed()) board.remove_hammer();

	// Check if Mario was hit by a barrel or a ghost
    if (mario.is_hit() || barrels.hitted_mario() || ghosts.hitted_mario()) {
        mario.lose_lives(); // Decrease the number of lives Mario has left
        state = mario.get_lives() > 0 ? Game_State::LVL_RESET : Game_State::FIN_FAIL; // Reset the level if Mario has more lives, else finish the game
    }
	// Check if Mario has rescued Pauline
    else if (mario.has_rescued_pauline()) {
        mario.update_score(Points::PAULINE_RESCUED);
        state = Game_State::FIN_SUC; // Finish the game successfully
    }
	return state;
}

/**
 * @brief Getter for the board.
 */
const Board& Level::get_board() const {
	return board;
}

/**
* @brief Renders the HUD (Heads Up Display) with the number of lives.
*/
void Level::render_hud() const {

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
void Level::print_score() const {
    int points_x = legend.pos.x + 6, points_y = legend.pos.y + 1; // Set the x-coordinate for the points display
	gotoxy(points_x, points_y); // Move the cursor to the position where points are displayed
    mario.get_score();
    std::cout << "Score: " << mario.get_score(); // Print the points Mario has collected
}

/**
* @brief Renders the level by drawing the board, Mario, and the HUD.
*/
void Level::render_level() {
    board.print(); // Draw the game board
    mario.set(); // Draw Mario
	ghosts.set_all(); // Draw the ghosts
    render_hud(); // Update the lives display
}

/**
 * @brief Getter for the errors from the board validation.
 * @return A vector of error codes.
 */
const std::vector<Board::Err_Code>& Level::get_errors() {
	return board.validate_board();
}

