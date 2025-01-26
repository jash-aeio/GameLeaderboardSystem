#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

void displayMenu() {
    clearScreen();
    cout << "==================================================\n";
    cout << "            Nix Game Leaderboard System      \n";
    cout << "==================================================\n";
    cout << "[1]   Add New Player Score\n";
    cout << "[2]   Update Existing Player Score\n";
    cout << "[3]   Display Leaderboard\n";
    cout << "[4]   Display All Players\n";
    cout << "[5]   Save Leaderboard to File\n";
    cout << "[6]   Delete Leaderboard Contents\n";
    cout << "[7]   Exit\n";
    cout << "==================================================\n";
    cout << "Enter your choice: ";
}

int main() {
    Leaderboard leaderboard;
    leaderboard.loadLeaderboardFromFile(); // Load leaderboard data from file
    int choice;

    do {
        displayMenu();
        while (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice! Enter a number between 1 and 7: ";
        }

        switch (choice) {
        case 1: { // Add New Player
            string name;
            int score;
            cout << "\n============= Add New Player Score ==============\n";
            cout << "Enter player name: ";
            cin.ignore();
            getline(cin, name);

            // Check if the player already exists
            if (leaderboard.playerExists(name)) {
                cout << "Player '" << name << "' already exists.\n";
                cout << "Use option[2] to update the score of an existing player.\n";
            }
            else {
                score = leaderboard.validateInput("Enter player score (non-negative): ");
                leaderboard.addPlayer(name, score); // Call the new method for adding a player
                cout << "Player '" << name << "' added successfully with a score of " << score << ".\n";
            }

            cout << "\nPress Enter key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 2: { // Update Existing Player
            string name;
            int score;
            cout << "\n========== Update Existing Player Score =========\n";
            cout << "Enter player name: ";
            cin.ignore();
            getline(cin, name);

            // Check if the player exists
            if (!leaderboard.playerExists(name)) {
                cout << "Player '" << name << "' does not exist.\n";
                cout << "Use option[1] to add a new player.\n";
            }
            else {
                score = leaderboard.validateInput("Enter new score (non-negative): ");
                leaderboard.updatePlayerScore(name, score); // Call the new method for updating a player's score
                cout << "Player '" << name << "' score updated to " << score << ".\n";
            }

            cout << "\nPress Enter key to continue...";
            cin.ignore();
            cin.get();
            break;
        }
        case 3:
            leaderboard.displayLeaderboard();
            break;
        case 4:
            leaderboard.displayAllPlayers();
            break;
        case 5:
            leaderboard.saveLeaderboardToFile();
            break;
        case 6:
            leaderboard.clearLeaderboardContents();
            break;
        case 7:
            cout << "\nThank you for using the Game Leaderboard System!\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
