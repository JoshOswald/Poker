#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

#include "player.h"

using namespace std;

void check(int numPlayers, vector<array<string, 2>> board, vector<Player> players);
int checkHand(Player playerH, vector<array<string, 2>> board);

bool royalFlush(vector<array<string, 2>> cards);
bool straightFlush(vector<array<string, 2>> cards);
bool fourOAKind(vector<array<string, 2>> cards);
bool fullHouse(vector<array<string, 2>> cards);
bool flush(vector<array<string, 2>> cards);
bool straight(vector<array<string, 2>> cards);
bool threeOAKind(vector<array<string, 2>> cards);
bool twoPair(vector<array<string, 2>> cards);
bool onePair(vector<array<string, 2>> cards);

void merge(vector<array<string, 2>>& cards, int p, int q, int r);
void merge_sort_aux(vector<array<string, 2>>& cards, int p, int r);
void merge_sort(vector<array<string, 2>>& cards);

void check(int numPlayers, vector<std::array<string, 2>> board, vector<Player> players){
    for(int i = 0; i < numPlayers; i++){
        checkHand(players[i], board);
    }
}

//Checks individual players hand and returns a number in accordance with that hands rank
//The higher the rank the better
int checkHand(Player playerH, vector<array<string, 2>> board){
    vector<array<string, 2>> cards = board;
    cards.push_back(playerH.hand[0]);
    cards.push_back(playerH.hand[1]);
    
    if(royalFlush(cards)){
        return 9;
    }else if(straightFlush(cards)){
        return 8;
    }else if(fourOAKind(cards)){
        return 7;
    }else if(fullHouse(cards)){
        return 6;
    }else if(flush(cards)){
        return 5;
    }else if(straight(cards)){
        return 4;
    }else if(threeOAKind(cards)){
        return 3;
    }else if(twoPair(cards)){
        return 2;
    }else if(onePair(cards)){
        return 1;
    }else{
        return 0;
    }

}

bool royalFlush(vector<array<string, 2>> cards){
    //Check if cards length is large enough for Royal Flush
    int len = cards.size();
    if(len <= 4 || len > 7){
        return false;
    }
    
    //Re-orders the cards in rank from lowest to highest
    merge_sort(cards);

    for(int i = 0; i < len; i++){
        //Current acts as a counter, while also acting as check for which card is needed next
        int current = stoi(cards[i][1]) + 1;
        //If current index makes it impossible to have a Royal Flush return false
        if(i != len-4){
            //If current index is not 10 and cannot be the start of a Royal Flush then skip this index
        	if(cards[i][1] == "10"){
				for(int j = i; j < len; j++){
					//Check if current is same suit
					if(i != j && current == stoi(cards[j][1]) && cards[i][0] == cards[j][0]){
						current = current + 1;
					}
				}

				//If we have five cards in sequence return true
				if(stoi(cards[i][1]) + 5 == current){
					return true;
				} 
           }
        }else{
            return false;
        }
    }

    return false;
}

bool straightFlush(vector<array<string, 2>> cards){
    //Check if cards length is large enough for straight
    int len = cards.size();
    if(len <= 4 || len > 7){
        return false;
    }
    
	//Sorts cards in lowest to highest order
    merge_sort(cards);


    for(int i = 0; i < len; i++){
		//Current acts as a counter, while also acting as check for which card is needed next
        int current = stoi(cards[i][1]) + 1;
        //If current index makes it impossible to have a straight return false
        if(i != len-4){
           for(int j = i; j < len; j++){
				//Check if card is same suit
                if(i != j && current == stoi(cards[j][1]) && cards[i][0] == cards[j][0]){
                    current = current + 1;
                }
            }

            //If we have five cards of the same suit in sequence return true
            if(stoi(cards[i][1]) + 5 == current){
                return true;
            }
        }else{
            return false;
        }
    }

    return false;
}

bool fourOAKind(vector<array<string, 2>> cards){
    //Check if cards length is large enough for four of a kind
    int len = cards.size();
    if(len <= 3 || len > 7){
        return false;
    }
    //Check each item to see if it has four of a kind
    //Iterate on next point forward and not entire vector
    for(int i = 0; i < len; i++){
        int count = 1;
        //If current index makes it impossible to have 4 pair return false
        if(i != len-3){
           for(int j = i; j < len; j++){
                if(i != j && cards[i][1] == cards[j][1]){
                    count = count + 1;
                }
            }

            //If we have four instances of the same value return true
            if(count == 4){
                return true;
            }
        }else{
            return false;
        }
    }

    return false;
}

bool fullHouse(vector<array<string, 2>> cards){
    //Check if cards length is large enough for three of a kind
    int len = cards.size();
    if(len <= 4 || len > 7){
        return false;
    }
    //Check each item to see if it has 3 of a kind
    //Iterate on next point forward and not entire vector
    string temp;
    for(int i = 0; i < len; i++){
        int count = 1;
        temp = cards[i][1];
        //If current index makes it impossible to have 3 pair return false
        if(i != len-count){
           for(int j = i; j < len; j++){
                if(i != j && cards[i][1] == cards[j][1]){
                    count = count + 1;
                }
            }

            //If we have three instances of the same value move to next section
            if(count == 3){
                goto checkForSinglePair;
            }
        }else{
            return false;
        }
    }

checkForSinglePair:

    //Check each item and see if it has a pair
    //Iterate on next point forward and not entire vector
    for(int i = 0; i < len; i++){
		//If current index is equal to the three pair, skip this index
		if(cards[i][1] != temp){
			for(int j = i; j < len; j++){
				if(i != j && cards[i][1] == cards[j][1]){
					return true;
				}
        	}
		}
    }

    return false;
}

bool flush(vector<array<string, 2>> cards){
    //Check if cards length is large enough for flush
    int len = cards.size();
    if(len <= 4 || len > 7){
        return false;
    }
    //Check to see if cards have 5 of same suit
    //Iterate on next point forward and not entire vector
    for(int i = 0; i < len; i++){
        int count = 1;
        //If current index makes it impossible to have flush return false
        if(i != len-4){
           for(int j = i; j < len; j++){
                if(i != j && cards[i][0] == cards[j][0]){
                    count = count + 1;
                }
            }

            //If we have five instances of the same value return true
            if(count == 5){
                return true;
            }
        }else{
            return false;
        }
    }

    return false;
}

bool straight(vector<array<string, 2>> cards){
    //Check if cards length is large enough for straight
    int len = cards.size();
    if(len <= 4 || len > 7){
        return false;
    }

    vector<int> cardsArray = {};
    for(int i = 0; i < len; i++){
        cardsArray.push_back(stoi(cards[i][1]));
    }

	//Sort array of card ranks and remove duplicates
    sort(cardsArray.begin(), cardsArray.end());
    cardsArray.erase( unique( cardsArray.begin(), cardsArray.end() ), cardsArray.end() );

    len = cardsArray.size();
    if(len <= 4 || len > 7){
        return false;
    }

    int start;

    for(int i = 0; i < len; i++){

        start = i;

        int current = cardsArray[i] + 1;
        if(current == 15){
            current = 2;
            start = 0;

        }
        for(int j = start; j < len; j++){
            if(i != j && current == cardsArray[j]){
                current = current + 1;
            }
        }

        //If we have five cards in sequence return true
        if(cardsArray[i] + 5 == current){
            return true;
        }else if(current == 6 && cardsArray[i] == 14){
            return true;
        }

        /*
        if(i != len-4){
           for(int j = i; j < len; j++){
                if(i != j && current == cardsArray[j]){
                    current = current + 1;
                }
            }

            //If we have five cards in sequence return true
            if(cardsArray[i] + 5 == current){
                return true;
            }
        }else if(current == 15){
            cout << "hi" << endl;
            current = 1;
            for(int j = 0; j < len; j++){
                if(i != j && current == cardsArray[j]){
                    current = current + 1;
                }
            }

            //If we have five cards in sequence return true
            if(5 == current){
                return true;
            }
        }else{
            return false;
        }
        */
    }

    return false;
}

bool threeOAKind(vector<array<string, 2>> cards){
    //Check if cards length is large enough for three of a kind
    int len = cards.size();
    if(len <= 2 || len > 7){
        return false;
    }
    //Check each item to see if it has 3 of a kind
    //Iterate on next point forward and not entire vector
    for(int i = 0; i < len; i++){
        int count = 1;
        //If current index makes it impossible to have 3 pair return false
        if(i != len-2){
           for(int j = i; j < len; j++){
                if(i != j && cards[i][1] == cards[j][1]){
                    count = count + 1;
                }
            }

            //If we have three instances of the same value return true
            if(count == 3){
                return true;
            }
        }else{
            return false;
        }
    }

    return false;
}

bool twoPair(vector<array<string, 2>> cards){
    //Check initial card amount size
    int len = cards.size();
    if(len <= 3 || len > 7){
        return false;
    }

    //Check each item and see if it has a pair
    //Iterate on next point forward and not entire vector
    for(int i = 0; i < len; i++){
        for(int j = i; j < len; j++){
            if(i != j && cards[i][1] == cards[j][1]){
                //If a pair is found, remove from the vector
                //Then go to next section of code
                cards.erase(cards.begin() + j);
                cards.erase(cards.begin() + i);
                goto findSecondPair;
            }
        }
    }
    //If no pair is found return false
    return false;

findSecondPair:

    //Check each item and see if it has another pair besides the first one
    //Iterate on next point forward and not entire vector
    len = cards.size();
    for(int i = 0; i < len; i++){
        for(int j = i; j < len; j++){
            if(i != j && cards[i][1] == cards[j][1]){
                return true;
            }
        }
    }

    return false;
}

bool onePair(vector<array<string, 2>> cards){
    //Check if cards length is large enough for a pair
    int len = cards.size();
    if(len <= 1 || len > 7){
        return false;
    }
    //Check each item and see if it has a pair
    //Iterate on next point forward and not entire vector
    for(int i = 0; i < len; i++){
        for(int j = i; j < len; j++){
            if(i != j && cards[i][1] == cards[j][1]){
                return true;
            }
        }
    }

    return false;
}

void merge(vector<array<string, 2>>& cards, int p, int q, int r){
    int n1 = q - p + 1;
    int n2 = r - q;
    vector<array<string, 2>> L(n1);
    vector<array<string, 2>> R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = cards[p + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = cards[q + 1 + j];
    }

    L.push_back({"", "99"}); // Sentinel for L
    R.push_back({"", "99"}); // Sentinel for R

    int i = 0, j = 0;
    for (int k = p; k <= r; k++) {
        if (stoi(L[i][1]) <= stoi(R[j][1])) {
            cards[k] = L[i];
            i++;
        } else {
            cards[k] = R[j];
            j++;
        }
    }
}

void merge_sort_aux(vector<array<string, 2>>& cards, int p, int r){
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort_aux(cards, p, q);
        merge_sort_aux(cards, q + 1, r);
        merge(cards, p, q, r);
    }
}

void merge_sort(vector<array<string, 2>>& cards){
    int size = cards.size();
    merge_sort_aux(cards, 0, size - 1);
    //cout << "End of merge sort: ";
    //printDeck(cards);
}