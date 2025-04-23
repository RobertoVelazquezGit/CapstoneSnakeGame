#include "scorerecord.h"
#include <iostream>
#include <fstream>
#include <sstream>

#ifdef MY_SCORERECORD_PATH_DEBUG
const std::string ScoreRecord::FILENAME = "./scorerecord.txt";  // When debugging
#else
const std::string ScoreRecord::FILENAME = "../scorerecord.txt";  // when ./build/SnakeGame executed
#endif

ScoreRecord::ScoreRecord() {
    std::ifstream infile(FILENAME);
    if (!infile.is_open()) {
        std::cerr << "Warning: could not open file, initializing scores to default values.\n";
        highest_score = DEFAULT_HIGHEST_SCORE;
        latest_score = DEFAULT_LATEST_SCORE;
        return;
    }

    // Initialize with default in case file is malformed
    highest_score = DEFAULT_HIGHEST_SCORE;
    latest_score = DEFAULT_LATEST_SCORE;

    std::string line;
    int parsed_values = 0;

    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string key;
        int value;

        if (!(iss >> key >> value)) {
            std::cerr << "Warning: invalid line format in file: \"" << line << "\"\n";
            continue; // Skip malformed lines
        }

        if (key == "highest_score") {
            highest_score = value;
            parsed_values++;
        } else if (key == "latest_score") {
            latest_score = value;
            parsed_values++;
        } else {
            std::cerr << "Warning: unknown key in file: \"" << key << "\"\n";
        }
    }

    infile.close();

    if (parsed_values < 2) {
        std::cerr << "Warning: some scores were not found in the file, using defaults.\n";
    }
}

// Getters
int ScoreRecord::getHighestScore() const {
    return highest_score;
}

int ScoreRecord::getLatestScore() const {
    return latest_score;
}

// Setters
void ScoreRecord::setHighestScore(int score) {
    highest_score = score;
}

void ScoreRecord::setLatestScore(int score) {
    latest_score = score;
}

// Saves the scores to the file (overwrites previous content)
void ScoreRecord::saveToFile() const {
    std::ostringstream line1;
    std::ostringstream line2;

    line1 << "highest_score " << highest_score;
    line2 << "latest_score " << latest_score;

    std::ofstream outfile(FILENAME, std::ios::trunc);
    if (outfile.is_open()) {
        outfile << line1.str() << "\n";
        outfile << line2.str() << "\n";
        outfile.close();
    } else {
        std::cerr << "Error: could not open file for writing.\n";
    }
}


