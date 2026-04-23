#include "SkipList.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Simulate a game between two teams
void simulateGame(SkipList& leaderboard, string team1Name, string team2Name) {
    // Random score between 3-10 for each team
    int score1 = rand() % 8 + 3;
    int score2 = rand() % 8 + 3;
    
    // Make sure there's a winner
    if (score1 == score2) {
        score1++;
    }
    
    string winner = (score1 > score2) ? team1Name : team2Name;
    string loser = (score1 > score2) ? team2Name : team1Name;
    int winnerScore = max(score1, score2);
    int loserScore = min(score1, score2);
    
    // Get current team data
    Team* team1 = leaderboard.search(team1Name);
    Team* team2 = leaderboard.search(team2Name);
    
    if (team1 && team2) {
        // Remove both teams
        leaderboard.remove(team1Name);
        leaderboard.remove(team2Name);
        
        // Update records
        if (winner == team1Name) {
            team1->wins++;
            team1->totalPoints += winnerScore;
            team2->losses++;
            team2->totalPoints += loserScore;
        } else {
            team2->wins++;
            team2->totalPoints += winnerScore;
            team1->losses++;
            team1->totalPoints += loserScore;
        }
        
        // Reinsert with updated stats
        leaderboard.insert(*team1);
        leaderboard.insert(*team2);
        
        cout << "\nGame Result: " << winner << " (" << winnerScore << ") defeats " 
             << loser << " (" << loserScore << ")\n";
    }
}

int main() {
    srand(time(0));
    SkipList leaderboard;
    
    // Initialize 12 teams
    vector<string> teamNames = {
        "Team Alberta", "Team Manitoba", "Team Saskatchewan",
        "Team Ontario", "Team Quebec", "Team BC",
        "Team Nova Scotia", "Team Yukon", "Team NWT",
        "Team Nunavut", "Team PEI", "Team Newfoundland"
    };
    
    cout << "===========================================\n";
    cout << "  CURLING BONSPIEL SKIP LIST SIMULATOR\n";
    cout << "===========================================\n\n";
    
    // Add all teams to leaderboard
    for (const string& name : teamNames) {
        leaderboard.insert(Team(name, 0, 0, 0));
    }
    
    cout << "Initial leaderboard (all teams 0-0):\n";
    leaderboard.display(12);
    
    // Simple menu
    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Simulate one round (6 games)\n";
        cout << "2. Display current leaderboard\n";
        cout << "3. Simulate full bonspiel (3 rounds)\n";
        cout << "4. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        if (choice == 1) {
            // Simulate 6 games (6 sheets, pair up teams)
            cout << "\n--- Simulating Round (6 games on 6 sheets) ---\n";
            for (int i = 0; i < 6; i++) {
                simulateGame(leaderboard, teamNames[i*2], teamNames[i*2 + 1]);
            }
            leaderboard.display(10);
            
        } else if (choice == 2) {
            leaderboard.display(10);
            
        } else if (choice == 3) {
            cout << "\n--- Simulating Full Bonspiel (3 rounds) ---\n";
            for (int round = 1; round <= 3; round++) {
                cout << "\n=== ROUND " << round << " ===\n";
                for (int i = 0; i < 6; i++) {
                    simulateGame(leaderboard, teamNames[i*2], teamNames[i*2 + 1]);
                }
                leaderboard.display(10);
            }
            
        } else if (choice == 4) {
            cout << "\nThanks for using the bonspiel simulator!\n";
        }
        
    } while (choice != 4);
    
    return 0;
}