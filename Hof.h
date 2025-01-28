#pragma once
#include <fstream>
#include <list>
#include <iostream>

/**
 * @class Hof
 * Represents the hall of fame.
 */
class Hof {

public:

	// Constants
    static constexpr int NAME_LEN = 7; // Maximum length of the player's name
    static constexpr int TOP_SCORES = 10; // Maximum number of top scores to display
	static constexpr int STATS_SIZE = 23; // Stats size in bytes

    // Struct to hold the game statistics
    struct Statistics {
        char player_name[NAME_LEN] = "";
        int score = 0;
        std::pair<int, int> time_played = { 0 ,0 };
        int difficulty = 0;
    };

    // Method to get the singleton instance of Hof
    static Hof& get_instance();

    // Method to insert the new statistics in the correct place
    bool record_statistics(const Statistics& stats);

    // Method to get the game statistics in the nth place
    const Statistics& get_stats_at(int n) const;

    // Method to get the entire list of statistics
    const std::list<Statistics>& get_list() const;

    // Method to check if the hall of fame is available
	bool is_available() const;

private:

    // Constructor - Checks the file exist and loads the statistics
    Hof();

    // Destructor - Saves the statistics to the file
    ~Hof();

    // Delete copy constructor and copy assignment operator
    Hof(const Hof&) = delete;
    Hof& operator=(const Hof&) = delete;

    // Delete move constructor and move assignment operator
    Hof(Hof&&) = delete;
    Hof& operator=(Hof&&) = delete;

    // Bool to check if the hall of fame opened successfully
    bool available;

    // Method to load the stats from the file
    bool load(std::ifstream& file);

    // Method to save the stats to the file
    bool save();

	// Method to write the stats to the file
	void write_statistics(std::ofstream& file, const Statistics& stats);

	// Method to read the stats from the file
	void read_statistics(std::ifstream& file, Statistics& stats);

    // File name to store the Hall Of Fame
    std::string fname = "hof.bin";

    // List to hold the game statistics in descending order
    std::list<Statistics> stats_list;

    // File size and number of statistics
    size_t fsize, nof_stats;
};
