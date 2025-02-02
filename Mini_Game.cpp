#include "Mini_Game.h"



Mini_Game::Mini_Game() : layout_column(0), state(Game_State::RUN), mario(nullptr) {



}

void Mini_Game::run() {

	while (!mario.is_hit()) {

		if (_kbhit()) {
			char key = _getch();
			mario.update_dir(key);
		}
		mario.move();
	}
	
}


bool Mini_Game::load_board() {

	std::ifstream fboard("Mini_Game.txt", std::ios::in);
	if (!fboard.is_open()) return false;


    for (int i = 0; i < MINIGAME_WIDTH; i++) {
    fboard.getline(board_layout[i], SCREEN_WIDTH + 1);
    }

	return true;
}


void Mini_Game::load_screen() {

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			curr_screen[i][j] = getch_console({ i , j });
		}
	}

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {

			if (j == 0) {
				next_screen[i][j] = board_layout[i][layout_column];
			}
			else {
				next_screen[i][j] = curr_screen[i][j];
			}
		}
	}
	layout_column++;
}

void Mini_Game::render_screen() {

	clear_screen();

	for (int i = 0; i < SCREEN_HEIGHT; i++) {
		for (int j = 0; j < SCREEN_WIDTH; j++) {
			gotoxy(i, j);
			std::cout << next_screen[i][j];
		}
	}
}

/**/
void Mini_Game::init_layout() {

	// Initialize the board_layout to spaces
	for (int i = 0; i < SCREEN_HEIGHT; ++i) {
		for (int j = 0; j < MINIGAME_WIDTH - 1; ++j) {
			board_layout[i][j] = ' ';
		}
		board_layout[i][MINIGAME_WIDTH - 1] = '\0'; // Null-terminate each row
	}
}



