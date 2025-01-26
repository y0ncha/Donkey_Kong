#pragma once
#include "Game_Base.h"
#include "Level_Base.h"
#include "Regular_Level.h"
#include "Save_Level.h"

class Play_Game : public Game_Base {

public:

	// Constructor for the Play_Game class
	Play_Game(Game_Mode mode) : Game_Base(mode) {}

	// Destructor for the Play_Game class
	~Play_Game() = default;

	// Method to run the Play_Game
	void run() override;

	// Method to start the Play_Game loop
	void start() override;


private:

	// Method to set the level
	bool load_level(const std::string& screen) override;

	// Method to advance to the next level (until valid)
	bool advance_level() override;

	// Method to handle the RUN state
	void handle_run() override;

	// Method to handle the PAUSE state
	void handle_pause();

	// Method to handle the RETRY state
	void handle_retry() override;

	// Method to handle the FAIL state
	void handle_fail(std::chrono::steady_clock::time_point start_t) override;

	// Method to handle the SUCCESS state
	void handle_success(std::chrono::steady_clock::time_point start_t) override;

	// Method to handle the EXIT state
	void handle_exit(std::chrono::steady_clock::time_point start_t) override;
};