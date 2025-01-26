#pragma once
#include "Game_Base.h"

class Replay_Game : public Game_Base {

public:
	Replay_Game(Game_Mode mode) : Game_Base(mode) {}
	~Replay_Game() = default;

private:

	// Method to set the level
	bool load_level(const std::string& screen) override;
};