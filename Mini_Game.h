#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>
#include "Mario.h"

/**
 * @class Mini_Game
 * Represents the mini game.
 */
class Mini_Game {

public: 

	Mini_Game();
	void run();

	static constexpr int MINIGAME_WIDTH = 160;

private: 

	int layout_column = 0;
	Game_State state;
	Mario mario;

	char board_layout[SCREEN_HEIGHT][MINIGAME_WIDTH + 1];
	char curr_screen[SCREEN_HEIGHT][SCREEN_WIDTH + 1];
	char next_screen[SCREEN_HEIGHT][SCREEN_WIDTH + 1];

	void load_screen();
	bool load_board();
	void render_screen();
	void init_layout();
};
