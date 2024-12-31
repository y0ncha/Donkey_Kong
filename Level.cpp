#include "Level.h"
#include "Display.h"
/**
 * @brief Constructor for the Level class.
 * @param fname The name of the file that holds the board layout.
 * @param mario Reference to the Mario object.
 * @param dif_lvl The difficulty level of the game.
 */
Level::Level(std::string fname, Mario& mario, Difficulty dif_lvl)
    : board(fname), mario(mario), barrels(&board, dif_lvl) {
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

    Display::render_level(mario, board); // Update the game screen

    while (state == RUN) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            key = _getch();

			if (key == ESC) { // If the key is ESC, open the pause menu
                state = PAUSE;
                break;
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
    barrels.reset(); // Reset the barrels
    frames = 0;
}

/**
 * @brief Advances the entities in the game.
 */
Game_State Level::advance_entities() {

    mario.move(); // Move Mario if he is on a floor element
    barrels.move(frames); // Move the barrels
	Game_State state = RUN; // Check the game state

    if (mario.is_hit() || barrels.hitted_mario()) { // Check if Mario was hit by a barrel
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
