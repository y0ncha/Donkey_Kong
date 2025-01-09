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
    hammer(Board::HAMMER, board.get_pos(Board::HAMMER)) {
    mario.set_board(&board);
    mario.reset();
	barrels.reset_all();
	ghosts.reset_all();
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

    Game_State state = Game_State::RUN; // Set the game status to RUN
    char key;

    render_level(); // Update the game screen

    while (state == Game_State::RUN) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            key = _getch();

			if (key == Ctrl::ESC) { // If the key is ESC, open the pause menu
                return Game_State::PAUSE;
			}
			else {
				mario.update_dir(key); // Update Mario's direction based on the key input
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
    mario.reset(); // Draw Mario at its default position
    barrels.reset_all(); // Reset the barrels
	ghosts.reset_all(); // Reset the ghosts
    frames = 0;
}

/**
 * @brief Advances the entities in the game.
 */
Game_State Level::advance_entities() {

    mario.move(); // Move Mario if he is on a floor element
    barrels.move_all(frames); // Move the barrels
	ghosts.move_all(); // Move the ghosts
	Game_State state = Game_State::RUN; // Check the game state

	if (mario.is_hit() || barrels.hitted_mario() || ghosts.hitted_mario()) { // Check if Mario was hit by a barrel or a ghost
		mario.lose_lives(); // Decrease the number of lives Mario has left
        state = mario.get_lives() > 0 ? Game_State::LVL_RESET : Game_State::FIN_FAIL; // Reset the level if Mario has more lives, else finish the game
    } 
    else if (mario.is_rescued_pauline()) { // Check if Mario saved Pauline
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
    gotoxy(Board::HRTS_DISP_X, Board::HRTS_DISP_Y); // Move the cursor to the position where lives are displayed
	int n = mario.get_lives(); // Get the number of lives Mario has left
    // Print the lives in the legend
    for (int i = 0; i < n; ++i) {
        std::cout << "<3 ";
    }
}

/**
* @brief Renders the level by drawing the board, Mario, and the HUD.
*/
void Level::render_level() const {
    board.print(); // Draw the game board
    mario.set(); // Draw Mario
	ghosts.set_all(); // Draw the ghosts
    render_hud(); // Update the lives display
}


