#include "Display.h"

/**
* @brief Prints the layout to the console.
* @param layout The layout to print.
*/
void Display::print_layout(const char layout[Screen_dim::Y][Screen_dim::X + 1]) const{
	gotoxy(0, 0);
	for (int i = 0; i < Screen_dim::Y - 1; i++) {
		std::cout << layout[i] << std::endl;
	}
	std::cout << layout[Screen_dim::Y - 1];
}
/**
 * @brief Prints the menu or pause menu based on the type.
 * @param type The type of menu to print (START_MENU or PAUSE_MENU).
 */
void Display::print(Menu_types type) const {

    if (type == START_MENU) {
		print_layout(main_layout);
    } else { // PAUSE_MENU
		print_layout(pause_layout);
    }
}

/**
 * @brief Prints the keys layout and waits for the ESC key to return to the menu.
 * @param type The type of menu to return to after displaying the keys.
 */
void Display::keys_menu(Menu_types type) const {
  
	print_layout(keys_layout);

    while (true) { // Wait for ESC
        if (_kbhit()) { // Check if a key is pressed
            char key = _getch(); // Get the key input
            if (key == ESC) {
                this->print(type);
                break;
            }
        }
        gotoxy(26, 22);
        std::cout << "Press ESC to return to menu";
        Sleep(700);
        if (_kbhit()) { // Check if a key is pressed (again to make it run faster between two "sleep")
            char key = _getch(); // Get the key input
            if (key == ESC) {
                this->print(type);
                break;
            }
        }
        gotoxy(26, 22);
        std::cout << "                           ";
        Sleep(300);
    }
}

/**
 * @brief Runs the specified menu and handles user input.
 * @param type The type of menu to run (START_MENU or PAUSE_MENU).
 * @return The selected menu option (START, KEYS, or EXIT).
 */
int Display::run(Menu_types type) const {
    this->print(type);

    while (true) {
        if (_kbhit()) { // Check if a key is pressed
            char key = _getch(); // Get the key input
            if (key == START || key == EXIT)
                return key; // Return the key value (START or EXIT)
            else if (key == KEYS)
                this->keys_menu(type);
        }
    }
}

/**
 * @brief Allows the user to choose the game level.
 * @return The selected level (EASY, MEDIUM, or HARD).
 */
int Display::levels_menu() const{
    
	print_layout(levels_layout);

    while (true) { // Wait for level selection
        if (_kbhit()) { // Check if a key is pressed
            char key = _getch(); // Get the key input
            switch (key) {
            case EASY:
                return EASY;
            case MEDIUM:
                return MEDIUM;
            case HARD:
                return HARD;
            }
        }
    }
}

/**
 * @brief Prints the exit layout.
 */
void Display::exit_messege() const {
	print_layout(exit_layout);
}

/**
 * @brief Prints the try again layout and waits for a key press to continue.
 */
void Display::strike_messege() const {
	print_layout(strike_layout);

	while (true) {
		if (_kbhit())  // Check if a key is pressed
			break;

		gotoxy(27, 23);
		std::cout << "Press any key to continue";

		Sleep(700);
		if (_kbhit()) { // Check if a key is pressed (again to make it run faster between two "sleep")
			break;
		}
		gotoxy(27, 23);
		std::cout << "                         ";
		Sleep(300);

	}
}

/**
 * @brief Prints the failure layout.
 */
void Display::failure_messege() const {
	print_layout(fail_layout);
}

/**
 * @brief Prints the success layout.
 */
void Display::success_messege() const {
	print_layout(success_layout);
}

//Main menu layout
char Display::main_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
	 "{ { }._:_.{  }}              START A NEW GAME   - 1                             ",// 19
	 "{{  } -:- { } }             INSTRUCTIONS & KEYS - 8                             ",// 20
	 "{_{ }`===`{  _}                    EXIT         - 9                             ",// 21
	 "((((\\)   (/))))                                                                 ",// 22
	 "================================================================================", // 23
};

//Keys instructions layout
char Display::keys_layout[Screen_dim::Y][Screen_dim::X + 1] = {
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	 "================================================================================",// 0
	 "//****************************************************************************\\\\",// 1
	 " *               Donkey Kong has kidnapped our beloved Pauline!               * ",// 2
	 " *                       We must hurry to rescue her!!!                       * ",// 3
	 " *                  Dodge the barrels in your way by JUMPING                  * ",// 4
	 " *                  and use the ladders to climb to the top.                  * ",// 5
	 " *                           You\'d better move fast!                          * ",// 6
	 " *              Every second counts when dealing with an ape like             * ",// 7
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
	 "================================================================================",// 23

};

// Level selection layout
char Display::levels_layout[Screen_dim::Y][Screen_dim::X + 1] = {
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	 "            _                                    _                       _      ",// 0
	 "      ___  | |__    ___    ___    ___   ___     | |  ___  __   __  ___  | |     ",//1
	 "     / __| | '_ \\  / _ \\  / _ \\  / __| / _ \\    | | / _ \\ \\ \\ / / / _ \\ | |     ",//2
	 "     | (__ | | | || (_) || (_) | \\__ \\ | __/    | | | __/  \\ V /  | __/ | |     ",//3
	 "     \\___| |_| |_| \\___/  \\___/  |___/ \\___|    |_| \\___|   \\_/   \\___| |_|     ",//4
	 "                                                                                ",// 5
	 "                                                                                ",// 6
	 "                                                                                ",// 7
	 "                       ________________________________                         ",// 8
	 "                      |                                |                        ",// 9
	 "                      |         MONKEY     -    1      |                        ",// 10
	 "                      |          APE       -    2      |                        ",// 11
	 "                      |      DONKEY KONG   -    3      |                        ",// 12
	 "                      |________________________________|                        ",// 13
	 "                                                                                ",// 14
	 "                                                                                ",// 15
	 "                                                                                ",// 16
	 "********************************************************************************",// 17
	 "| WARNING: THIS GAME TAKES NO RESPONSIBILITY FOR YOUR MENTAL HEALTH IF YOU DARE|",// 18
	 "|                          TO SELECT \'DOUNKEY KONG\'.                           |",// 19
	 "|                                 GOOD LUCK !                                  |",// 20
	 "********************************************************************************",// 21
	 "                                                                                ",// 22
	 "                                                                                ", // 23

};

// Pause menu layout
char Display::pause_layout[Screen_dim::Y][Screen_dim::X + 1] = {
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	 "                      _____              __  __   ______                        ",//0
	 "                     / ____|     /\\     |  \\/  | |  ____|                       ",//1
	 "                    | |  __     /  \\    | \\  / | | |__                          ",//2
	 "                    | | |_ |   / /\\ \\   | |\\/| | |  __|                         ",//3
	 "                    | |__| |  / ____ \\  | |  | | | |____                        ",//4
	 "                     \\_____/ /_/    \\_\\ |_|  |_| |______|                       ",//5
	 "            _____               _    _    _____   ______   _____                ",//6
	 "           |  __ \\      /\\     | |  | |  / ____| |  ____| |  __ \\               ",//7
	 "           | |__) |    /  \\    | |  | | | (___   | |__    | |  | |              ",//8
	 "           | ____/    / /\\ \\   | |  | |  \\___ \\  |  __|   | |  | |              ",//9
	 "           | |       / ____ \\  | |__| |  ____) | | |____  | |__| |              ",//10
	 "           |_|      /_/    \\_\\  \\____/  |_____/  |______| |_____/               ",//11
	 "                                                                                ",//12
	 "                                                                                ",//13
	 "                                                                                ",//14
	 "                                                                                ",//15
	 "********************************************************************************",//16
	 "                                RESUME GAME     - 1                             ",//17
	 "                            INSTRUCTIONS & KEYS - 8                             ",//18
	 "                                   EXIT         - 9                             ",//19
	 "********************************************************************************",//20
	 "                                                                                ",//21
	 "                                                                                ",//22
	 "                                                                                ", //23

};

// Exit messege layout
char Display::exit_layout[Screen_dim::Y][Screen_dim::X + 1] = {
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	 "                          ############################                          ",//0
	 "                          #                      _   #                          ",//1
	 "                          #   __ _  ___  ___  __| |  #                          ",//2
	 "                          #  / _` |/ _ \\/ _ \\/ _` |  #                          ",//3
	 "                          #  \\__, |\\___/\\___/\\__,_|  #                          ",//4
	 "                          #  |___/                   #                          ",//5
	 "                          #     _                    #                          ",//6
	 "                          #    | |__  _  _  ___      #                          ",//7
	 "                          #    | '_ \\| || |/ -_)     #                          ",//8
	 "                          #    |_.__/ \\_, |\\___|     #                          ",//9
	 "                          #           |__/           #                          ",//10
	 "                          ############################                          ",//11
	 "                                                                                ",//12
	 "                                                                                ",//13
	 "********************************************************************************",//14
	 "                                ______  _                                       ",//15
	 "                               |  __  \\| \\    /\\                                ",//16
	 "                               | (  \\  |  \\  / /                                ",//17
	 "                               | |   ) |  (_/ /                                 ",//18
	 "                               | |   | |   _ (                                  ",//19
	 "                               | |   ) |  ( \\ \\                                 ",//20
	 "                               | (__/  |  /  \\ \\                                ",//21
	 "                               |______/|_/    \\/                                ",//22
	 "                                                                                ",//23
	 "********************************************************************************",//24
};

// Try again messege layout
char Display::strike_layout[Screen_dim::Y][Screen_dim::X + 1] = {
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	 "                                   :=*%@@@%*=:                                  ",//0
	 "                               =@@@@=       =@@@@+                              ",//1
	 "                            +@@@                 @@@+                           ",//2
	 "                          *@@                       @@*                         ",//3
	 "                         @@:                         .@@                        ",//4
	 "                       :@@                             @@=                      ",//5
	 "                      -@@                               @@=                     ",//6
	 "                      @@        +@@@         @@@*        @@                     ",//7
	 "                     *@+        @@@@.        @@@@        =@#                    ",//8    
	 "                     %@                                   @@                    ",//9
	 "                     @@                                   @@                    ",//10 
	 "                     @@                                   @@                    ",//11
	 "                     @@            -@@@@@@@@@-            @@                    ",//12
	 "                     *@+        .@@@+       +@@@.        =@%                    ",//13
	 "                      @@       @@#             *@@       @@                     ",//14
	 "                      =@@     #@                 @%     @@+                     ",//15
	 "                       =@@                             %@+                      ",//16
	 "                         @@:                          @@                        ",//17
	 "                         *@@                       @@#                          ",//18     
	 "                           +@@@                 %@@*                            ",//19
	 "                              *@@@@=-*%@@@%*-@@@@*                              ",//20
	 "                                                                                ",//21
	 "                                 MARIO GOT HIT!                                 ",//22
	 "                                                                                ",//23

};

// Fail messege layout
char Display::fail_layout[Screen_dim::Y][Screen_dim::X + 1] = {
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789
	 "                                                                                ", // 0
	 "                                                                                ", // 1
	 "                                                                                ", // 2
	 "                                                                                ", // 3
	 "                                                                                ", // 4
	 "                                                                                ", // 5
	 "                                                                                ", // 6
	 "                                                                                ", // 7
	 "                                                                                ", // 8
	 "          __   __              _____  _     ___  _      _____  ____             ", // 9
	 "          \\ \\ / /___   _   _  |  ___|/ \\   |_ _|| |    | ____||  _ \\            ", // 10
	 "           \\ V // _ \\ | | | | | |_  / _ \\   | | | |    |  _|  | | | |           ", // 11
	 "            | || (_) || |_| | |  _|/ ___ \\  | | | |___ | |___ | |_| |           ", // 12
	 "            |_| \\___/  \\__,_| |_| /_/   \\_\\|___||_____||_____||____/            ", // 13
	 "                                                                                ", // 14
	 "                                                                                ", // 15
	 "                                                                                ", // 16
	 "                             BETTER LUCK NEXT TIME !                            ", // 17
	 "                                                                                ", // 18
	 "                                                                                ", // 19
	 "                                                                                ", // 20
	 "                                                                                ", // 21
	 "                                                                                ", // 22
	 "                                                                                ", // 23

};

// Success messege layout
char Display::success_layout[Screen_dim::Y][Screen_dim::X + 1] = {
"                                                                                ", // 0
"                                   :=*####*=                                    ", // 1
"                                -*##*-   =*####.                                ", // 2
"                              -###*  **:*#: +####                               ", // 3
"                            :*####. #+ +  #= #####*                             ", // 4
"                           =######*:*     =-*#######.                           ", // 5
"                          *##########################                           ", // 6
"                         +########%%%%%%%%%%%%%#######                          ", // 7
"                        :####%%@@@@@#**####@@@@@%%%%%#-                         ", // 8
"                        ###%%%%@%*#@@=====@@%*#@@%%%%%*                         ", // 9
"                        ###@+--------:---==++==++**@%%*                         ", // 10
"                         #%%.... .*#*...:=%##:-====@@%:                         ", // 11
"                        ..=#.... :@@@:..:=@%%*.-===@%*=:                        ", // 12
"                       ...+%.... .++    ...++=:---+@%+*+                        ", // 13
"                       ..:*=.@=.. ..   ........:=@+#@#+=                        ", // 14
"                        ....@@@@@@........::-@@@@@@:**=                         ", // 15
"                         ...:@@@@@#...:::--=@@@@@@*--=                          ", // 16
"                           ...:+@@@@%++=+*@@@@@@++=:                            ", // 17
"                            .....-=+@@@@@@@#++====-                             ", // 18
"                              :::::::--==========                               ", // 19
"                                 .::::::---===.                                 ", // 20
"                                    .:::::.                                     ", // 21
"                                                                                ", // 22
"                    CONGRATULATIONS, YOU HAVE SAVED PAULINE!                    ", // 23
};