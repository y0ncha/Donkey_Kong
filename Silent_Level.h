#pragma once
#include "Level_Base.h"

class Level_Base;

class Silent_Level : public Level_Base {

public:

	Silent_Level(std::string fname, Mario& mario, Difficulty dif_lvl) : Level_Base(fname, mario, dif_lvl) {}
	~Silent_Level() = default;

private:

};