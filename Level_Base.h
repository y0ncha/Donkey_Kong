#pragma once
#include "Config.h"
#include "Mario.h"
#include "Board.h"
#include "Barrels.h"
#include "Display.h"
#include "Ghosts.h"


/**
 * @class Level_Base
 * Represents the base class for the game levels.
 */
class Level_Base {

public:

    virtual void pure() = 0; // todo delete

    // Constructor for the Level_Base class
    Level_Base(std::string screen, Mario& mario, Difficulty dif_lvl);

    // Destructor for the Level_Base class
    virtual ~Level_Base() = default;

    // Move constructor
    Level_Base(Level_Base&& other, std::string screen) noexcept;

    // Move assignment operator
    Level_Base& operator=(Level_Base&& other) noexcept;

    // Do not allow copy constructor and copy assignment operator
    Level_Base(const Level_Base&) = delete;
    Level_Base& operator=(const Level_Base&) = delete;

    // Starts the Level_Base loop and handles user input
    virtual Game_State start(unsigned int seed = 0);

    // Resets the Level_Base
    void reset_level();

    // Handle the hammer attack
    void perform_attack();

    // Getter for the board (const by reference)
    const Board& get_board() const;

    // Method to get the errors from the board validation
    const std::vector<Board::Err_Code>& get_errors();

    // Static consts for the game
    static constexpr int DEF_DELAY = 100; // Default delay in milliseconds
    static constexpr int KILLED_DELAY = 1000; // Delay after Mario is hit
    static constexpr int ATTACK_RANGE = 2; // Delay after Mario picks up the hammer

protected:

    // Difficulty Level_Base
    Difficulty dif_lvl;

    // Game board
    Board board;

    // Game's mario by reference, same mario will continue to the next levels
    Mario& mario;

    // Hold a set of barrels
    Barrels barrels;

    // Hold a set of ghosts
    Ghosts ghosts;

    // Entities in the game
    Point legend;
    Point pauline;
    Point donkey_kong;
    Point hammer;

	// Level's screen
	std::string screen;

    // Frame counter used to follow the Level_Base frames for barrel control (can be used for future Level_Base features)
    unsigned long int frames = 0;

    // Method to advance the entities in the game
    Game_State advance_entities();

    // Method to render the HUD
    void render_hud() const;

    // Method to render the Level_Base
    void render_level();

    // Method to print mario's gained points
    void print_score() const;

    // Method to check if an enemy is in the attack range
    Point is_enemy_hit(Coordinates pos, Coordinates dir);

	// Method to caclulate the game's state
	Game_State calc_state() const;

	// Method to push an error to the error vector
	void push_error(Board::Err_Code err);
};

