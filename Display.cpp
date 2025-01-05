#include "Display.h"

/**
* @brief Get the singleton instance of Display.
* @return The singleton instance of Display.
*/
Display& Display::get_instance(Game* pGame) {
    static Display instance;
	if (pGame) instance.game = pGame;
    return instance;
}

/**
* @brief Prints the layout to the console.
* @param layout The layout to print.
*/
void Display::print_layout(const char layout[Screen_Dim::Y][Screen_Dim::X + 1]) const {
    gotoxy(0, 0);
    for (int i = 0; i < Screen_Dim::Y - 1; i++) {
        std::cout << layout[i] << std::endl;
    }
    std::cout << layout[Screen_Dim::Y - 1];
}

/*
* @brief Prints the main menu and handles the user input.
* @return A "Game::status" to update the status if needed
*/
void Display::main_menu() const {

    print_layout(main_layout);
	int input = DEF;
	bool pending = true;

    while (pending) {
        if (_kbhit()) {

            input = _getch(); // Get the key input
    
            switch (input) {
			case Menu_Options::LEVELS:
				levels_menu();
				print_layout(main_layout);
				break;
            case Menu_Options::KEYS:
                keys_menu();
                print_layout(main_layout);
                break;
            case Menu_Options::START:
                difficulty_menu();
                game->set_state(RUN);
                pending = false;
                break;
            case Menu_Options::EXIT:
                exit_messege();
                game->set_state(TERMINATE);
				pending = false;
                break;
            default:
                break;
            }
        }
    }
}

void Display::levels_menu() const {

    print_layout(levels_layout);
    int input = DEF;
    bool pending = true;

    while (pending) {

        if (_kbhit()) {

			// Get the key input
            input = _getch();
            short ind = input - '0' - 1;

            if (game->set_level(ind)) {
                pending = false;
            }
			else if (input == ESC) {
				pending = false;
			}
        }

    }
}

/*
* @brief Prints the pause menu and handles the user input.
* @return A "Game::status" to update the status if needed
*/
void Display::pause_menu() const {

    print_layout(pause_layout);
    int input = DEF;
	bool pending = true;

    while (pending) {

        // todo add flash_message function to display
        gotoxy(28, 22);
        std::cout << "Press ESC to resume";
        Sleep(700);
        gotoxy(28, 22);
        std::cout << "                   ";
        Sleep(300);

        if (_kbhit()) {
            input = _getch(); // Get the key input

            switch (input) {
            case Menu_Options::RESUME:
				pending = false;
				game->set_state(RUN);
				break;
            case Menu_Options::KEYS:
                keys_menu();
                print_layout(pause_layout);
                break;
            case Menu_Options::EXIT:
				pending = false;
				game->set_state(TERMINATE);
				break;
            default:
                break;
            }
        }
    }
}

void Display::keys_menu() const {

    print_layout(keys_layout);
    int input = DEF;
	bool pending = true;

    while (pending) {

        gotoxy(26, 22);
        std::cout << "Press ESC to return to menu";
        Sleep(700);
        gotoxy(26, 22);
        std::cout << "                           ";
        Sleep(300);

        if (_kbhit()) pending = (_getch() != ESC);
    }
}

void Display::difficulty_menu() const {

    print_layout(difficulty_layout);
    int input = DEF;
    bool pending = true;

    while (pending) {
        if (_kbhit()) {
            input = _getch(); // Get the key input
            switch (input) {
            case EASY:
                game->set_difficulty(EASY);
                pending = false;
                break;
            case MEDIUM:
                game->set_difficulty(MEDIUM);
                pending = false;
                break;
            case HARD:
				game->set_difficulty(HARD);
                pending = false;
                break;
            case Display::RESUME:
				pending = false;
                break;
            default:
                break;
            }
        }
    }
}

void Display::exit_messege() const {
    print_layout(exit_layout);
}

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

void Display::failure_messege() const {
    print_layout(fail_layout);
}

void Display::success_messege() const {
    print_layout(success_layout);

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

// Main menu layout
char Display::main_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "================================================================================",// 0
     "                                                                                ",// 1
     "                                                                                ",// 2
     "                                                                                ",// 3
     "                                                                                ",// 4
     "                _____     ____    _   _   _  __  ______  __     __              ",// 5
  R"!(               |  __ \   / __ \  | \ | | | |/ / |  ____| \ \   / /              )!",// 6
  R"!(               | |  | | | |  | | |  \| | | ' /  | |__     \ \_/ /               )!",// 7
  R"!(               | |  | | | |  | | | . ` | |  <   |  __|     \   /                )!",// 8
  R"!(               | |__| | | |__| | | |\  | | . \  | |____     | |                 )!",// 9
  R"!(               |_____/   \____/  |_| \_| |_|\_\ |______|    |_|                 )!",// 10
     "                         _  __   ____    _   _   _____                          ",// 11
  R"!(                        | |/ /  / __ \  | \ | | / ____|                         )!",// 12
  R"!(     ."`".              | ' /  | |  | | |  \| | | |  __                         )!",// 13
  R"!( .-./ _=_ \.-.          |  <   | |  | | | . ` | | | |_ |                        )!",// 14
  R"!({  (,(oYo),) }}         | . \  | |__| | | |\  | | |__| |                        )!",// 15
  R"!({{ |   "   |} }         |_|\_\  \____/  |_| \_|  \_____|                        )!",// 16
  R"!({ { \(---)/  }}                                                                 )!",// 17
     "{{  }'-=-'{ } }              START A NEW GAME     - 1                           ",// 18
     "{ { }._:_.{  }}           (OPTIONAL) CHOOSE LEVEL - 2                           ",// 19
     "{{  } -:- { } }             INSTRUCTIONS & KEYS   - 8                           ",// 20
     "{_{ }`===`{  _}                    EXIT           - 9                           ",// 21
  R"!((((\)    (/))))                                                                 )!",// 22
     "================================================================================", // 23
     "                                                                                ", // 24
};

//Keys instructions layout
char Display::keys_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "================================================================================",// 0
  R"!(//****************************************************************************\\)!",// 1
     " *               Donkey Kong has kidnapped our beloved Pauline!               * ",// 2
     " *                       We must hurry to rescue her!!!                       * ",// 3
     " *                  Dodge the barrels in your way by JUMPING                  * ",// 4
     " *                  and use the ladders to climb to the top.                  * ",// 5
  R"!( *                           You'd better move fast!                          * )!",// 6
     " *              Every second counts when dealing with an ape like             * ",// 7
     " *                                DONKEY KONG!                                * ",// 8
  R"!( \\**************************************************************************// )!",// 9
     "                          _                                                     ",// 10
     "                         | | __   ___   _   _   ___   _                         ",// 11
  R"!(                         | |/ /  / _ \ | | | | / __| (_)                        )!",// 12
  R"!(                         |   <  |  __/ | |_| | \__ \  _                         )!",// 13
  R"!(                         |_|\_\  \___|  \__, | |___/ (_)                        )!",// 14
     "                                        |___/                                   ",// 15
     "                                 LEFT   -   A                                   ",// 16
     "                                 RIGHT  -   D                                   ",// 17
     "                                 JUMP   -   W                                   ",// 18
     "                                 DOWN   -   X                                   ",// 19
     "                                 STAY   -   S                                   ",// 20
     "--------------------------------------------------------------------------------",// 21
     "                                                                                ",// 22
     "================================================================================",// 23
     "                                                                                ", // 24

};

// Difficulty selection layout
char Display::difficulty_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "                       ____ _                                                   ",// 0
     "                      / ___| |__   ___   ___  ___  ___                          ",//1
  R"!(                     | |   | '_ \ / _ \ / _ \/ __|/ _ \                         )!",//2
  R"!(                     | |___| | | | (_) | (_) \__ \  __/                         )!",//3
  R"!(                      \____|_| |_|\___/ \___/|___/\___|                         )!",//4
     "                   ____  _  __  __ _            _ _                             ",// 5
  R"!(                  |  _ \(_)/ _|/ _(_) ___ _   _| | |_ _   _                     )!",// 6
     "                  | | | | | |_| |_| |/ __| | | | | __| | | |                    ",// 7
     "                  | |_| | |  _|  _| | (__| |_| | | |_| |_| |                    ",// 8
  R"!(                  |____/|_|_| |_| |_|\___|\__,_|_|\__|\__, |                    )!",// 9
     "                                                       |___/                    ",// 10
     "                               MONKEY     -    1                                ",// 11
     "                                APE       -    2                                ",// 12
     "                            DONKEY KONG   -    3                                ",// 13
     "                                                                                ",// 14
     "                                                                                ",// 15
     "                                                                                ",// 16
     "********************************************************************************",// 17
     "| WARNING: THIS GAME TAKES NO RESPONSIBILITY FOR YOUR MENTAL HEALTH IF YOU DARE|",// 18
  R"!(|                          TO SELECT 'DOUNKEY KONG'.                           |)!",// 19
     "|                                 GOOD LUCK !                                  |",// 20
     "********************************************************************************",// 21
     "                                                                                ",// 22
     "                                                                                ", // 23
     "                                                                                ", // 24

};

// Pause menu layout
char Display::pause_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
  R"!(                      _____              __  __   ______                        )!",//0
  R"!(                     / ____|     /\     |  \/  | |  ____|                       )!",//1
  R"!(                    | |  __     /  \    | \  / | | |__                          )!",//2
  R"!(                    | | |_ |   / /\ \   | |\/| | |  __|                         )!",//3
  R"!(                    | |__| |  / ____ \  | |  | | | |____                        )!",//4
  R"!(                     \_____/ /_/    \_\ |_|  |_| |______|                       )!",//5
  R"!(            _____               _    _    _____   ______   _____                )!",//6
  R"!(           |  __ \      /\     | |  | |  / ____| |  ____| |  __ \               )!",//7
  R"!(           | |__) |    /  \    | |  | | | (___   | |__    | |  | |              )!",//8
  R"!(           | ____/    / /\ \   | |  | |  \___ \  |  __|   | |  | |              )!",//9
  R"!(           | |       / ____ \  | |__| |  ____) | | |____  | |__| |              )!",//10
  R"!(           |_|      /_/    \_\  \____/  |_____/  |______| |_____/               )!",//11
     "                                                                                ",//12
     "                                                                                ",//13
     "                                                                                ",//14
     "                                                                                ",//15
     "********************************************************************************",//16
     "                                RESUME GAME     - ESC                           ",//17
     "                            INSTRUCTIONS & KEYS - 8                             ",//18
     "                                   EXIT         - 9                             ",//19
     "********************************************************************************",//20
     "                                                                                ",//21
     "                                                                                ",//22
     "                                                                                ", //23
     "                                                                                ", //24
};

// Exit messege layout
char Display::exit_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
  R"!(                          ############################                          )!",//0
  R"!(                          #                      _   #               / \ ____   )!",//1
     "                          #   __ _  ___  ___  __| |  #               <> ( oo )  ",//2
  R"!(                          #  / _` |/ _ \/ _ \/ _` |  #               <>_| ^^ |_)!",//3
  R"!(                          #  \__, |\___/\___/\__,_|  #               <>   @    \)!",//4
  R"!(                          #  |___/                   #              /~~\ . . _ |)!",//5
  R"!(                          #     _                    #             /~~~~\    | |)!",//6
  R"!(                          #    | |__  _  _  ___      #            /~~~~~~\/ _| |)!",//7
  R"!(                          #    | '_ \| || |/ -_)     #            |[][][]/ / [m])!",//8
  R"!(                          #    |_.__/ \_, |\___|     #            |[][][[m]     )!",//9
     "                          #           |__/           #            |[][][]|      ",//10
     "                          ############################            |[][][]|      ",//11
     "                                                                  |[][][]|      ",//12
     "                                                                  |[][][]|      ",//13
     "****************************************************************  |[][][]|      ",//14
     "                                ______  _                         |[][][]|      ",//15
  R"!(                               |  __  \| \    /\                  |[][][]|      )!",//16
  R"!(                               | (  \  |  \  / /                  |[][][]|      )!",//17
  R"!(                               | |   ) |  (_/ /                   |[|--|]|      )!",//18
  R"!(                               | |   | |   _ (                    |[|  |]|      )!",//19
  R"!(                               | |   ) |  ( \ \                   ========      )!",//20
  R"!(                               | (__/  |  /  \ \                 ==========     )!",//21
  R"!(                               |______/|_/    \/                 | [[  ]] |     )!",//22
     "                                                                 ==========     ",//23
     "********************************************************************************",//24
};

// Try again messege layout
char Display::strike_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
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
     "                                                                                ",//24

};

// Fail messege layout
char Display::fail_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
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
  R"!(          \ \ / /___   _   _  |  ___|/ \   |_ _|| |    | ____||  _ \            )!", // 10
  R"!(           \ V // _ \ | | | | | |_  / _ \   | | | |    |  _|  | | | |           )!", // 11
  R"!(            | || (_) || |_| | |  _|/ ___ \  | | | |___ | |___ | |_| |           )!", // 12
  R"!(            |_| \___/  \__,_| |_| /_/   \_\|___||_____||_____||____/            )!", // 13
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
     "                                                                                ", // 24
};

// Success messege layout
char Display::success_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
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
"                                                                                ", // 0
"                    CONGRATULATIONS, YOU HAVE SAVED PAULINE!                    ", // 22
"                                                                                ", // 23
"                                                                                ", // 24
};

// Levels selection layout
char Display::levels_layout[Screen_Dim::Y][Screen_Dim::X + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "            _                                    _                       _      ", // 0
     "      ___  | |__    ___    ___    ___   ___     | |  ___  __   __  ___  | |     ", // 1
  R"!(     / __| | '_ \  / _ \  / _ \  / __| / _ \    | | / _ \ \ \ / / / _ \ | |     )!", // 2
  R"!(     | (__ | | | || (_) || (_) | \__ \ | __/    | | | __/  \ V /  | __/ | |     )!", // 3
  R"!(     \___| |_| |_| \___/  \___/  |___/ \___|    |_| \___|   \_/   \___| |_|     )!", // 4
     "                                                                                ", // 5
     "                                                                                ", // 6
     "                                                                                ", // 7
     "                       ________________________________                         ", // 8
     "                      |                                |                        ", // 9
     "                      |          LEVEL I   - 1         |                        ", // 10
     "                      |          LEVEL II  - 2         |                        ", // 11
     "                      |         LEVEL III  - 3         |                        ", // 12
     "                      |________________________________|                        ", // 13
     "                                                                                ", // 14
     "                                                                                ", // 15
     "                                                                                ", // 16
     "                                                                                ", // 17
     "********************************************************************************", // 18
  R"!(|                        CHOOSE WHAT LEVEL TO START WITH.                      |)!", // 19
     "|            AFTER YOU CHOSE THE WANTED LEVEL START THE GAME FROM MAIN         |", // 20
     "********************************************************************************", // 21
     "                                                                                ", // 22
     "                                                                                ", // 23
     "                                                                                ", // 24
};
