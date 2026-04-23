# CSPB2270_final-project_skip-list-bonspiel
CSPB 2270 - Final Project Repo - Spring 2026
# Skip List Bonspiel Leaderboard

A real-time curling bonspiel (tournament) leaderboard system using a skip list data structure to efficiently manage team rankings.

## Motivation

Curling bonspiels involve multiple teams competing across several sheets of ice simultaneously. As games finish at different times, organizers need to quickly update standings. This project demonstrates how skip lists provide O(log n) performance for the constant insertions, deletions, and rank queries needed in a dynamic tournament leaderboard.

Teams are ranked by wins (primary) with total points as a tiebreaker, mirroring real bonspiel standings.

## What is a Skip List?

A skip list is a probabilistic data structure that extends a linked list by adding multiple levels of "express lane" pointers. This allows for efficient searching, insertion, and deletion operations—all in O(log n) average time—without the complexity of balanced trees.

When inserting a node, coin flips determine its "tower height" (how many levels it appears in). On average, this creates a balanced structure where higher levels skip over more nodes, enabling fast traversal.

## How to Compile and Run

**Requirements:** C++ compiler with C++11 support

**Compile:**
```bash
g++ -std=c++11 main.cpp SkipList.cpp -o bonspiel
```

**Run:**
```bash
./bonspiel
```

## Demo

The program simulates a 12-team bonspiel across 6 sheets of ice.

**Menu Options:**
1. Simulate one round (6 games)
2. Display current leaderboard
3. Simulate full bonspiel (3 rounds)
4. Exit

**Sample Output:**
========================================
BONSPIEL LEADERBOARD
Rank Team                 Record    Points
1    Team Alberta         3-0       24
2    Team Manitoba        2-1       18
3    Team Saskatchewan    2-1       17
...

After each game, both teams are removed from the skip list, their records updated (wins/losses/points), and reinserted in the correct sorted position.

## Code Structure

- **Team.h**: Team data structure with comparison operators (wins descending, then points descending)
- **SkipList.h**: Skip list class declaration
- **SkipList.cpp**: Skip list implementation (insert, remove, search, display)
- **main.cpp**: Bonspiel simulator with menu system

## Technical Challenges

**[CUSTOMIZE THIS - what was hard for you? Pick 2-3:]**

1. **Implementing probabilistic level assignment**: Understanding how random coin flips create balanced structure without explicit rebalancing required careful testing of the randomLevel() function.

2. **Composite comparison function**: Sorting by wins first, then points required careful implementation of the Team comparison operators to ensure the skip list maintained correct order.

3. **Update logic**: When a game finishes, both teams must be removed, updated, and reinserted. This required search → remove → modify → insert workflow for each game.

4. **Optional: Time pressure**: Completing this project in about 20 hours over several days meant focusing on core functionality over advanced features like visualization. I had to spend time and make some notes to myself outside of the project to remember where I left off each time and what wasn't working. I wasn't able to do anything too complicated from a combination of skill level and time constraints overall, but I think it approximates what is possible and the purpose of using Skip List.

## What I Learned

Skip lists provide an elegant alternative to balanced trees for maintaining sorted data with frequent updates. The probabilistic approach is simpler to implement than red-black tree rotations while achieving similar O(log n) performance. This project demonstrated how the right data structure choice can solve real-world problems—in this case, dynamic tournament rankings.

## Future Enhancements

- Visualize skip list internal structure (showing levels/towers)
- Performance comparison: skip list vs sorted array for 100+ teams
- Multiple draws with swiss-style pairings
- Export leaderboard to file

---

**Author**: Elizabeth Thompson  
**Course**: CSPB 2270 Data Structures  - Spring 2026
**Date**: 04/23/2026