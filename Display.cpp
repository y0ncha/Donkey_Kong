#include "Display.h"

/**
* @brief Get the singleton instance of Display.
* @param pGame Pointer to the Game instance.
* @return The singleton instance of Display.
*/
Display& Display::get_instance(Game_Base* pGame) {
    static Display instance;
    if (pGame) instance.pGame = pGame;
    return instance;
}

/**
* @brief Prints the layout to the console.
* @param layout The layout to print.
*/
void Display::print_layout(const char layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1]) const {
    gotoxy(0, 0);
    for (int i = 0; i < SCREEN_HEIGHT - 1; i++) {
        std::cout << layout[i] << std::endl;
    }
    std::cout << layout[SCREEN_HEIGHT - 1];
}

/**
* @brief Prints the main menu and handles the user input.
*/
Display::Menu_Options Display::main_menu() const {

	print_layout(main_layout); // Print the main menu layout
	Menu_Options input = Menu_Options::DEF; // Initialize the input
    bool pending = true;

    while (pending) {
        if (_kbhit()) {
            input = static_cast<Menu_Options>(_getch()); // Get the key input
            switch (input) {
            case Menu_Options::LEVELS: // Choose the level
                if (levels_menu()) {
					prompt_nickname();
                    if (difficulty_menu()) {
                        pGame->set_state(Game_State::RUN);
                        pending = false;
                    }
                    else {
						pGame->set_index(0);
                        print_layout(main_layout);
                    }
                }
                else {
                    print_layout(main_layout);
                }
                break;
            case Menu_Options::KEYS: // Show the keys
                keys_menu();
                print_layout(main_layout);
                break;
            case Menu_Options::START: // Start the game
				prompt_nickname();
                if (difficulty_menu()) {
                    pGame->set_state(Game_State::RUN);
                    pending = false;
                }
                else {
                    print_layout(main_layout);
                }
                break;
            case Menu_Options::EXIT: // Exit the game
                exit_message();
                pGame->set_state(Game_State::TERMINATE);
                pending = false;
                break;
            case Menu_Options::HALL_OF_FAME:
				top_scores();
				print_layout(main_layout);
				break;
            default:
                break;
            }
        }
    }
	return input;
}

/**
 * @brief Prints 5 levels at a time starting from the current page index.
 * @param page_ind The index of the current page.
 * @param last_page The index of the last page.
 */
void Display::print_levels(int page_ind, int last_page) const {
    short x = 28, y = 7;
    auto it = pGame->get_fnames().begin();
	auto end_it = pGame->get_fnames().end();
    std::advance(it, page_ind * LEVELS_PER_PAGE); // Move the iterator to the start of the current page

    // Print 5 levels
    for (int i = 1; it != end_it && i <= LEVELS_PER_PAGE; ++i, ++it) {
        gotoxy(x, y);
        std::cout << remove_ext(*it);
        gotoxy(x + 20, y);
        std::cout << " - " << i;
        y += 2;
    }
    gotoxy(71, 16);
    std::cout << "Page " << page_ind << "/" << last_page;
}

/**
* @brief Prints the levels menu and handles the user input.
*/
bool Display::levels_menu() const {

    Menu_Options input = Menu_Options::DEF;
    int ind, last_page = (int)pGame->get_nof_screens() / LEVELS_PER_PAGE, page_ind = 0;
    bool pending = true;

    print_layout(levels_layout);
    print_levels(page_ind, last_page);

    while (pending) {

        flash_message({ "Press ESC to resume",  "Press Enter for next page" }, { {29, 22}, {26, 23} });

        if (_kbhit()) {
			input = static_cast<Menu_Options>(_getch()); // Get the key input by integer
			ind = page_ind * LEVELS_PER_PAGE + (static_cast<int>(input) - '0') - 1; // Calculate the index of the selected level

            switch (input) {
            case Menu_Options::RESUME:
                pending = false;
                break;
            case Menu_Options::ENTER:
                page_ind = (last_page == page_ind) ? 0 : page_ind + 1;
                print_layout(levels_layout);
                print_levels(page_ind, last_page);
                break;
            default:
				if (pGame->set_index(ind)) { // If the level index is valid, break
                    pending = false;
                    return true;
                }
                break;
            }
        }
    }
	return false;
}

/**
* @brief Prints the pause menu and handles the user input.
*/
void Display::pause_menu() const {

    print_layout(pause_layout);
    Menu_Options input = Menu_Options::DEF;
    bool pending = true;

    while (pending) {
       
        if (_kbhit()) {
            input = static_cast<Menu_Options>(_getch()); // Get the key input
            switch (input) {
            case Menu_Options::RESUME:
                pending = false;
                pGame->set_state(Game_State::RUN);
                break;
            case Menu_Options::KEYS:
                keys_menu();
                print_layout(pause_layout);
                break;
            case Menu_Options::EXIT:
                pending = false;
                pGame->set_state(Game_State::TERMINATE);
                break;
            default:
                break;
            }
        }
    }
}

/**
* @brief Prints the keys menu and handles the user input.
*/
void Display::keys_menu() const {

    print_layout(keys_layout);
    bool pending = true;

    while (pending) {
        flash_message({ "Press ESC to return to menu" }, { {26, 24} });
        if (_kbhit()) pending = (_getch() != Ctrl::ESC);
    }
}

/**
* @brief Prints the difficulty menu and handles the user input.
* @return True if a difficulty was selected, false otherwise.
*/
bool Display::difficulty_menu() const {

    std::cout.flush(); // Flush the output buffer to prevent _getch() read the previous input

    print_layout(difficulty_layout);
    Difficulty input;
    bool pending = true;
	char key;

    while (pending) {
        if (_kbhit()) {

            key = _getch();
			if (key == Ctrl::ESC) return false; // If the key is ESC, return false
            input = static_cast<Difficulty>(key); // Get the key input

            switch (input) {
            case Difficulty::EASY:
                pGame->set_difficulty(Difficulty::EASY);
                pending = false;
                break;
            case Difficulty::MEDIUM:
                pGame->set_difficulty(Difficulty::MEDIUM);
                pending = false;
                break;
            case Difficulty::HARD:
                pGame->set_difficulty(Difficulty::HARD);
                pending = false;
                break;
            default:
                break;
            }
        }
		flash_message({ "Press ESC to return" }, { {27, 23} });
    }
    return true;
}

/**
* @brief Prints the exit message.
*/
void Display::exit_message() const {
    print_layout(exit_layout);
}

/**
* @brief Prints the strike message.
*/
void Display::strike_message() const {

	bool pending = true;
	char void_input;

    print_layout(strike_layout);
    std::cout.flush();
    while (pending) {
		flash_message({ "Press any key to continue" }, { {27, 23} });
		if (_kbhit()) {
            void_input = _getch(); // Get the key input to clear the buffer
			pending = false; // Check if a key is pressed
		}
    }
}

/**
* @brief Prints the failure message.
*/
void Display::failure_message() const {

    bool pending = true;
    char void_input;

    print_layout(fail_layout);

    gotoxy(40, 16); // Print the score
    std::cout << pGame->get_statistics().score;

    gotoxy(42, 18); // Print the time played (minutes : seconds)
    std::cout << std::setw(2) << std::setfill('0') << pGame->get_statistics().time_played.first << ":"
              << std::setw(2) << std::setfill('0') << pGame->get_statistics().time_played.second;


    while (pending) {
        flash_message({ "Press ESC to exit" }, { {30, 23} });
        if (_kbhit()) {
            void_input = _getch(); // Get the key input to clear the buffer
            pending = (void_input != Ctrl::ESC);
        }
    }
}

/**
* @brief Prints the success message.
*/
void Display::success_message() const {

    bool pending = true;
    char void_input;

    print_layout(success_layout);
    while (pending) {
        flash_message({ "Press any key to continue" }, { {27, 23} });   
        if (_kbhit()) {
            void_input = _getch(); // Get the key input to clear the buffer
            pending = false;
        }
    }
}

/**
 * @brief Prints the winning message (finished all valid levels).
 */
void Display::winning_message() const {

    bool pending = true;
    char void_input;

	print_layout(winning_layout);

	gotoxy(26, 22); // Print the score
	std::cout << pGame->get_statistics().score;
    
	gotoxy(54, 22); // Print the time played (minutes : seconds)
    std::cout << std::setw(2) << std::setfill('0') << pGame->get_statistics().time_played.first << ":"
        << std::setw(2) << std::setfill('0') << pGame->get_statistics().time_played.second;

    while (pending) {
        flash_message({ "Press any key to continue" }, { {27, 24} });
        if (_kbhit()) {
            void_input = _getch(); // Get the key input to clear the buffer
            pending = false;
        }
    }
}

/**
* @brief Prints a flash message for a short duration.
* @param message The message to print.
*/
void Display::flash_message(const std::vector<std::string>& messages, const std::vector<Coordinates>& positions) const {

	size_t size = messages.size();
	
	// Make the flash effect
	for (size_t i = 0; i < size; i++) { // Print the messages in the given positions
        gotoxy(positions[i]);
		std::cout << messages[i];
    }
    if (_kbhit()) return;
	Sleep(700);
	for (size_t i = 0; i < size; i++) { // Clear the messages
        size_t len = messages[i].size();
        gotoxy(positions[i]);
        while (len--) std::cout << " ";
    }
    if (_kbhit()) return;
	Sleep(200);
}

/**
 * @brief Prints the nickname prompt and update the game's nickname.
 */
void Display::prompt_nickname() const {
    print_layout(nickname_layout);
    gotoxy(37, 15);

	std::string buff; // Buffer to store the nickname (using string to make sure non of the chars will be left in the input stream)
	buff.reserve(Hof::NAME_LEN); // Reserve the maximum nickname length
    std::cin >> buff; // Read up to 6 characters, leaving space for the null terminator

    pGame->set_nickname(buff);
}


/**
* @brief Prints the error message.
* @param errors The vector of error codes.
* @return false if there are no errors, true otherwise.
*/
bool Display::error_message(const std::vector<Board::Err_Code>& errors) const {

	// Check if there are no errors, if so return false to stop the while loop
    if (errors.empty()) {
		return false; 
    }

	// Set the row to start printing the error messages
    int row = 17;
    bool pending = true;
	char void_input;

	// Print the layout
	print_layout(error_layout);
    gotoxy(33, 14);
    std::cout << '"' << pGame->pop_screen() << '"';


    // Mechnism to print the error messages
	for (auto err : errors) {
		gotoxy(3, row);
		switch (err) {
		case Board::Err_Code::MISSING_MARIO:
            std::cout << "-The screen must include a Mario (@) instance.";
            row += 1;
			break;
		case Board::Err_Code::MISSING_PAULINE:
            std::cout << "-The screen must include a Pauline ($) instance.";
            row += 1;
			break;
		case Board::Err_Code::FILE_FAIL:
			std::cout << "-File failed to open.";
            row += 1;
			break;
		default:
			break;
		}
	}
	while (pending) {
		flash_message({ "Press any key to skip to the next level" }, { {22, 23} });
        if (_kbhit()) {
            void_input = _getch(); // Get the key input to clear the buffer
            pending = false; // Check if a key is pressed
        }
	}
	return true;
}

/**
* @brief Prints the error message.
* @param errors The vector of error codes.
* @return false if there are no errors, true otherwise.
*/
bool Display::error_message(std::string message) const {

    // Print the layout
    print_layout(error_layout);
	bool pending = true;
	char void_input;

    gotoxy(33, 14);
	std::cout << "- " << message;
   
    while (pending) {
        flash_message({ "Press any key to skip to the next level" }, { {22, 23} });
        if (_kbhit()) {
            void_input = _getch(); // Get the key input to clear the buffer
            pending = false; // Check if a key is pressed
        }
    }
    return true;
}

/**
* @brief Prints the top scores.
*/
void Display::top_scores() const {

	print_layout(scores_board);
	int row = 13;
    bool pending = true;
	char void_input;

    // Print the top scores
    for (const auto& stats : pGame->get_hof()) {
        gotoxy(28, row);
        std::cout << stats.player_name;
        gotoxy(42, row);
        std::cout << stats.score;
        gotoxy(49, row);
        std::cout << std::setw(2) << std::setfill('0') << stats.time_played.first << ":" << std::setw(2) << std::setfill('0') << stats.time_played.second;
		gotoxy(57, row);
		switch (static_cast<Difficulty>(stats.difficulty)) {
		case Difficulty::EASY:
			std::cout << "MONKEY";
			break;
		case Difficulty::MEDIUM:
			std::cout << "APE";
			break;
		case Difficulty::HARD:
			std::cout << "D-KONG";
			break;
		default:
			break;
		}

        row++; // Move to the next row
    }
    while (pending) {
        if (_kbhit()) {
			(void_input = _getch()) == Ctrl::ESC ? pending = false : pending = true;
        }
		flash_message({ "Press ESC to return to menu" }, { {26, 24} });
    }
}


// Main menu layout
char Display::main_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "================================================================================",// 0
     "                                                                                ",// 1
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
  R"!(                        | ' /  | |  | | |  \| | | |  __                         )!",// 13
  R"!(     ."`".              |  <   | |  | | | . ` | | | |_ |                        )!",// 14
  R"!( .-./ _=_ \.-.          | . \  | |__| | | |\  | | |__| |                        )!",// 15
  R"!({  (,(oYo),) }}         |_|\_\  \____/  |_| \_|  \_____|                        )!",// 16
  R"!({{ |   "   |} }                                                                 )!",// 17
  R"!({ { \(---)/  }}              START A NEW GAME     - 1                           )!",// 18
     "{{  }'-=-'{ } }           (OPTIONAL) CHOOSE LEVEL - 2                           ",// 19
     "{{  } -:- { } }                 HALL OF FAME      - 7                           ",// 20
     "{{  } -:- { } }              INSTRUCTIONS& KEYS   - 8                           ",// 21
  R"!({_{ }`===`{  _}                    EXIT           - 9                           )!",// 22
  R"!((((\)    (/))))                                                                 )!",// 2
     "================================================================================", // 23
     "                                                                                ", // 24
};  

//Keys instructions layout
char Display::keys_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "================================================================================",// 0
  R"!(//****************************************************************************\\)!",// 1
     " *               Donkey Kong has kidnapped our beloved Pauline!               * ",// 2
     " *                       We must hurry to rescue her!!!                       * ",// 3
     " *          Dodge the barrels and the ghosts in your way by JUMPING           * ",// 4
     " *                     or pick up the hammer to HIT them.                     * ",// 5
  R"!( *                    Use the ladders to climb to the top.                    * )!",// 6
     " *                          You'd better move fast!                           * ",// 7
     " *              Every second counts when dealing with an ape like             * ",// 8
  R"!( *                                DONKEY KONG!                                * )!",// 9
  R"!( \\**************************************************************************// )!",// 10
     "                          _                                                     ",// 11
     "                         | | __   ___   _   _   ___   _                         ",// 12
  R"!(                         | |/ /  / _ \ | | | | / __| (_)                        )!",// 13
  R"!(                         |   <  |  __/ | |_| | \__ \  _                         )!",// 14
  R"!(                         |_|\_\  \___|  \__, | |___/ (_)                        )!",// 15
  R"!(                                        |___/                                   )!",// 16
     "                                 LEFT   -   A                                   ",// 17
     "                                 RIGHT  -   D                                   ",// 18
     "                                 JUMP   -   W                                   ",// 19
     "                                 DOWN   -   X                                   ",// 20
     "                                 STAY   -   S                                   ",// 21
     "                                 HIT    -   P                                   ",//22
     "================================================================================",// 23
     "                                                                                ", // 24

};

// Difficulty selection layout
char Display::difficulty_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
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
     "                                                                                ",// 11
     "                               MONKEY     -    1                                ",// 12
     "                                APE       -    2                                ",// 13
     "                            DONKEY KONG   -    3                                ",// 14
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
char Display::pause_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
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

// Exit message layout
char Display::exit_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
  R"!(                          ############################                          )!",//0
  R"!(   ____ / \               #                      _   #               / \ ____   )!",//1
     "  ( oo ) <>               #   __ _  ___  ___  __| |  #               <> ( oo )  ",//2
  R"!( _| ^^ |_<>               #  / _` |/ _ \/ _ \/ _` |  #               <>_| ^^ |_ )!",//3
  R"!(/    @   <>               #  \__, |\___/\___/\__,_|  #               <>   @    \)!",//4
  R"!(| _ . . /~~\              #  |___/                   #              /~~\ . . _ |)!",//5
  R"!(| |    /~~~~\             #     _                    #             /~~~~\    | |)!",//6
  R"!(| |_ \/~~~~~~\            #    | |__  _  _  ___      #            /~~~~~~\/ _| |)!",//7
  R"!([m] \ \[][][]|            #    | '_ \| || |/ -_)     #            |[][][]/ / [m])!",//8
  R"!(     [m]][][]|            #    |_.__/ \_, |\___|     #            |[][][[m]     )!",//9
     "      |[][][]|            #           |__/           #            |[][][]|      ",//10
     "      |[][][]|            ############################            |[][][]|      ",//11
     "      |[][][]|                                                    |[][][]|      ",//12
     "      |[][][]|                                                    |[][][]|      ",//13
     "      |[][][]|   ***********************************************  |[][][]|      ",//14
     "      |[][][]|                  ______  _                         |[][][]|      ",//15
  R"!(      |[][][]|                 |  __  \| \    /\                  |[][][]|      )!",//16
  R"!(      |[][][]|                 | (  \  |  \  / /                  |[][][]|      )!",//17
  R"!(      |[|--|]|                 | |   ) |  (_/ /                   |[|--|]|      )!",//18
  R"!(      |[|  |]|                 | |   | |   _ (                    |[|  |]|      )!",//19
  R"!(      ========                 | |   ) |  ( \ \                   ========      )!",//20
  R"!(     ==========                | (__/  |  /  \ \                 ==========     )!",//21
  R"!(     | [[  ]] |                |______/|_/    \/                 | [[  ]] |     )!",//22
     "     ==========                                                  ==========     ",//23
     "********************************************************************************",//24
};

// Try again message layout
char Display::strike_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
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

// Fail message layout
char Display::fail_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "********************************************************************************", // 0
     "*                                                                              *", // 1
     "*                                                                              *", // 2
     "*                                                                              *", // 3
     "*                                                                              *", // 4
     "*                                                                              *", // 5
     "*                                                                              *", // 6
     "*                                                                              *", // 7
     "*         __   __              _____  _     ___  _      _____  ____            *", // 8
  R"!(*         \ \ / /___   _   _  |  ___|/ \   |_ _|| |    | ____||  _ \           *)!", // 9
  R"!(*          \ V // _ \ | | | | | |_  / _ \   | | | |    |  _|  | | | |          *)!", // 10
  R"!(*           | || (_) || |_| | |  _|/ ___ \  | | | |___ | |___ | |_| |          *)!", // 11
  R"!(*           |_| \___/  \__,_| |_| /_/   \_\|___||_____||_____||____/           *)!", // 12
     "*                                                                              *", // 13
     "*                                                                              *", // 14
     "*                                                                              *", // 15
     "*                                SCORE:                                        *", // 16
     "*                                                                              *", // 17
     "*                            TIME PLAYED:                                      *", // 18
     "*                                                                              *", // 19
     "*                                                                              *", // 20
     "*                          BETTER LUCK NEXT TIME !                             *", // 21
     "*                                                                              *", // 22
     "*                                                                              *", // 23
     "********************************************************************************", // 24

};

// Success message layout
char Display::success_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
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
char Display::levels_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
     "            _                                    _                       _      ", // 0
     "      ___  | |__    ___    ___    ___   ___     | |  ___  __   __  ___  | |     ", // 1
  R"!(     / __| | '_ \  / _ \  / _ \  / __| / _ \    | | / _ \ \ \ / / / _ \ | |     )!", // 2
  R"!(     | (__ | | | || (_) || (_) | \__ \ | __/    | | | __/  \ V /  | __/ | |     )!", // 3
  R"!(     \___| |_| |_| \___/  \___/  |___/ \___|    |_| \___|   \_/   \___| |_|     )!", // 4
     "                                                                                ", // 5
     "                                                                                ", // 6
     "                                                                                ", // 7
     "                                                                                ", // 8
     "                                                                                ", // 9
     "                                                                                ", // 10
     "                                                                                ", // 11
     "                                                                                ", // 12
     "                                                                                ", // 13
     "                                                                                ", // 14
     "                                                                                ", // 15
     "                                                                                ", // 16
     "********************************************************************************", // 18
  R"!(|                        CHOOSE WHAT LEVEL TO START WITH.                      |)!", // 19
     "********************************************************************************", // 21
     "                                                                                ", // 16
     "                                                                                ", // 17
     "                                                                                ", // 22
     "                                                                                ", // 23
     "                                                                                ", // 24
};

// Error message layout
char Display::error_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
      //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    R"!(                                                                                )!", // 0
    R"!(         #############################################################          )!", // 1
    R"!(         #                                                           #          )!", // 2
    R"!(         #  8888888888 8888888b.  8888888b.   .d88888b.  8888888b.   #          )!", // 3
    R"!(         #  888        888   Y88b 888   Y88b d88P" "Y88b 888   Y88b  #          )!", // 4
    R"!(         #  888        888    888 888    888 888     888 888    888  #          )!", // 5
    R"!(         #  8888888    888   d88P 888   d88P 888     888 888   d88P  #          )!", // 6
    R"!(         #  888        8888888P"  8888888P"  888     888 8888888P"   #          )!", // 7
    R"!(         #  888        888 T88b   888 T88b   888     888 888 T88b    #          )!", // 8
    R"!(         #  888        888  T88b  888  T88b  Y88b. .d88P 888  T88b   #          )!", // 9
    R"!(         #  8888888888 888   T88b 888   T88b  "Y88888P"  888   T88b  #          )!", // 10
    R"!(         #                                                           #          )!", // 11
    R"!(         #############################################################          )!", // 12
    R"!(                                                                                )!", // 13
    R"!(                         SCREEN :                                               )!", // 14
    R"!(                                  IS NOT VALID                                  )!", // 15
    R"!(                                                                                )!", // 16
    R"!(                                                                                )!", // 17
    R"!(                                                                                )!", // 18
    R"!(                                                                                )!", // 19
    R"!(                                                                                )!", // 20
    R"!(                                                                                )!", // 21
    R"!(                                                                                )!", // 22
    R"!(                                                                                )!", // 23
    R"!(                                                                                )!"  // 24
};

// Finish succes message layout
char Display::winning_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
      //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    R"!(                             @%%%%%%%%%%%%%%%%%%%@                              )!", // 0
    R"!(                          -#%@%%%%%%%%%%%%%%%%%%%@%#-                           )!", // 1
    R"!(                        -@.:==@#               +@==- @=                         )!", // 2
    R"!(                        @ @.  :@       .       %-   @ @.                        )!", // 3
    R"!(                       .@ @    @      /|       %    @ @.                        )!", // 4
    R"!(                        @ @:   @       |       @   .@ @                         )!", // 5
    R"!(                        ##:@   %.      |       @   %-*%                         )!", // 6
    R"!(                         @:=#  +-     _|_     :#  **.@                          )!", // 7
    R"!(                          @+.@--@             @-:@:=@                           )!", // 8
    R"!(                           -@: @@#           *@@.:@=                            )!", // 9
    R"!(                             .@@=**         +#-@@:                              )!", // 10
    R"!(                                 :-@+     +@-:                                  )!", // 11
    R"!(                                   @=------@                                    )!", // 12
    R"!(                                   +@@@@@@@*                                    )!", // 13
    R"!(                                  .@@=   -@@:                                   )!", // 14
    R"!(                                  @-       :@                                   )!", // 15
    R"!(                              @*...............+@.                              )!", // 16
    R"!(                             #:   +*********+   .@                              )!", // 17
    R"!(                             %.    :+++++++-     @                              )!", // 18
    R"!(                             **+++++++++++++++++*%                              )!", // 19
    R"!(                  YOUV'E FINISHED SUCCEFULLY ALL THE LEVELS !                   )!", // 20
    R"!(                                                                                )!", // 21
    R"!(                   SCORE:                TIME PLAYED:                           )!", // 22
    R"!(                                                                                )!", // 23
    R"!(                                                                                )!", // 24
};

// Nickname prompt layout
char Display::nickname_layout[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
      //01234567890123456789012345678901234567890123456789012345678901234567890123456789
    R"!(||****************************************************************************||)!", // 0
    R"!(||           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           ||)!", // 1
    R"!(||           ~                  _                                 ~           ||)!", // 2
    R"!(||           ~  __      __ ___ | |  ___   ___   _ __ ___    ___   ~           ||)!", // 3
    R"!(||           ~  \ \ /\ / // _ \| | / __| / _ \ | '_ ` _ \  / _ \  ~           ||)!", // 4
    R"!(||           ~   \ V  V /|  __/| || (__ | (_) || | | | | ||  __/  ~           ||)!", // 5
    R"!(||           ~    \_/\_/  \___||_| \___| \___/ |_| |_| |_| \___|  ~           ||)!", // 6
    R"!(||           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           ||)!", // 7
    R"!(||                                                                            ||)!", // 8
    R"!(||                                                                            ||)!", // 9
    R"!(||                                                                            ||)!", // 10
    R"!(||                    The rumors about Pauline are true !                     ||)!", // 11
    R"!(||                But before you face off against Donkey Kong                 ||)!", // 12
    R"!(||                          Please enter a NICKNAME:                          ||)!", // 13
    R"!(||                                                                            ||)!", // 14
    R"!(||                                                                            ||)!", // 15
    R"!(||                          ***********************                           ||)!", // 16
    R"!(||                               (max 6 char)                                 ||)!", // 17
    R"!(||                                                                            ||)!", // 18
    R"!(||                                                                            ||)!", // 19
    R"!(||                       -- press Enter to continue --                        ||)!", // 20
    R"!(||                                                                            ||)!", // 21
    R"!(||                                                                            ||)!", // 22
    R"!(||                                                                            ||)!", // 23
    R"!(||****************************************************************************||)!", // 24
};

char Display::scores_board[SCREEN_HEIGHT][SCREEN_WIDTH + 1] = {
    //01234567890123456789012345678901234567890123456789012345678901234567890123456789
  R"!(********************************************************************************)!", // 0
  R"!( _____                                                                    _____ )!", // 1
  R"!(( ___ )------------------------------------------------------------------( ___ ))!", // 2
  R"!( |   |  _             _  _           __    __                             |   | )!", // 3
  R"!( |   | | |__    __ _ | || |   ___   / _|  / _|  __ _  _ __ ___    ___   _ |   | )!", // 4
  R"!( |   | | '_ \  / _` || || |  / _ \ | |_  | |_  / _` || '_ ` _ \  / _ \ (_)|   | )!", // 5
  R"!( |   | | | | || (_| || || | | (_) ||  _| |  _|| (_| || | | | | ||  __/  _ |   | )!", // 6
  R"!( |   | |_| |_| \__,_||_||_|  \___/ |_|   |_|   \__,_||_| |_| |_| \___| (_)|   | )!", // 7
  R"!( |___|                                                                    |___| )!", // 8
  R"!((_____)------------------------------------------------------------------(_____))!", // 9
  R"!(             ----------------------------------------------------               )!", // 10
  R"!(            ||   PLACE    |    NAME    | SCORE | TIME  |  MODE   ||             )!", // 11
  R"!(            ||---------------------------------------------------||             )!", // 12
  R"!(            ||     #1     |            |       |       |         ||             )!", // 13
  R"!(            ||     #2     |            |       |       |         ||             )!", // 14
  R"!(            ||     #3     |            |       |       |         ||             )!", // 15
  R"!(            ||     #4     |            |       |       |         ||             )!", // 16
  R"!(            ||     #5     |            |       |       |         ||             )!", // 17
  R"!(            ||     #6     |            |       |       |         ||             )!", // 18
  R"!(            ||     #7     |            |       |       |         ||             )!", // 19
  R"!(            ||     #8     |            |       |       |         ||             )!", // 20
  R"!(            ||     #9     |            |       |       |         ||             )!", // 21
  R"!(            ||     #10    |            |       |       |         ||             )!", // 22
  R"!(             ----------------------------------------------------               )!", // 23
  R"!(                              press Esc to exit                                 )!"  // 24
  /////////////////////////////flash this message right here//////////////////////////////////
};
