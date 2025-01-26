#pragma once
#include <memory>
#include "Game_Base.h"
#include "Level_Base.h"

class Replay_Game : public Game_Base {

public:

	// Constructor for the Replay_Game class
	Replay_Game(Game_Mode mode) : Game_Base(mode) {};

	// Destructor for the Replay_Game class
	~Replay_Game() = default;

	// Method to run the Replay_Game
	void run() override;
	
	// Method to start the Replay_Game loop
	void start() override;

private:

	// Method to set the level
	bool load_level(const std::string& screen) override;

	// Method to advance to the next level (until valid)
	bool advance_level() override;

	// Method to handle the RUN state
	void handle_run() override;

	// Method to handle the RETRY state
	void handle_retry() override;

	// Method to handle the FAIL state
	void handle_fail(std::chrono::steady_clock::time_point start_t) override;

	// Method to handle the SUCCESS state
	void handle_success(std::chrono::steady_clock::time_point start_t) override;

	// Method to handle the EXIT state
	void handle_exit(std::chrono::steady_clock::time_point start_t) override;

	static constexpr int MSG_DELAY = 1400; // Delay for the messages
};