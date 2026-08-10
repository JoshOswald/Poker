#include <iostream>
#include <array>
#include <vector>
#include <string>

using namespace std;

#ifndef player
#define player

class Player{
    public:

    int playerNum;
    int chips;
    int bet;
    string name;
    std::vector<std::array<string, 2>> hand;
    int handDeg;
    bool winner;
    bool fold;
};

#endif