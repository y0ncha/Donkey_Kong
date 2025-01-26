#pragma once
#include "Game_Base.h"
#include "Level_Base.h"
#include "Regular_Level.h"
#include "Save_Level.h"

class Play_Game : public Game_Base {

public:
	Play_Game(Game_Mode mode) : Game_Base(mode) {}
	~Play_Game() = default;

private:

	// Method to set the level
	bool load_level(const std::string& screen) override;
};