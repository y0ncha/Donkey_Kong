#pragma once
#include <iostream>
#include <conio.h>
#include "Utils.h"

class Menu {
	void print(MENU_TYPES type) const;
	void ShowKeys() const;
	char MenuLayout[MAX_Y][MAX_X + 1] = {
		"================================================================================",// 0
	"                                                                                ",// 1
	"                                                                                ",// 2
	"                                                                                ",// 3
	"                                                                                ",// 4
	"      _____     ____    _   _   _  __  ______  __     __         ",// 5
	"     |  __ \\   / __ \\  | \\ | | | |/ / |  ____| \\ \\   / /               ",// 6
	"     | |  | | | |  | | |  \\| | | ' /  | |__     \\ \\_/ /                ",// 7
	"     | |  | | | |  | | | . ` | |  <   |  __|     \\   /                 ",// 8
	"     | |__| | | |__| | | |\\  | | . \\  | |____     | |                  ",// 9
	"     |_____/   \\____/  |_| \\_| |_|\\_\\ |______|    |_|                  ",// 10
	"                                                                                ",// 11
	"      _  __     ____      _  __    _   _      ____    ____                     ",// 12
	"     | |/ /    / __ \\    | |/ /   | | | |    / __ \\  |  _ \\                    ",// 13
	"     | ' /    | |  | |   | ' /    | |_| |   | |  | | | | | |                   ",// 14
	"     |  <     | |  | |   |  <     |  _  |   | |  | | | | | |                   ",// 15
	"     | . \\    | |__| |   | . \\    | | | |   | |__| | | |_| |                   ",// 16
	"     |_|\\_\\    \\____/    |_|\\_\\   |_| |_|    \\____/  |____/                    ",// 17
	"                                                                                ",// 18
	"                                                                                ",// 19
	"                                                                                ",// 20
	"                                                                                ",// 21
	"                                                                                ",// 22
	"================================================================================" // 23
	};
public:
	Menu();
	int run(MENU_TYPES type) const;
};