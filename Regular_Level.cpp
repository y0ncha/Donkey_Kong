#include "Regular_Level.h"


/**
 * @brief Constructor for the Regular_Level class.
 * @param fname The name of the file that holds the board layout.
 * @param mario Reference to the Mario object.
 * @param dif_lvl The difficulty level of the game.
 */
Regular_Level::Regular_Level(std::string fname, Mario& mario, Difficulty _diff) :
    Level_Base(fname, mario) {
	diff = _diff;
}
/**
 * @brief Starts the level loop and saves the relevant data.
 * @param seed The seed for the random number generator.
 * @return The game state.
 */
Game_State Regular_Level::start() {

    Game_State state = Game_State::RUN; // Variable to hold the game state
    char input; // Variable to hold the user input
    Ctrl key; // Variable to hold the key input

    render_level(); // Update the game screen

    while (state == Game_State::RUN) { // Main game loop

        if (_kbhit()) { // Check if a key is pressed
            input = _getch();
            key = static_cast<Ctrl>(input);

            if (key == Ctrl::ESC) { // If the key is ESC, open the pause menu
                return Game_State::PAUSE;
            }
            else if (key == Ctrl::HIT && mario.is_armed()) { // If the key is HIT, handle the hammer attack
                perform_attack();
            }
            else {
                mario.update_dir(input); // If any other key is pressed
            }
        }
        state = advance_entities(); // Advance all the entities in the game
        Sleep(DEF_DELAY); // Delay for 100 milliseconds
        frames++; // Increment the frame counter
    }
    return state;
}