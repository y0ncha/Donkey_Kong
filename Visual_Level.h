#pragma once
#include "Level_Base.h"

class Level_Base;

class Visual_Level : public Level_Base {

public:

	// Constructor for the Visual_Level class
	Visual_Level(std::string screen, Mario& mario);

	// Destructor for the Visual_Level class
	~Visual_Level();


protected:

	// Method to start the level loop
	Game_State start() override;

	// Method to read the next step from the file
	std::pair<int, char> read_next(File_Type type);

	// Variable to hold the next step
	std::pair<int, char> next_step;

	// Variable to hold the next result
	std::pair<int,char> next_res;

	// Terminator
	static const char TERMINATOR = '~';

	// Method to generate the error string
	std::string generate_error_string(Result_Type type,bool UnKnown=false) const;

	// Method to check if the result matches the game
	void check_result(Game_State state);

	// Method to compare the results to the game
	bool compare_results(Result_Type type);

	// Method to compare the score
	void compare_score();

	// Method to check if the result file is open
	bool result_file_open() { return result.is_open(); };

	// Method to check if the steps file is open
	bool steps_file_open() { return steps.is_open(); };

	//method to check if the level is success in save mood
	void is_level_sucsses();

	// variable to hold if mario finish the level in save mood when runnin load mood
	bool level_success = false;

	// Method to push the remaining results to the vector
	void push_remaining_results();

private: 


	// File to read the steps from
	std::ifstream steps;

	// File to read the results from
	std::ifstream result;
};