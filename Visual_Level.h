#pragma once
#include "Level_Base.h"

class Level_Base;

class Visual_Level : public Level_Base {

public:

	Visual_Level(std::string fname, Mario& mario, Difficulty dif_lvl) : Level_Base(fname, mario, dif_lvl) {}
	~Visual_Level() = default;

private:

	void pure() override {} // todo delete
};