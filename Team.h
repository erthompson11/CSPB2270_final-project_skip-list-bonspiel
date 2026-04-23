#ifndef TEAM_H
#define TEAM_H

#include <string>
using namespace std;

struct Team {
    string name;
    int wins;
    int losses;
    int totalPoints;
    
    Team(string n = "", int w = 0, int l = 0, int pts = 0) 
        : name(n), wins(w), losses(l), totalPoints(pts) {}
    
    // Comparison: sort by wins (descending), then points (descending)
    bool operator>(const Team& other) const {
        if (wins != other.wins) {
            return wins > other.wins;
        }
        return totalPoints > other.totalPoints;
    }
    
    bool operator<(const Team& other) const {
        if (wins != other.wins) {
            return wins < other.wins;
        }
        return totalPoints < other.totalPoints;
    }
    
    bool operator==(const Team& other) const {
        return name == other.name;
    }
};

#endif