#include "SkipList.h"
#include <iostream>
#include <iomanip>

SkipList::SkipList() {
    currentLevel = 0;
    Team dummy("", -1, -1, -1);
    header = new SkipNode(dummy, MAX_LEVEL);
    srand(time(0));
}

SkipList::~SkipList() {
    SkipNode* current = header->forward[0];
    while (current != nullptr) {
        SkipNode* next = current->forward[0];
        delete current;
        current = next;
    }
    delete header;
}

int SkipList::randomLevel() {
    int level = 0;
    while (rand() % 2 == 0 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

void SkipList::insert(Team team) {
    vector<SkipNode*> update(MAX_LEVEL + 1);
    SkipNode* current = header;
    
    // Find position to insert
    for (int i = currentLevel; i >= 0; i--) {
        while (current->forward[i] != nullptr && 
               current->forward[i]->data > team) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    // If team exists, update it
    if (current != nullptr && current->data == team) {
        current->data = team;
        return;
    }
    
    // Insert new node
    int newLevel = randomLevel();
    if (newLevel > currentLevel) {
        for (int i = currentLevel + 1; i <= newLevel; i++) {
            update[i] = header;
        }
        currentLevel = newLevel;
    }
    
    SkipNode* newNode = new SkipNode(team, newLevel);
    for (int i = 0; i <= newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}

bool SkipList::remove(string teamName) {
    vector<SkipNode*> update(MAX_LEVEL + 1);
    SkipNode* current = header;
    
    for (int i = currentLevel; i >= 0; i--) {
        while (current->forward[i] != nullptr && 
               current->forward[i]->data.name != teamName &&
               current->forward[i]->data > Team(teamName, 0, 0, 0)) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (current == nullptr || current->data.name != teamName) {
        return false;
    }
    
    for (int i = 0; i <= currentLevel; i++) {
        if (update[i]->forward[i] != current) break;
        update[i]->forward[i] = current->forward[i];
    }
    
    delete current;
    
    while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
        currentLevel--;
    }
    
    return true;
}

Team* SkipList::search(string teamName) {
    SkipNode* current = header;
    
    for (int i = currentLevel; i >= 0; i--) {
        while (current->forward[i] != nullptr && 
               current->forward[i]->data.name != teamName) {
            current = current->forward[i];
        }
    }
    
    current = current->forward[0];
    
    if (current != nullptr && current->data.name == teamName) {
        return &(current->data);
    }
    return nullptr;
}

void SkipList::display(int topN) {
    cout << "\n========================================\n";
    cout << "     BONSPIEL LEADERBOARD\n";
    cout << "========================================\n";
    cout << left << setw(4) << "Rank" 
         << setw(20) << "Team" 
         << setw(10) << "Record"
         << setw(10) << "Points" << endl;
    cout << "----------------------------------------\n";
    
    SkipNode* current = header->forward[0];
    int rank = 1;
    
    while (current != nullptr && rank <= topN) {
        cout << left << setw(4) << rank
             << setw(20) << current->data.name
             << setw(10) << (to_string(current->data.wins) + "-" + 
                             to_string(current->data.losses))
             << setw(10) << current->data.totalPoints << endl;
        current = current->forward[0];
        rank++;
    }
    cout << "========================================\n";
}

int SkipList::size() {
    int count = 0;
    SkipNode* current = header->forward[0];
    while (current != nullptr) {
        count++;
        current = current->forward[0];
    }
    return count;
}