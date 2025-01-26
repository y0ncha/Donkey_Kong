#pragma once
#include "Level_Base.h"

class Level_Base;

class Silent_Level : public Level_Base {

public:

	Silent_Level(std::string fname, Mario& mario) : Level_Base(fname, mario) {}
	~Silent_Level() = default;

private:

};