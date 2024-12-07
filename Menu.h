#pragma once
#include <iostream>
#include <conio.h>
#include "Utils.h"

/**
 * @class Menu
 * Handles the display and interaction of the game's menus.
 * This class is responsible for:
 * - Displaying the main menu when the program starts.
 * - Showing the keys and controls to the user.
 * - Managing the option to exit the game gracefully.
 *
 * The Menu class is utilized at two key points:
 * - When the program initially starts.
 * - When the game is paused by the player.
 * 
 * the "DONKEY KONG" big letters made with chatGPT
 * the "KEYS" big letters made with : https://www.asciiart.eu/text-to-ascii-art 
 * the ape from : https://github.com/devtooligan/awesome-ascii-art/blob/main/monkeys.txt
 */

class Menu {
	void print(MENU_TYPES type) const;//Print the menu
	void ShowKeys(MENU_TYPES type) const;//Print the keys instructions

	//Menu layout
	char MenuLayout[MAX_Y][MAX_X + 1] = {
   //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    "================================================================================",// 0
	"                                                                                ",// 1
	"                                                                                ",// 2
	"                                                                                ",// 3
	"                                                                                ",// 4
	"                _____     ____    _   _   _  __  ______  __     __              ",// 5
	"               |  __ \\   / __ \\  | \\ | | | |/ / |  ____| \\ \\   / /              ",// 6
	"               | |  | | | |  | | |  \\| | | ' /  | |__     \\ \\_/ /               ",// 7
	"               | |  | | | |  | | | . ` | |  <   |  __|     \\   /                ",// 8
	"               | |__| | | |__| | | |\\  | | . \\  | |____     | |                 ",// 9
	"               |_____/   \\____/  |_| \\_| |_|\\_\\ |______|    |_|                 ",// 10
	"                         _  __   ____    _   _   _____                          ",// 11
	"                        | |/ /  / __ \\  | \\ | | / ____|                         ",// 12
	"     .\"`\".              | ' /  | |  | | |  \\| | | |  __                         ",// 13
	" .-./ _=_ \\.-.          |  <   | |  | | | . ` | | | |_ |                        ",// 14
	"{  (,(oYo),) }}         | . \\  | |__| | | |\\  | | |__| |                        ",// 15
	"{{ |   \"   |} }         |_|\\_\\  \\____/  |_| \\_|  \\_____|                        ",// 16
	"{ { \\(---)/  }}                                                                ",// 17
	"{{  }'-=-'{ } }                                                                ",// 18
	"{ { }._:_.{  }}              START A NEW GAME   - 1                            ",// 19
	"{{  } -:- { } }             INSTRUCTIONS & KEYS - 8                            ",// 20
	"{_{ }`===`{  _}                    EXIT         - 9                             ",// 21
	"((((\)     (/))))                                                               ",// 22
	"================================================================================" // 23
	};

	//Keys instructions layout
	char KeysLayout[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "================================================================================",// 0
		 "//****************************************************************************\\\\",// 1
		 " *               Donkey Kong has kidnapped our beloved Pauline!               * ",// 2
		 " *                       We must hurry to rescue her!!!                       * ",// 3
		 " *                  Dodge the barrels in your way by jumping                  * ",// 4
		 " *                  and use the ladders to climb to the top.                  * ",// 5
		 " *                           You’d better move fast!                        * ",// 6
		 " *                Every second counts when dealing with an ape like           * ",// 7
		 " *                                  DONKEY KONG!                              * ",// 8
		 " \\\\**************************************************************************//",// 9
		 "                          _                                                     ",// 10
		 "                         | | __   ___   _   _   ___   _                         ",// 11
		 "                         | |/ /  / _ \\ | | | | / __| (_)                        ",// 12
		 "                         |   <  |  __/ | |_| | \\__ \\  _                         ",// 13
		 "                         |_|\\_\\  \\___|  \\__, | |___/ (_)                        ",// 14
		 "                                        |___/                                   ",// 15
		 "                                 LEFT   -   A                                   ",// 16
		 "                                 RIGHT  -   D                                   ",// 17
		 "                                 JUMP   -   W                                   ",// 18
		 "                                 DOWN   -   X                                   ",// 19
		 "                                 STAY   -   S                                   ",// 20
		 "--------------------------------------------------------------------------------",// 21
		 "                                                                                ",// 22
		 "================================================================================" // 23
	};

public:
	Menu();//Constructor #####not sure if we need one######
	int run(MENU_TYPES type) const;//Run the menu
};