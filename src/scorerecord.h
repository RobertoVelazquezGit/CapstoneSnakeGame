#ifndef SCORERECORD_H
#define SCORERECORD_H

#include <string>

class ScoreRecord {
private:
    int highest_score;
    int latest_score;

    // Simple types can be initialized here. More complex type, like a std::string, we need to initialize it in the .cpp file
    static const int DEFAULT_HIGHEST_SCORE = 0;
    static const int DEFAULT_LATEST_SCORE = 0;
    static const std::string FILENAME;

public:
    // Constructor
    ScoreRecord();

    // Getters
    int getHighestScore() const;
    int getLatestScore() const;

    // Setters
    void setHighestScore(int score);
    void setLatestScore(int score);

    // Method to save scores to the file
    void saveToFile() const;
};

#endif // SCORERECORD_H

