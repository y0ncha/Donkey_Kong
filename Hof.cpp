#include "Hof.h"
#include <iostream>
#include <algorithm>

/**
* @brief Constructor for the Hof class.
* Opens the hall of fame file and loads the statistics.
* @note The constructor is private to prevent instantiation.
*/
Hof::Hof() : fsize(0), nof_stats(0) {
    // Open the file in binary mode for reading only
    file.open(fname, std::ios::binary | std::ios::in);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        // If the file does not exist, create it
        std::ofstream create_file(fname, std::ios::binary);
        create_file.close();
        // Reopen the file in read-only mode
        file.open(fname, std::ios::binary | std::ios::in);
    }
    // Get the file size
    if (file.is_open()) {
        file.seekg(0, std::ios::end);
        fsize = file.tellg();
        nof_stats = fsize / sizeof(Statistics);
        load();
    } 
    else {
        // todo print error
    }
    file.close();
}

/**
 * @brief Destructor for the Hof class.
 * Saves the hall of fame to the file.
 */
Hof::~Hof() {
    save();
}

/**
 * @brief Load the hall of fame from the file to the list.
 * @return True if the hall of fame was loaded properly, false otherwise.
 * @note the method does not opens the file but do checks if the file is open.
 */
bool Hof::load() {
    // Open the file in binary mode for reading
    std::ifstream file(fname, std::ios::binary | std::ios::in);

    if (!file.is_open()) {
        return false;
    }

    // Read the statistics from the file
    for (size_t i = 0; i < nof_stats; i++) {
        Statistics stats;
        read_statistics(file, stats);
        stats_list.push_back(stats);
    }
    file.close();
    return true;
}

/**
 * @brief Saves the hall of fame to the file (write over the old data).
 * @return True if the hall of fame was saved properly, false otherwise.
 */
bool Hof::save() {
    // Open the file in binary mode for writing
    std::ofstream file(fname, std::ios::binary | std::ios::out);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        return false;
    }

    // Write the statistics to the file
    for (const auto& stats : stats_list) {
        write_statistics(file, stats);
    }
    file.close();
    return true;
}

/**
 * @brief Getter for the singleton instance of Hof.
 * @return The singleton instance of Hof.
 */
Hof& Hof::get_instance() {
    static Hof instance;
    return instance;
}

/**
 * @brief Inserts the new statistics in the correct place.
 * @param stats The new statistics to insert.
 * @return True if the statistics were inserted, false otherwise.
 */
bool Hof::record_statistics(const Statistics& stats) {

    // If the list is empty, insert the new statistics
    if (stats_list.empty()) {
        stats_list.push_back(stats);
        nof_stats++;
        return true;
    }

    // Insert the new statistics in the correct place
    for (auto it = stats_list.begin(); it != stats_list.end(); ++it) {
        if (stats.score > it->score) {
            stats_list.insert(it, stats);
            if (stats_list.size() > TOP_SCORES) stats_list.pop_back();
            nof_stats = stats_list.size();
            return true;
        }
    }

    // If the new statistics has the lowest score and the list is not full, insert it at the end
    if (stats_list.size() < TOP_SCORES) {
        stats_list.push_back(stats);
        nof_stats = stats_list.size();
        return true;
    }

    return false;
}

/**
 * @brief Gets the game statistics at the specified index.
 * @param i The index of the statistics to get.
 * @return The game statistics at the specified index.
 */
const Hof::Statistics& Hof::get_stats_at(int n) const {

	// Return an empty statistics if the index is out of bounds
    static Statistics empty_stats;
    if (n < 0 || n >= stats_list.size()) {
        return empty_stats;
    }
	auto it = stats_list.begin();
	std::advance(it, n);
	return *it;
}

/**
 * @brief Gets the entire list of game statistics.
 * @return A constant reference to the list of game statistics.
 */
const std::list<Hof::Statistics>& Hof::get_list() const {
	return stats_list;
}

/**
* @brief Writes the statistics to the file.
 * @param file The file to write the statistics to.
 * @param stats The statistics to write.
 */
void Hof::write_statistics(std::ofstream& file, const Hof::Statistics& stats) {
    file.write(stats.player_name, sizeof(stats.player_name));
    file.write(reinterpret_cast<const char*>(&stats.score), sizeof(stats.score));
    file.write(reinterpret_cast<const char*>(&stats.time_played.first), sizeof(stats.time_played.first));
    file.write(reinterpret_cast<const char*>(&stats.time_played.second), sizeof(stats.time_played.second));
    file.write(reinterpret_cast<const char*>(&stats.difficulty), sizeof(stats.difficulty));
}

/**
* @brief Reads the statistics from the file.
* @param file The file to read the statistics from.
* @param stats The statistics to read.
*/
void Hof::read_statistics(std::ifstream& file, Hof::Statistics& stats) {
	file.read(stats.player_name, sizeof(stats.player_name));
	file.read(reinterpret_cast<char*>(&stats.score), sizeof(stats.score));
	file.read(reinterpret_cast<char*>(&stats.time_played.first), sizeof(stats.time_played.first));
	file.read(reinterpret_cast<char*>(&stats.time_played.second), sizeof(stats.time_played.second));
	file.read(reinterpret_cast<char*>(&stats.difficulty), sizeof(stats.difficulty));
}
