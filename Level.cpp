#include "Level.h"
#include "Display.h"
/**
 * @brief Constructor for the Level class.
 * @param fname The name of the file that holds the board layout.
 * @param mario Reference to the Mario object.
 * @param dif_lvl The difficulty level of the game.
 */
Level::Level(std::string fname, Mario& mario, Difficulty dif_lvl)
    : board(fname),
    mario(mario),
	ghosts(&board),
    barrels(&board, dif_lvl), 
    legend(Board::LEGEND, board.get_pos(Board::LEGEND)),
    pauline(Board::PAULINE, board.get_pos(Board::PAULINE)),
    donkey_kong(Board::DONKEY_KONG, board.get_pos(Board::DONKEY_KONG)){
    mario.set_board(&board);

}

/**
 * @brief Advances to the next level by resetting and loading the new board.
 * @param next_level_file The name of the file that holds the next board layout.
 */
void Level::advance_level(const std::string& fname) {
    
    board.load(fname); // Load the new board layout from the file
    reset_level(); // Reset the current level
}

/**
 * @brief Starts the game loop.
 */
Game_State Level::start() {

    Game_State state = RUN; // Set the game status to RUN
    char key;

    render_level(); // Update the game screen
    while (state == RUN) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            key = _getch();

			if (key == ESC) { // If the key is ESC, open the pause menu
                return PAUSE;
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

    Sleep(KILLED_DELAY); // Delay for 1 second
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
	Game_State state = RUN; // Check the game state

	if (mario.is_hit() || barrels.hitted_mario() || ghosts.hitted_mario()) { // Check if Mario was hit by a barrel or a ghost
        state = mario.get_lives() > 1 ? LVL_RESET : FIN_FAIL; // Reset the level if Mario has more lives, else finish the game
    } else if (mario.is_rescued_pauline()) { // Check if Mario saved Pauline
		state = FIN_SUC; // Finish the game successfully
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
void Level::render_hud() const{
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
void Level::render_level() const{
    board.print(); // Draw the game board
    mario.set(); // Draw Mario
	std::cout << pauline << donkey_kong; // Draw the game elements
    render_hud(); // Update the lives display
}


