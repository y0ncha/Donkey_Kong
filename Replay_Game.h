#pragma once
#include "Game_Base.h"

class Replay_Game : public Game_Base {

public:
	Replay_Game(Game_Mode mode) : Game_Base(mode) {}
	~Replay_Game() = default;

private:
	void pure() override {} // todo delete
};