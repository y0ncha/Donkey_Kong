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

    // Constructor for the Level_Base class
    Level_Base(std::string screen, Mario& mario);

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
    virtual Game_State start() = 0;

    // Resets the Level_Base
    void retry_level();

    // Handle the hammer attack
    virtual void perform_attack();

    // Getter for the board (const by reference)
    const Board& get_board() const;

    // Method to get the errors from the board validation
    const std::vector<Board::Err_Code>& get_errors();

    // Method to determine if an action is required in the result file
    bool is_result_action_required(Game_State state);

    // Method to show the result file opening faile message
    void handle_result_isnt_open(Game_Mode mode);

    // Method to set the result file opening faile message appears to true
    void set_res_message_appear() { res_message_appear = true; };

    // Method to handle the steps file opening faile message
    Game_State handle_steps_isnt_open(Game_Mode mode);

    // Static consts for the game
    static constexpr int DEF_DELAY = 100; // Default delay in milliseconds
    static constexpr int REPLAY_DELAY = 60; // Delay for the replay
    static constexpr int KILLED_DELAY = 1000; // Delay after Mario is hit
    static constexpr int ATTACK_RANGE = 2; // Delay after Mario picks up the hammer

protected:

    // Difficulty Level_Base
    Difficulty diff;

	// Randomness seed
    unsigned int seed;

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
    virtual Game_State advance_entities();

    // Method to render the HUD
    void render_hud() const;

    // Method to render the Level_Base
    virtual void render_level();

    // Method to print mario's gained points
    void print_score() const;

    // Method to check if an enemy is in the attack range
    Point is_enemy_hit(Coordinates pos, Coordinates dir);

	// Method to caclulate the game's state
	Game_State calc_state() const;

	// Method to push an error to the error vector
	void push_error(Board::Err_Code err);

	// Method to get the screen's steps and results file names
	const std::string generate_fname(const std::string& type);

    // method to check if the result file opening faile message already appeard
    bool res_message_appear = false;
};

