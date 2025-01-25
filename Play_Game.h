#pragma once
#include "Game_Base.h"

class Play_Game : public Game_Base {

public:
	Play_Game(Game_Mode mode) : Game_Base(mode) {}
	~Play_Game() = default;

private:
	void pure() override {} // todo delete
};