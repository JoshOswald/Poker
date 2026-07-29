#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>

#include "player.h"

using namespace std;

vector<array<string, 2>> createDeck();
vector<Player> setupPlayers(vector<string> playerNames);
void printDeck(vector<array<string, 2>> deck);
void shuffleDeck(vector<array<string, 2>>& deck);
void intro();
void deal(vector<array<string, 2>> deck, vector<Player>& players);
void printCurrentHand(vector<Player> players, int numPlayers);
vector<array<string, 2>> setupBoard(vector<array<string, 2>> deck);

//Creates deck of 52 cards, ranked from 2 to 14
//14 Representing an ACE high in Texas Hold em
//C = Clubs, S = Spades, D = Diamonds, H = Hearts
vector<array<string, 2>> createDeck(){
    vector<array<string, 2>> deck;
    for(int i = 0; i < 4; i++){
        for(int j = 2; j < 15; j++){
            string temp2 = to_string(j);
            array<string, 2> temp;
            if(i == 0){
                temp = {"C",to_string(j)};
            }
            if(i == 1){
                temp = {"S",to_string(j)};
            }
            if(i == 2){
                temp = {"D",to_string(j)};
            }
            if(i == 3){
                temp = {"H",to_string(j)};
            }
            deck.push_back(temp);
        }
    }
    return deck;
}

//Creates Player Objects
//Gives player names in order of supplied strings
//Numbers players 0 to (number of players - 1)
vector<Player> setupPlayers(vector<string> playerNames){
    int numPlayers = playerNames.size();

    if(numPlayers > 22){
        throw std::runtime_error("Too many players.");
    }

    vector<Player> players;
    Player temp;
    for(int i = 0; i < numPlayers; i++){
        temp.playerNum = i;
        temp.chips = 5000;
        temp.name = playerNames[i];
        players.push_back(temp);
    }
    return players; 
}

//Deals 2 cards to each players object
//Deals 1 card to each player and loops over again
//Removes used cards from deck vector
void deal(vector<array<string, 2>> deck, vector<Player>& players){
    int numPlayers = players.size();
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < numPlayers; j++){
            players[j].hand.push_back(deck[0]);
            deck.erase(deck.begin());
        }
    }
}

//Returns the river, run, and flop as one vector
//Removes cards from deck
vector<array<string, 2>> setupBoard(vector<array<string, 2>> deck){
    vector<array<string, 2>> board;
    for(int i = 0; i < 2; i++){
        board.push_back(deck[0]);
        deck.erase(deck.begin());
    }
    return board;
}

//Prints all cards on deck in order, along with providing the number of cards
void printDeck(vector<array<string, 2>> deck){
    for (array<string, 2> x : deck) {
        cout << x[0] << " " << x[1] << "  ";
    }
    cout << "\n" << "Length of vector: " << deck.size() << endl;
}

//Look over when running***
void printCurrentHand(vector<Player> players, int numPlayers){
    for(int i = 0; i < numPlayers; i++){
        if(players[i].playerNum == 1876031856){
            cout << "test";
        }
        cout << "Player No: " << players[i].playerNum << "\n" <<"Player Cards: " << "\n"; 
        cout << players[i].hand[0][0] << " " << players[i].hand[0][1] << "\n";
        cout << players[i].hand[1][0] << " " << players[i].hand[1][1] << "\n";
    }
}

//Takes newly created deck of cards and shuffles them
//DOES NOT WORK, need to edit or change random seed generation again
void shuffleDeck(vector<array<string, 2>>& deck){

    default_random_engine eng;
    unsigned long int t = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    eng.seed(t);

    std::mt19937 rng(eng());

    std::shuffle(std::begin(deck), std::end(deck), rng);
}


void intro(){
    string answer;
    cout << "Welcome to Oswald's Poker Lounge and Bar!" << "\n" << "Manual setup: \"Yes\" or \"No\"?" << "\n";
    cin >> answer;
    
    std::string inputString = "WhatEver", cleanString;
    for (char & c : answer)
        if (c != ' ')
            cleanString += tolower(static_cast<unsigned char>(c));

    if(cleanString == "yes"){}
    if(cleanString == "no"){}
}