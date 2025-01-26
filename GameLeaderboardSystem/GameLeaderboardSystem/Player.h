#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
public:
    string name;
    int score;

    // Default Constructor
    Player() : name(""), score(0) {}

    // Parameterized Constructor
    Player(string playerName, int playerScore) : name(playerName), score(playerScore) {}

    // Overloaded operator for comparisons
    bool operator<(const Player& other) const {
        return score < other.score;
    }
};

class Leaderboard {
private:
    Player* allPlayers;
    int totalPlayers;
    int capacity;

    void resizeArray();

public:
    Leaderboard();
    ~Leaderboard();

    void detailsHeader();
    bool addPlayer(const string& name, int score);            // Add new player
    bool updatePlayerScore(const string& name, int score);    // Update existing player's score
    bool playerExists(const string& name) const;             // Check if a player exists
    void displayLeaderboard();
    void displayAllPlayers();
    void saveLeaderboardToFile();
    void clearLeaderboardFile();
    void loadLeaderboardFromFile();
    int validateInput(const string& prompt);
    bool isEmpty() const; // Check if the leaderboard is empty
    void clearLeaderboardContents();
};

void clearScreen(); // Clear screen function

#endif
