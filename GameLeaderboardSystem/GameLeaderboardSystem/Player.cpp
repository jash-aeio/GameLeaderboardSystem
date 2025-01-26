#include "Player.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

// Clear screen implementation
void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the terminal
}

// Leaderboard constructor
Leaderboard::Leaderboard() : totalPlayers(0), capacity(10) {
    allPlayers = new Player[capacity];
}

// Resize array dynamically
void Leaderboard::resizeArray() {
    capacity *= 2;
    Player* temp = new Player[capacity];
    for (int i = 0; i < totalPlayers; i++) {
        temp[i] = allPlayers[i];
    }
    delete[] allPlayers;
    allPlayers = temp;
}

// Check if the leaderboard is empty
bool Leaderboard::isEmpty() const {
    return totalPlayers == 0;
}

// Add new player
bool Leaderboard::addPlayer(const string& name, int score) {
    if (playerExists(name)) {
        return false; // Player already exists
    }

    if (totalPlayers == capacity) {
        resizeArray();
    }

    allPlayers[totalPlayers++] = Player(name, score);
    return true; // Player added successfully
}

// Update player's score
bool Leaderboard::updatePlayerScore(const string& name, int score) {
    for (int i = 0; i < totalPlayers; i++) {
        if (allPlayers[i].name == name) {
            allPlayers[i].score = max(allPlayers[i].score, score); // Update only if the new score is higher
            return true;
        }
    }
    return false; // Player not found
}

// Check if player exists
bool Leaderboard::playerExists(const string& name) const {
    for (int i = 0; i < totalPlayers; i++) {
        if (allPlayers[i].name == name) {
            return true; // Player exists
        }
    }
    return false; // Player does not exist
}

void Leaderboard::detailsHeader() {
    cout << left << setw(10) << "Rank" << setw(30) << "Player Name" << setw(10) << "Score" << endl;
    cout << "--------------------------------------------------\n";
}

// Display leaderboard
void Leaderboard::displayLeaderboard() {
    if (isEmpty()) {
        cout << "\nThe leaderboard is currently empty.\n";
        cout << "\nPress Enter key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n================== Leaderboard ===================\n";
    cout << "Choose leaderboard view:\n";
    cout << "1. Top 10\n";
    cout << "2. Top 50\n";
    cout << "3. Bottom 10\n";
    cout << "4. Bottom 50\n";
    cout << "5. Specific Rank\n";
    cout << "--------------------------------------------------\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;
    int rank = 0;

    if (choice == 5) {
        cout << "Enter rank to view: ";
        cin >> rank;
    }

    switch (choice) {
    case 1:
        cout << "\n=============== Top 10 Leaderboard ===============\n";
        detailsHeader();
        for (int i = 0; i < (totalPlayers < 10 ? totalPlayers : 10); i++) {
            cout << left << setw(10) << i + 1 << setw(30) << allPlayers[i].name << setw(10) << allPlayers[i].score << "\n";
        }
        break;
    case 2:
        cout << "\n=============== Top 50 Leaderboard ===============\n";
        detailsHeader();
        for (int i = 0; i < (totalPlayers < 50 ? totalPlayers : 50); i++) {
            cout << left << setw(10) << i + 1 << setw(30) << allPlayers[i].name << setw(10) << allPlayers[i].score << "\n";
        }
        break;
    case 3:
        cout << "\n============== Bottom 10 Leaderboard =============\n";
        detailsHeader();
        for (int i = totalPlayers - 1, count = 0; i >= 0 && count < 10; i--, count++) {
            cout << left << setw(10) << totalPlayers - i << setw(30) << allPlayers[i].name << setw(10) << allPlayers[i].score << "\n";
        }
        break;
    case 4:
        cout << "\n============== Bottom 50 Leaderboard =============\n";
        detailsHeader();
        for (int i = totalPlayers - 1, count = 0; i >= 0 && count < 50; i--, count++) {
            cout << left << setw(10) << totalPlayers - i << setw(30) << allPlayers[i].name << setw(10) << allPlayers[i].score << "\n";
        }
        break;
    case 5:
        cout << "\n=========== Specific Rank Leaderboard ============\n";
        if (rank > 0 && rank <= totalPlayers) {
            cout << left << setw(10) << rank << setw(30) << allPlayers[rank - 1].name << setw(10) << allPlayers[rank - 1].score << "\n";
        }
        else {
            cout << "Invalid rank!\n";
        }
        break;
    default:
        cout << "Invalid choice!\n";
    }
    cout << "==================================================\n";
    cout << "\nPress Enter key to continue...";
    cin.ignore();
    cin.get();
}

// Display all players
void Leaderboard::displayAllPlayers() {
    if (isEmpty()) {
        cout << "\nThe leaderboard is currently empty.\n";
        cout << "\nPress Enter key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    cout << "\n=================== All Players ==================\n";
    for (int i = 0; i < totalPlayers; i++) {
        cout << left << setw(10) << i + 1 << setw(30) << allPlayers[i].name << setw(10) << allPlayers[i].score << "\n";
    }

    cout << "==================================================\n";
    cout << "\nPress Enter key to continue...";
    cin.ignore();
    cin.get();
}

// Save leaderboard to file
void Leaderboard::saveLeaderboardToFile() {
    if (isEmpty()) {
        cout << "\nThe leaderboard is empty. No data to save.\n";
        cout << "\nPress Enter key to continue...";
        cin.ignore();
        cin.get();
        return;
    }

    ofstream file("leaderboard.txt");
    if (!file) {
        cout << "Error saving leaderboard to file.\n";
        return;
    }

    file << "Rank\tPlayer Name\tScore\n";
    for (int i = 0; i < totalPlayers; i++) {
        file << i + 1 << "\t" << allPlayers[i].name << "\t" << allPlayers[i].score << "\n";
    }
    cout << "\nLeaderboard saved to 'leaderboard.txt' successfully!\n";
    file.close();
    cout << "\nPress Enter key to continue...";
    cin.ignore();
    cin.get();
}

// Clear leaderboard contents
void Leaderboard::clearLeaderboardContents() {
    delete[] allPlayers; // Free the existing array
    totalPlayers = 0;    // Reset player count
    capacity = 10;       // Reset capacity
    allPlayers = new Player[capacity]; // Reallocate the array

    ofstream file("leaderboard.txt", ios::trunc); // Truncate the file
    if (!file) {
        cout << "Error clearing leaderboard file.\n";
        return;
    }
    cout << "\nLeaderboard cleared successfully!\n";
    file.close();
    cout << "\nPress Enter key to continue...";
    cin.ignore();
    cin.get();
}

// Load leaderboard from file
void Leaderboard::loadLeaderboardFromFile() {
    ifstream file("leaderboard.txt");
    if (!file) {
        cout << "No leaderboard file found. Starting with an empty leaderboard.\n";
        return;
    }

    string name;
    int score;
    totalPlayers = 0; // Reset totalPlayers before loading

    // Skip the header line
    string header;
    getline(file, header);

    while (file >> score) {
        file.ignore(); // Ignore the tab character
        getline(file, name);
        addPlayer(name, score);
    }

    cout << "Leaderboard loaded from 'leaderboard.txt' successfully!\n";
    file.close();
    cout << "\nPress Enter key to continue...";
    cin.ignore();
}

// Validate input
int Leaderboard::validateInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a non-negative number.\n\n";
        }
        else {
            break;
        }
    }
    return value;
}

// Destructor
Leaderboard::~Leaderboard() {
    delete[] allPlayers;
}
