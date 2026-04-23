#ifndef SKIPLIST_H
#define SKIPLIST_H

#include "Team.h"
#include <vector>
#include <cstdlib>
#include <ctime>

const int MAX_LEVEL = 16;

struct SkipNode {
    Team data;
    vector<SkipNode*> forward;
    
    SkipNode(Team team, int level) : data(team), forward(level + 1, nullptr) {}
};

class SkipList {
private:
    SkipNode* header;
    int currentLevel;
    
    int randomLevel();
    
public:
    SkipList();
    ~SkipList();
    
    void insert(Team team);
    bool remove(string teamName);
    Team* search(string teamName);
    void display(int topN = 10);
    int size();
};

#endif