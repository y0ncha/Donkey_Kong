#include "Visual_Level.h"



/**
 * @brief Constructor for the Visual_Level class.
 * @param
 */
Visual_Level::Visual_Level(std::string screen, Mario& mario) :
	Level_Base(screen, mario), 
	steps(generate_fname("steps"), std::ios::in),
	result(generate_fname("result"), std::ios::in) {

	if (steps.is_open()) {
		steps >> diff;
		steps >> seed;
		next_step = read_next(File_Type::STEPS);
	}
	if (result.is_open()) {
		is_level_sucsses();
		next_res = read_next(File_Type::RES); 
	}
	srand(seed);
}

/**
 * @brief Destructor for the Visual_Level class.
 */
Visual_Level::~Visual_Level() {
	steps.close();
	result.close();
}

/**
 * @brief Starts the level loop.
 * @return The game state.
 */
Game_State Visual_Level::start() {

	Game_State state = Game_State::RUN; // Variable to hold the game state
	char input; // Variable to hold the user input
	Ctrl key; // Variable to hold the key input
	
	if (!steps.is_open()) return handle_steps_isnt_open(Game_Mode::LOAD);
	if (!result.is_open()&&!res_message_appear) handle_result_isnt_open(Game_Mode::LOAD);

	render_level(); // Update the game screen

	while (state == Game_State::RUN) { // Main game loop

		if (frames == next_step.first) {
			input = std::tolower(next_step.second);
			key = static_cast<Ctrl>(input);

			if (input == TERMINATOR) {
				state = Game_State::EXIT;
				break;
			}
			else if (key == Ctrl::HIT && mario.is_armed()) {
				perform_attack(); // Handle the hammer attack
			}
			else {
				mario.update_dir(input); // If any other key is pressed
			}
			next_step = read_next(File_Type::STEPS);
		}
		state = advance_entities(); // Advance all the entities in the game
		if (result.is_open()&&is_result_action_required(state)) {
			check_result(state);
			if (next_res.second != static_cast<char>(Result_Type::SCORE_GAINED))
			next_res = read_next(File_Type::RES);
		}
		Sleep(REPLAY_DELAY); // Delay for 100 milliseconds
		frames++;
	}

	if (level_success && (state == Game_State::EXIT || state == Game_State::FAIL)) {
		state = Game_State::SUCCESS;
		Display::print_load_bug();
	}

	if (state== Game_State::EXIT||state==Game_State::FAIL||state==Game_State::SUCCESS)
	push_remaining_results();

	return state;
}

/**
 * @brief Reads the next step or result from the file.
 * @return The next step or result
 */
std::pair<int, char> Visual_Level::read_next(File_Type type) {
	std::pair<int, char> next_type;
	if (type == File_Type::STEPS&&steps.is_open()) {
		steps >> next_type.first >> next_type.second;
		}
	else if(type == File_Type::RES&&result.is_open()){
		result >> next_type.first >> next_type.second;
	}
	return next_type;
}

// Method to generate the error string
std::string Visual_Level::generate_error_string(Result_Type type,bool UnKnown) const
{
	std::string res ="##ERROR##- "+ screen + "\n";
	if (!UnKnown) {
		if (type == Result_Type::LIFE_LOST || type == Result_Type::FINISH_SCREEN) {
			res += " -- Recorded screen frame: " + std::to_string(next_res.first) + " -- Dispalyed screen frame: " + std::to_string(frames);
			if (type == Result_Type::LIFE_LOST)
				res += " Mario lost life";
			else// type == Result_Type::FINISH_SCREEN
				res += " Mario finished the screen";
		}
		else//type == Result_Type::SCORE_GAINED
			res += " -- Recorded screen score : " + std::to_string(next_res.first) + " -- Displayed screen score: " + std::to_string(mario.get_score());
	}
	else
	{
		res += "Saved screen not match Displayed screen. ";
		switch (type)
		{	
		case Result_Type::LIFE_LOST:
			res += "Mario wasnt supposed to lose a life.";
			break;
		case Result_Type::FINISH_SCREEN:
			res+= "Mario wasnt supposed to end screen.";
			break;
		case Result_Type::SCORE_GAINED:
			res+= "Mario wasnt supposed to fail.";
			break;
		default:
			break;
		}
	}
	return res;
}

void Visual_Level::check_result(Game_State state)
{
	bool valid = false;
	Result_Type unknown;// Variable to hold the unknown result if the result not match the game state

	switch (state) {
	case Game_State::RETRY:
		unknown= Result_Type::LIFE_LOST;
		valid= compare_results(Result_Type::LIFE_LOST);
		break;

	case Game_State::SUCCESS:
		unknown = Result_Type::FINISH_SCREEN;
		if (valid = compare_results(Result_Type::FINISH_SCREEN)){// Check if the recorded result is the same as the displayed result
			next_res = read_next(File_Type::RES);
		}
		break;

	case Game_State::FAIL:
		unknown = Result_Type::SCORE_GAINED;
		if (valid = compare_results(Result_Type::LIFE_LOST)) {// Check if the recorded result is life lost
			next_res = read_next(File_Type::RES);
		}
	};
	// Push the unknown error to the error vector if the result not match the game state
	if (!valid) Display::push_res_errors(generate_error_string(unknown, true));

}

// Method to compare the results to the game
bool Visual_Level::compare_results(Result_Type type)
{
	bool res = false;
	if (next_res.second == static_cast<char>(type))// Check if the recorded result is the same as the displayed result
	{
		res = true;
		if (frames != next_res.first)// Check if the recorded frame is the same as the displayed frame
			Display::push_res_errors(generate_error_string(type));
	}
	return res;
}

// Method to compare the score
void Visual_Level::compare_score()
{
	if (next_res.second == static_cast<char>(Result_Type::SCORE_GAINED))// Check if the recorded result is score gained
		if (mario.get_score() != next_res.first)// Check if the recorded score is the same as the displayed score
			Display::push_res_errors(generate_error_string(Result_Type::SCORE_GAINED));
		else
		{
			Display::push_res_errors("##EQUAL SCORE## - " + screen 
				                   + "\n -- Recorded screen score : " + std::to_string(next_res.first)
								     + " -- Displayed screen score: " + std::to_string(mario.get_score()));
			Display::Num_of_Test_Passed++;	
		}
}

void Visual_Level::is_level_sucsses()
{
	int size = sizeof(int) + sizeof(char) + sizeof(" ");
	result.seekg(-size, std::ios::end);
	next_res = read_next(File_Type::RES);
	if (next_res.second == static_cast<char>(Result_Type::LEVEL_END) && next_res.first == static_cast<int>(SUC_OR_FAIL::SUCCESS))
		level_success = true;
	else level_success = false;
	result.seekg(0, std::ios::beg);
}

// Method to push the remaining results to the vector
void Visual_Level::push_remaining_results()
{
	std::string res;

	while (next_res.second!=static_cast<char> (Result_Type::LEVEL_END))
	{
		res = "";
		switch (next_res.second)
		{
		case static_cast<char>(Result_Type::LIFE_LOST):
			res += "##LOAD AND SAVE NOT EQUAL## "+screen+"\n--Recorded screen frame : "
				+ std::to_string(next_res.first) + " Mario lost life";
			Display::push_res_errors(res);
			break;
		case static_cast<char>(Result_Type::FINISH_SCREEN):
			res += "##LOAD AND SAVE NOT EQUAL## " + screen + "\n--Recorded screen frame : "
				+ std::to_string(next_res.first) + " Mario finished the screen";
			Display::push_res_errors(res);
			break;
		case static_cast<char>(Result_Type::SCORE_GAINED):
			compare_score();
			break;
		}
		next_res=read_next(File_Type::RES);
	}
}


