#pragma once
#include <stdexcept>
#include <iostream>
#include "Config.h"
#include "Game_Base.h"
#include "Play_Game.h"
#include "Replay_Game.h"

// Forward declaration
class Level;
class Display;
class Hof;

/**
 * @class Game
 * @brief Simple interface for the game.
 */
class Game {

public:

	// Constructor for the Game class
	Game(Game_Mode mode) noexcept ;

	// Destructor for the Game class
	~Game();

	// Delete Copy functionalities (allowing only move functionalities)
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	// Move functionallites
	Game(Game&& other) noexcept;
	Game& operator=(Game&& other) noexcept;

	// Operator to access the game pointer
	//Game_Base* operator->() const { return pGame; }

	// Method to get the game Game_Mode
	Game_Mode get_mode() const { return mode; }

	// Method to run the game
	void run() { if (pGame) pGame->run(); }

private:

	// Game pointer 
	Game_Base* pGame;

	// Game Game_Mode
	Game_Mode mode;

	// Method to set the game Game_Mode
	void configure_game();
};