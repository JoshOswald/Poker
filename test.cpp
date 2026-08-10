#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>
#include <cmath> // Required for std::floor

#include "player.h"
#include "setup.cpp"
#include "check.cpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"      // Red text
#define GREEN   "\033[32m"      // Green text
#define YELLOW  "\033[33m"      // Yellow text
#define BLUE    "\033[34m"      // Blue text

using namespace std;

bool checkSetupPlayers();
bool checkOnePair();
bool checkTwoPair();
bool checkThreeOAKind();
bool checkFourOAKind();
bool checkFlush();
bool checkStraight();
bool checkFullHouse();
bool checkStraightFlush();
bool checkRoyalFlush();

void checkATonOfHands();

void checkRandom();

int main() {
    //vector<array<string, 2>> cards = createDeck();
    //printDeck(cards);

    //checkOnePair();
    //checkTwoPair();
    //checkThreeOAKind();
    //checkFourOAKind();
    //checkFlush();
    //checkStraight();
    //checkFullHouse();
    //checkStraightFlush();
    //checkRoyalFlush();

    checkATonOfHands();

    //checkRandom();


    return 0;
}

bool checkOnePair(){
    cout << boolalpha;

    cout << "|| Pair Test ||" << "\n\n";

    std::vector<std::array<string, 2>> deck = {{"H","2"},{"H","2"},{"H","2"},{"H","2"},{"H","2"}};
    if(onePair(deck)){
        cout << "All cards create a pair: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "All cards create a pair: " << RED << "Failed" << RESET << "\n";
    }

    deck = {{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"}};
    if(!onePair(deck)){
        cout << "No possible pair: "<< GREEN << "Passed" << RESET <<"\n";
    }else{
        cout << "No possible pair: " << RED << "Failed" << RESET << "\n";
    }

    deck = {{"H","2"},{"H","2"},{"H","4"},{"H","5"},{"H","6"}};
    if(onePair(deck)){
        cout << "Front Edge: "<< GREEN << "Passed" << RESET <<"\n";
    }else{
        cout << "Front Edge: " << RED << "Failed" << RESET << "\n";
    }

    deck = {{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","5"}};
    if(onePair(deck)){
        cout << "Back Edge: "<< GREEN << "Passed" << RESET <<"\n";
    }else{
        cout << "Back Edge: " << RED << "Failed" << RESET << "\n";
    }

    deck = {{"H","1"},{"H","2"},{"H","2"},{"H","3"},{"H","5"}};
    if(onePair(deck)){
        cout << "Middle Case: "<< GREEN << "Passed" << RESET <<"\n";
    }else{
        cout << "Middle Case: " << RED << "Failed" << RESET << "\n";
    }

    deck = {{"H","1"}};
    if(!onePair(deck)){
        cout << "Deck too short: "<< GREEN << "Passed" << RESET <<"\n";
    }else{
        cout << "Deck too short: " << RED << "Failed" << RESET << "\n";
    }

    deck = {{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"},{"H","8"}};
    try{
        onePair(deck);
        cout << "7 Cards("<< YELLOW << "Max" << RESET <<"): "<< GREEN << "Passed" << RESET <<"\n";
    }
    catch(const std::runtime_error& e){
        cout << "7 Cards("<< YELLOW << "Max" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    cout << "\n";

    return false;
}

bool checkTwoPair(){
    cout << "|| Pair Test ||" << "\n\n";

    //Only 4 cards
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","2"},{"H","1"},{"H","2"}};
    if(twoPair(deck)){
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","1"},{"H","3"}};
    if(!twoPair(deck)){
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //Only 3 cards
    deck = {{},{},{}};
    if(!twoPair(deck)){
        cout << "Below Minimum: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Below Minimum: "<< RED << "Failed" << RESET << "\n";
    }
    //7 Cards
    deck = {{"H","1"},{"H","1"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","6"}};
    if(twoPair(deck)){
        cout << "Max Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"}};
    if(!twoPair(deck)){
        cout << "Max Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //Exceed Max
    deck = {{},{},{},{},{},{},{},{}};
    if(!twoPair(deck)){
        cout << "Exceed Max: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Exceed Max: "<< RED << "Failed" << RESET << "\n";
    }

    //Mixed Pair
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","4"},{"H","6"},{"H","2"}};
    if(twoPair(deck)){
        cout << "Mixed Pair: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mixed Pair: "<< RED << "Failed" << RESET << "\n";
    }

    return false;
}

bool checkThreeOAKind(){
    cout << "|| Three of a Kind Test ||" << "\n\n";


    //min amount of cards
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","1"},{"H","1"}};
    if(threeOAKind(deck)){
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"}};
    if(!threeOAKind(deck)){
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //max amount of cards
    deck = {{"H","1"},{"H","10"},{"H","3"},{"H","10"},{"H","5"},{"H","6"},{"H","10"}};
    if(threeOAKind(deck)){
        cout << "Max amount of cards("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max amount of cards("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"}};
    if(!threeOAKind(deck)){
        cout << "Max amount of cards("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max amount of cards("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //more than max
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"}};
    if(!threeOAKind(deck)){
        cout << "More than max: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "More than max: "<< RED << "Failed" << RESET << "\n";
    }
    //less than min
    deck = {{"H","1"},{"H","1"}};
    if(!threeOAKind(deck)){
        cout << "Less than min: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than min: "<< RED << "Failed" << RESET << "\n";
    }

    //front edge
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","10"},{"H","5"},{"H","6"},{"H","10"}};
    if(threeOAKind(deck)){
        cout << "Front Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge: "<< RED << "Failed" << RESET << "\n";
    }

    //back edge
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","7"},{"H","7"},{"H","7"}};
    if(threeOAKind(deck)){
        cout << "Front Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge: "<< RED << "Failed" << RESET << "\n";
    }
    
    return false;
}

bool checkFourOAKind(){
    cout << "|| Four of a Kind Test ||" << "\n\n";


    //min amount of cards
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","1"},{"H","1"},{"H","1"}};
    if(fourOAKind(deck)){
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"}};
    if(!fourOAKind(deck)){
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //max amount of cards
    deck = {{"H","1"},{"H","10"},{"H","3"},{"H","10"},{"H","10"},{"H","6"},{"H","10"}};
    if(fourOAKind(deck)){
        cout << "Max amount of cards("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max amount of cards("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"}};
    if(!fourOAKind(deck)){
        cout << "Max amount of cards("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max amount of cards("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //more than max
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"}};
    if(!fourOAKind(deck)){
        cout << "More than max: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "More than max: "<< RED << "Failed" << RESET << "\n";
    }
    //less than min
    deck = {{"H","1"},{"H","1"},{"H","1"}};
    if(!fourOAKind(deck)){
        cout << "Less than min: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than min: "<< RED << "Failed" << RESET << "\n";
    }

    //front edge
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","5"},{"H","6"},{"H","10"}};
    if(fourOAKind(deck)){
        cout << "Front Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge: "<< RED << "Failed" << RESET << "\n";
    }

    //back edge
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","7"},{"H","7"},{"H","7"},{"H","7"}};
    if(fourOAKind(deck)){
        cout << "Front Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge: "<< RED << "Failed" << RESET << "\n";
    }
    
    return false;
}

bool checkFlush(){
    cout << "|| Flush Test ||" << "\n\n";


    //min amount of cards
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"}};
    if(flush(deck)){
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"S","5"}};
    if(!flush(deck)){
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //max amount of cards
    deck = {{"S","1"},{"H","2"},{"H","3"},{"H","4"},{"D","5"},{"H","6"},{"H","7"}};
    if(flush(deck)){
        cout << "Max amount of cards("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max amount of cards("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"S","1"},{"H","2"},{"C","3"},{"D","4"},{"D","5"},{"H","6"},{"H","7"}};
    if(!flush(deck)){
        cout << "Max amount of cards("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Max amount of cards("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }

    //more than max
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"},{"H","1"}};
    if(!flush(deck)){
        cout << "More than max: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "More than max: "<< RED << "Failed" << RESET << "\n";
    }
    //less than min
    deck = {{"H","1"},{"H","1"},{"H","1"}};
    if(!flush(deck)){
        cout << "Less than min: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than min: "<< RED << "Failed" << RESET << "\n";
    }

    //front edge
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"D","6"},{"D","7"}};
    if(flush(deck)){
        cout << "Front Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge: "<< RED << "Failed" << RESET << "\n";
    }

    //back edge
    deck = {{"D","1"},{"D","2"},{"H","3"},{"H","7"},{"H","7"},{"H","7"},{"H","7"}};
    if(flush(deck)){
        cout << "Front Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge: "<< RED << "Failed" << RESET << "\n";
    }
    
    return false;
}

bool checkStraight(){
    cout << "|| Straight Test ||" << "\n\n";
    
    //less than min
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"}};
    if(!straight(deck)){
        cout << "Less than 5 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than 5 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //more than max
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"},{"H","8"}};
    if(!straight(deck)){
        cout << "Over 7 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Over 7 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //minimum length
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"}};
    if(straight(deck)){
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","6"}};
    if(!straight(deck)){
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //maximum length && front edge
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"}};
    if(straight(deck)){
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"S","6"},{"H","7"},{"H","8"}};
    if(!straight(deck)){
        cout << "Maximum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Maximum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //back edge
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"}};
    if(straight(deck)){
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //mixed
    deck = {{"H","2"},{"H","1"},{"H","5"},{"H","4"},{"H","8"},{"H","9"},{"H","3"}};
    if(straight(deck)){
        cout << "Mixed: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mixed: "<< RED << "Failed" << RESET << "\n";
    }

    //mixed
    deck = {{"H","2"},{"H","5"},{"H","14"},{"H","4"},{"H","8"},{"H","9"},{"H","3"}};
    if(straight(deck)){
        cout << "Ace Low: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Ace Low: "<< RED << "Failed" << RESET << "\n";
    }

    return false;
}

bool checkFullHouse(){
    cout << "|| Full House ||" << "\n\n";

    //less than min
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"}};
    if(!fullHouse(deck)){
        cout << "Less than 5 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than 5 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //more than max
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","2"},{"H","2"},{"H","2"},{"H","2"}};
    if(!fullHouse(deck)){
        cout << "Less than 5 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than 5 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //front edge
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","4"}};
    if(fullHouse(deck)){
        cout << "Font Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge: "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","2"},{"H","2"},{"H","3"},{"H","4"}};
    if(fullHouse(deck)){
        cout << "Font Edge 2.0: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge 2.0: "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","1"},{"H","2"},{"H","2"},{"H","2"},{"H","3"},{"H","4"}};
    if(fullHouse(deck)){
        cout << "Font Edge 3.0: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Front Edge 3.0: "<< RED << "Failed" << RESET << "\n";
    }
    //back edge
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","3"},{"H","4"},{"H","4"},{"H","4"}};
    if(fullHouse(deck)){
        cout << "Back Edge: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Back Edge: "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","3"},{"H","3"},{"H","4"},{"H","4"}};
    if(fullHouse(deck)){
        cout << "Back Edge 2.0: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Back Edge 2.0: "<< RED << "Failed" << RESET << "\n";
    }
    //mixed case
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","3"},{"H","4"},{"H","5"},{"H","5"}};
    if(fullHouse(deck)){
        cout << "Mix("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mix("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","3"},{"H","4"},{"H","5"},{"H","5"}};
    if(fullHouse(deck)){
        cout << "Mix("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mix("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","5"},{"H","2"},{"H","1"},{"H","10"},{"H","2"},{"H","5"},{"H","2"}};
    if(fullHouse(deck)){
        cout << "Mix("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mix("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","18"},{"H","2"},{"H","9"},{"H","10"},{"H","2"},{"H","5"},{"H","2"}};
    if(!fullHouse(deck)){
        cout << "Mix("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mix("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //5 cards
    deck = {{"H","18"},{"H","2"},{"H","18"},{"H","2"},{"H","18"}};
    if(fullHouse(deck)){
        cout << "5 Cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "5 Cards:: "<< RED << "Failed" << RESET << "\n";
    }
    
    return false;
}

bool checkStraightFlush(){
    cout << "|| Straight Flush Test ||" << "\n\n";
    
    //less than min
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"}};
    if(!straightFlush(deck)){
        cout << "Less than 5 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than 5 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //more than max
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"},{"H","8"}};
    if(!straightFlush(deck)){
        cout << "Over 7 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Over 7 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //minimum length
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"}};
    if(straightFlush(deck)){
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"S","5"}};
    if(!straightFlush(deck)){
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //maximum length && front edge
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"}};
    if(straightFlush(deck)){
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"S","6"},{"H","7"},{"H","8"}};
    if(!straightFlush(deck)){
        cout << "Maximum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Maximum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //back edge
    deck = {{"H","1"},{"H","1"},{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"}};
    if(straightFlush(deck)){
        cout << "back edge("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "back edge("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //mixed
    deck = {{"H","2"},{"H","1"},{"H","5"},{"H","4"},{"H","8"},{"H","9"},{"H","3"}};
    if(straightFlush(deck)){
        cout << "Mixed: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mixed: "<< RED << "Failed" << RESET << "\n";
    }
    //ace low
    deck = {{"H","2"},{"H","5"},{"H","7"},{"H","4"},{"H","8"},{"H","3"},{"H","14"}};
    if(straightFlush(deck)){
        cout << "Ace Low: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Ace Low: "<< RED << "Failed" << RESET << "\n";
    }
    //mixed
    deck = {{"H","2"},{"H","5"},{"S","14"},{"H","4"},{"H","14"},{"H","9"},{"H","3"}};
    if(straightFlush(deck)){
        cout << "Ace Low: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Ace Low: "<< RED << "Failed" << RESET << "\n";
    }

    return false;
}

bool checkRoyalFlush(){
    cout << "|| Royal Flush Test ||" << "\n\n";
    
    //less than min
    std::vector<std::array<string, 2>> deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"}};
    if(!straightFlush(deck)){
        cout << "Less than 5 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Less than 5 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //more than max
    deck = {{"H","1"},{"H","2"},{"H","3"},{"H","4"},{"H","5"},{"H","6"},{"H","7"},{"H","8"}};
    if(!straightFlush(deck)){
        cout << "Over 7 cards: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Over 7 cards: "<< RED << "Failed" << RESET << "\n";
    }
    //minimum length
    deck = {{"H","10"},{"H","11"},{"H","12"},{"H","13"},{"H","14"}};
    if(straightFlush(deck)){
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","14"},{"H","12"},{"H","13"},{"H","14"},{"S","15"}};
    if(!straightFlush(deck)){
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Minimum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //maximum length && front edge
    deck = {{"H","14"},{"H","12"},{"H","13"},{"H","10"},{"H","11"},{"H","6"},{"H","7"}};
    if(straightFlush(deck)){
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Maximum Length("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    deck = {{"H","11"},{"H","12"},{"S","13"},{"H","10"},{"H","14"},{"H","6"},{"H","7"}};
    if(!straightFlush(deck)){
        cout << "Maximum Length("<< YELLOW << "Fail" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Maximum Length("<< YELLOW << "Fail" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //back edge
    deck = {{"H","1"},{"H","1"},{"H","10"},{"H","11"},{"H","12"},{"H","13"},{"H","14"}};
    if(straightFlush(deck)){
        cout << "back edge("<< YELLOW << "Pass" << RESET <<"): "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "back edge("<< YELLOW << "Pass" << RESET <<"): "<< RED << "Failed" << RESET << "\n";
    }
    //mixed
    deck = {{"H","12"},{"H","11"},{"H","5"},{"H","14"},{"H","10"},{"H","9"},{"H","13"}};
    if(straightFlush(deck)){
        cout << "Mixed: "<< GREEN << "Passed" << RESET << "\n";
    }else{
        cout << "Mixed: "<< RED << "Failed" << RESET << "\n";
    }

    return false;
}

bool checkSetupPlayers(){
    std::vector<std::array<string, 2>> deck = createDeck();
    int numPlayers = 4;
    string answer;
    bool autoSetup = true;

    default_random_engine eng;
    unsigned long int t = chrono::high_resolution_clock::now().time_since_epoch().count();
    eng.seed(t);

    mt19937 rng(eng());

    // 1. Obtain a random seed from the hardware
    std::random_device rd;

    // 2. Initialize the pseudo-random number generator (Twister) with the seed
    std::mt19937 g(rd());

    //intro();
    shuffleDeck(deck, g);

    //Debug print deck and # of cards
    printDeck(deck);

    vector<std::string> playerNames = {"","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","","",""};
    std::vector<Player> players;
    try {
        setupPlayers(playerNames);
        return true;
    } 
    catch (const std::runtime_error& e) {
        // Handle the error smoothly without crashing the program
        std::cerr << "Caught error: " << e.what() << '\n';
        return false;
    }
}

void checkATonOfHands(){
    vector<array<string, 2>> deck;
    vector<string> playerNames = { "Steve", "Adrian", "Charles", "Tim"};
    vector<Player> players;
    int numPlayers = 4;
    vector<array<string, 2>> board;
    int temp;

    int royalFlush = 0;
    int straightFlush = 0;
    int fourOAKind = 0;
    int fullHouse = 0;
    int flush = 0;
    int straight = 0;
    int threeOAKind = 0;
    int twoPair = 0;
    int onePair = 0;
    int pig = 0;

    int player1 = 0;
    int player2 = 0;
    int player3 = 0;
    int player4 = 0;

    int numberOfRuns = 10;

    default_random_engine eng;
    unsigned long int t = chrono::high_resolution_clock::now().time_since_epoch().count();
    eng.seed(t);

    mt19937 rng(eng());

    // 1. Obtain a random seed from the hardware
    std::random_device rd;

    // 2. Initialize the pseudo-random number generator (Twister) with the seed
    std::mt19937 g(rd());

    std::vector<std::vector<std::array<std::string, 2>>> large_vector;
    std::vector<std::vector<std::array<std::string, 2>>> larger_vector;

    std::vector<int> winner;
    int pot;
    int rem = 0;

    players = setupPlayers(playerNames);

    for(int i = 0; i < numberOfRuns; i++){
        temp = 0;
        deck = createDeck();
        shuffleDeck(deck, g);
        deal(deck,players);
        board = setupBoard(deck);

        for(int j = 0; j < numPlayers; j++){
            players[j].bet = 10;
            players[j].chips = players[j].chips - 10;

            //cout << "Player " << i << "\'s chips."<< endl;
            //cout << players[i].chips << endl;
        }

        winner = check(board, players);

        pot = 0;

        rem = rem + pot % winner.size();

        for(int j = 0; j < numPlayers; j++){
            pot = pot + players[j].bet;
            players[j].bet = 0;

            switch (players[j].handDeg) {
            case 9: royalFlush++; break;
            case 8: straightFlush++; break;
            case 7: fourOAKind++; break;
            case 6: fullHouse++; break;
            case 5: flush++; break;
            case 4: straight++; break;
            case 3: threeOAKind++; break;
            case 2: twoPair++; break;
            case 1: onePair++; break;
            default: pig++; break;
            }
        }

        for(int j = 0; j < winner.size(); j++){
            if(players[winner[j]].winner){
                players[winner[j]].chips = players[winner[j]].chips + std::floor(pot / winner.size());
            }

            cout << "\nCurrent Hand: " << i+1 << endl;
            printPlayer(players[winner[j]]);

            switch (winner[j]) {
            case 3: player4++; break;
            case 2: player3++; break;
            case 1: player2++; break;
            default: player1++; break;
            }
        }

        //players[0].hand = {{"H","14"},{"C","14"}};
        //board = {{"S","14"},{"D","12"},{"H","10"},{"C","12"},{"C","8"}};

        //vector<array<string, 2>> cards = board;
        //cards.push_back(players[0].hand[0]);
        //cards.push_back(players[0].hand[1]);
        //temp = checkHand(cards);

        //printCurrentHand(players,numPlayers);
        //printCurrentHand(players,1);

        //large_vector.push_back(players[0].hand);
        //larger_vector.push_back(board);

        /*
        switch (temp) {
            case 9: royalFlush++; break;
            case 8: straightFlush++; break;
            case 7: fourOAKind++; break;
            case 6: fullHouse++; break;
            case 5: flush++; break;
            case 4: straight++; break;
            case 3: threeOAKind++; break;
            case 2: twoPair++; break;
            case 1: onePair++; break;
            default: pig++; break;
        }
        */

    }

    //Associated with checking unique hand and unique board *does not work... kind of
    /*
    sort(large_vector.begin(), large_vector.end());
    large_vector.erase(std::unique(large_vector.begin(), large_vector.end()), large_vector.end());

    sort(larger_vector.begin(), larger_vector.end());
    larger_vector.erase(std::unique(larger_vector.begin(), larger_vector.end()), larger_vector.end());

    cout << "Unique Hands: " << large_vector.size() << endl;
    cout << "Unique Boards: " << larger_vector.size() << endl;
    */

    cout << "Royal Flush: " << royalFlush << "\n";
    cout << static_cast<double>(royalFlush) / numberOfRuns * 100 << "%\n\n";

    cout << "Straight Flush: " << straightFlush << "\n";
    cout << static_cast<double>(straightFlush) / numberOfRuns * 100 << "%\n\n";

    cout << "Four of A Kind: " << fourOAKind << "\n";
    cout << static_cast<double>(fourOAKind) / numberOfRuns * 100 << "%\n\n";

    cout << "Full House: " << fullHouse << "\n";
    cout << static_cast<double>(fullHouse) / numberOfRuns * 100 << "%\n\n";

    cout << "Flush: " << flush << "\n";
    cout << static_cast<double>(flush) / numberOfRuns * 100 << "%\n\n";

    cout << "Straight: " << straight << "\n";
    cout << static_cast<double>(straight) / numberOfRuns * 100 << "%\n\n";

    cout << "Three Of A Kind: " << threeOAKind << "\n";
    cout << static_cast<double>(threeOAKind) / numberOfRuns * 100 << "%\n\n";

    cout << "Two Pair: " << twoPair << "\n";
    cout << static_cast<double>(twoPair) / numberOfRuns * 100 << "%\n\n";

    cout << "One Pair: " << onePair << "\n";
    cout << static_cast<double>(onePair) / numberOfRuns * 100 << "%\n\n";

    cout << "Pig: " << pig << "\n";
    cout << static_cast<double>(pig) / numberOfRuns * 100 << "%\n\n";

    //Print out player results
    cout << "\033[4mPlayer results:\033[0m" << endl;
    cout << "Player 1: " << endl;
    cout << "Hands won: " << player1 << endl;
    cout << "Chips: " << players[0].chips << endl;

    cout << "Player 2: " << endl;
    cout << "Hands won: " << player2 << endl;
    cout << "Chips: " << players[1].chips << endl;

    cout << "Player 3: " << endl;
    cout << "Hands won: " << player3 << endl;
    cout << "Chips: " << players[2].chips << endl;

    cout << "Player 4: " << endl;
    cout << "Hands won: " << player4 << endl;
    cout << "Chips: " << players[3].chips << endl;

    //Print out remainder chips
    cout << "\n\033[4mRemaining chips:\033[0m" << endl;
    cout << rem << endl;

}

void checkRandom(){

    std::random_device dev;
    std::mt19937 rng(dev());

    for(int i = 0; i < 10; i++){
        std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6); // distribution in range [1, 6]

        std::cout << dist6(rng) << std::endl;
    }


}