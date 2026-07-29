#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

#include "player.h"
//#include "check.cpp"
#include "setup.cpp"

using namespace std;

std::vector<std::array<string, 2>> createDeck();
std::vector<Player> setupPlayers(vector<std::string> playerNames, std::vector<std::array<string, 2>> deck);
void printDeck(std::vector<std::array<string, 2>> deck);
std::vector<std::array<string, 2>> shuffleDeck(std::vector<std::array<string, 2>> deck);
void intro();
std::vector<Player> deal(int numPlayers, std::vector<std::array<string, 2>> deck, std::vector<Player> players);
void printCurrentHand(std::vector<Player> players, int numPlayers);
std::vector<std::array<string, 2>> setupBoard(std::vector<std::array<string, 2>> deck);

//Clubs, Spades, Diamonds, Hearts

int main() {
    std::vector<std::array<string, 2>> deck = createDeck();
    string answer;
    bool autoSetup = true;

    //intro();
    deck = shuffleDeck(deck);

    //Debug print deck and # of cards
    printDeck(deck);

    //setupPlayers
    vector<std::string> playerNames = {"","","",""};
    int numPlayers = playerNames.size();
    std::vector<Player> players = setupPlayers(playerNames,deck);
    players = deal(numPlayers, deck, players);
    std::vector<std::array<string, 2>> board = setupBoard(deck);

    printCurrentHand(players, numPlayers);

    return 0;
}