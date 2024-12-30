#include "Game.h"

/**
* @brief Prints the layout to the console.
* @param layout The layout to print.
*/
void Game::Display::print_layout(const char layout[Screen_dim::Y][Screen_dim::X + 1]) const {
    gotoxy(0, 0);
    for (int i = 0; i < Screen_dim::Y - 1; i++) {
        std::cout << layout[i] << std::endl;
    }
    std::cout << layout[Screen_dim::Y - 1];
}

/*
* @brief Prints the main menu and handles the user input.
* @return A "Game::status" to update the status if needed
*/
void Game::Display::main_menu(Game& game) {

    print_layout(main_layout);
	bool pending = true;
    char key;

    while (pending) {
        if (_kbhit()) {
            key = _getch(); // Get the key input

            switch (key) {
            case Menu_Options::START:
                difficulty_menu(game);
                game.status = Game::RUN;
				pending = false;
                break;
			case Menu_Options::LEVELS:
				levels_menu(game);
                print_layout(main_layout);
				break;
            case Menu_Options::KEYS:
                keys_menu();
                print_layout(main_layout);
                break;
            case Menu_Options::EXIT:
                exit_messege();
                game.status = Game::EXIT;
				pending = false;
            default:
                break;
            }
        }
    }
}

void Game::Display::levels_menu(Game& game) {

    print_layout(levels_layout);
    bool pending = true;
    char key;

    while (pending) {

        if (_kbhit()) {

            key = _getch(); // Get the key input
            if (0 < key - '0' && key - '0' < NOF_LEVELS) {
                game.lvl_ind = key - '0';
                pending = false;
            }
			else if (key == ESC) {
				pending = false;
			}
        }

    }
}

/*
* @brief Prints the pause menu and handles the user input.
* @return A "Game::status" to update the status if needed
*/
void Game::Display::pause_menu(Game& game) {

    print_layout(pause_layout);
	bool pending = true;
    char key;
	Game::Status status = Game::PAUSE;

    while (pending) {

        gotoxy(28, 22);
        std::cout << "Press ESC to resume";
        Sleep(700);
        gotoxy(28, 22);
        std::cout << "                   ";
        Sleep(300);

        if (_kbhit()) {
            key = _getch(); // Get the key input

            switch (key) {
            case Menu_Options::RESUME:
				pending = false;
				game.status = Game::RUN;
				break;
            case Menu_Options::KEYS:
                keys_menu();
                print_layout(pause_layout);
                break;
            case Menu_Options::EXIT:
				pending = false;
				game.status = Game::EXIT;
				break;
            default:
                break;
            }
        }
    }
}

void Game::Display::keys_menu() const {
    print_layout(keys_layout);
	bool pending = true;
    char key;

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

void Game::Display::difficulty_menu(Game& game) {
    print_layout(difficulty_layout);
    bool pending = true;
    char key;

    while (pending) {
        if (_kbhit()) {
            key = _getch(); // Get the key input
            switch (key) {
            case EASY:
                game.dif_lvl = EASY;
                pending = false;
                break;
            case MEDIUM:
                game.dif_lvl = MEDIUM;
                pending = false;
                break;
            case HARD:
				game.dif_lvl = HARD;
                pending = false;
                break;
			case ESC:
				pending = false;
            default:
                break;
            }
        }
    }
}

void Game::Display::exit_messege() const {
    print_layout(exit_layout);
}

void Game::Display::strike_messege() const {
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

void Game::Display::failure_messege() const {
    print_layout(fail_layout);
}

void Game::Display::success_messege() const {
    print_layout(success_layout);
}

void Game::Display::render_hud(const Mario& mario) const {
    int n = mario.get_lives(); // Get the number of lives Mario has left
    gotoxy(Board::HRTS_DISP_X, Board::HRTS_DISP_Y); // Move the cursor to the position where lives are displayed

    // Print the lives
    for (int i = 0; i < n; ++i) {
        std::cout << "<3 ";
    }
}

void Game::Display::render_level(const Mario& mario, const Board& board) const {
    board.print(); // Draw the game board
    mario.set(); // Draw Mario
    render_hud(mario); // Update the lives display
}

// Main menu layout
char Game::Display::main_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
     "{{  }'-=-'{ } }              START A NEW GAME   - 1                             ",// 18
     "{ { }._:_.{  }}                 CHOOSE LEVEL    - 2                             ",// 19
     "{{  } -:- { } }             INSTRUCTIONS & KEYS - 8                             ",// 20
     "{_{ }`===`{  _}                    EXIT         - 9                             ",// 21
  R"!((((\)    (/))))                                                                 )!",// 22
     "================================================================================", // 23
     "                                                                                ", // 24
};

//Keys instructions layout
char Game::Display::keys_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
char Game::Display::difficulty_layout[Screen_dim::Y][Screen_dim::X + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "            _                                    _                       _      ",// 0
     "      ___  | |__    ___    ___    ___   ___     | |  ___  __   __  ___  | |     ",//1
  R"!(     / __| | '_ \  / _ \  / _ \  / __| / _ \    | | / _ \ \ \ / / / _ \ | |     )!",//2
  R"!(     | (__ | | | || (_) || (_) | \__ \ | __/    | | | __/  \ V /  | __/ | |     )!",//3
  R"!(     \___| |_| |_| \___/  \___/  |___/ \___|    |_| \___|   \_/   \___| |_|     )!",//4
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
  R"!(|                          TO SELECT 'DOUNKEY KONG'.                           |)!",// 19
     "|                                 GOOD LUCK !                                  |",// 20
     "********************************************************************************",// 21
     "                                                                                ",// 22
     "                                                                                ", // 23
     "                                                                                ", // 24

};

// Pause menu layout
char Game::Display::pause_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
char Game::Display::exit_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
char Game::Display::strike_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
char Game::Display::fail_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
char Game::Display::success_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
"                                                                                ", // 24
};

// Levels selection layout
char Game::Display::levels_layout[Screen_dim::Y][Screen_dim::X + 1] = {
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
     "                      |          LEVEL I (1)           |                        ", // 10
     "                      |          LEVEL II (2)          |                        ", // 11
     "                      |         LEVEL III (3)          |                        ", // 12
     "                      |________________________________|                        ", // 13
     "                                                                                ", // 14
     "                                                                                ", // 15
     "                                                                                ", // 16
     "                                                                                ", // 17
     "********************************************************************************", // 18
  R"!(|                         CHOOSE WHAT LEVEL TO START WITH.                     |)!", // 19
     "|                                  GOOD LUCK !                                 |", // 20
     "********************************************************************************", // 21
     "                                                                                ", // 22
     "                                                                                ", // 23
     "                                                                                ", // 24
};
