/*
    Advent of Code 2023 - 07.12.2023

    Link to the problem: https://adventofcode.com/2023/day/7

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Card{

    std::string hand;
    int type;
    int bid;
};

// Function to split a std::string by a specific delimitator
std::vector<std::string> split(std::string text, std::string delim){

    std::vector<std::string> splittedText;
    size_t pos = 0;
    std::string token;

    while((pos = text.find(delim)) != std::string::npos){
        token = text.substr(0, pos);
        splittedText.push_back(token);
        text.erase(0, pos + delim.length());
    }

    if(text.length() > 0)
        splittedText.push_back(text);

    return splittedText;
}

// Read input data from txt file
std::string readInputText(std::string inputText){

    std::fstream inputfile;
    std::string inputData;

    inputfile.open(inputText, std::ios::in);
    if (inputfile.is_open()){
        std::string tp;
        while (getline(inputfile, tp)){
            inputData += tp;
            inputData += "\n";
        }
    }
    return inputData;
}


/*
    Function to determine the type of a hand. The strenght order is as follows.

    7: Five of a kind: If all equal (AAAAA)
    6: Four of a kind: If four equal (AAAAQ)
    5: Full house: Three cards equal, two cards equal (AA3A3)
    4: Three of a kind: Three equal (T9T8T)
    3: Two pair: Two shared labels (AKAK5)
    2: One pair: (56758)
    1: High card: No repeated cards (12345)

    Brief explanation about the Jokers: I've thought all the different cases separately
    
    - Five of a kind (JJJJJ) --> Stays as Five of a Kind
    - Four of a kind (JJJJA, AAAAJ) --> Becomes Five of a Kind
    - Full House (JJJAA, AAAJJ) --> Becomes Five of a Kind
    - Three of a kind (JJJAB, AAAJB) --> Becomes Four of a Kind
    - Two Pair (JJAAB) --> Four of a kind // (AABBJ) Full House
    - One Pair (JJABC, AAJBC) --> Becomes Three of a Kind
    - High card (1234J) --> Becomes One Pair
*/
int assignType(std::string hand){

    // Count how many times each character appears
    std::unordered_map<char, int> charCount;
    int numJokers = 0;
    for(char c: hand){
        if(c == 'J')
            numJokers ++;
       charCount[c] ++;
    }
    
    switch(charCount.size()){

        case 1:          
            return 7;   // Five of a kind
        case 2:      
            for(auto mapElement: charCount){
                if(mapElement.second == 4 && numJokers == 0)
                    return 6;   // Four of a kind
                else if(mapElement.second == 4 && numJokers > 0)
                    return 7;   // Becomes Five of a kind 
            }
            if(numJokers > 0)
                return 7;   // Becomes Five of a kind
            return 5;   // Full house
        case 3:      
            for(auto mapElement: charCount){
                if(mapElement.second == 3 && numJokers == 0)
                    return 4;   // Three of a kind
                else if (mapElement.second == 3 && numJokers > 0)
                    return 6;   // Becomes Four of a kind
            }
            if(numJokers == 2)
                return 6;   // Becomes Four of a kind
            else if(numJokers == 1)
                return 5;   // Becomes Full house
            else
                return 3;   // Two pair
        case 4: 
            if(numJokers > 0)
                return 4;   // Becomes Three of a kind
            else        
                return 2;   // One pair
        case 5:       
            if(numJokers == 1) 
                return 2;   // Becomes One Pair 
            return 1;   // High card
    }

    // Error
    return -1;
}

// Function to compare the hands and get the rank
void camelCardsGame(Card card, std::vector<Card> &rankVector, std::unordered_map<char, int> strengthMap){

    // First element
    if(rankVector.size() == 0){  
        rankVector.push_back(card);
        return;
    }

    // Compare the card with all of the vector
    for(int i = 0; i < rankVector.size(); i++){

        Card vecCard = rankVector[i];

        // I want them in ascendent order, so its index is (rank - 1)
        if(card.type < vecCard.type){
            rankVector.insert(rankVector.begin() + i, card);
            return;
        }
        else if(card.type == vecCard.type){ // Must compare char by char
            for(int j = 0; j < 5; j++){
                if (strengthMap.at(card.hand[j]) > strengthMap.at(vecCard.hand[j])) // Must check the next card in the vector
                    break;
                else if (strengthMap.at(card.hand[j]) == strengthMap.at(vecCard.hand[j]))   // Must check the next char in the hand
                    continue;
                else{   // Insert in the vector
                    rankVector.insert(rankVector.begin() + i, card);
                    return;
                }
            }
        }
    }
    // If it's the smallest, just add it at the end
    rankVector.push_back(card);
}


int main(){

    std::string example = "32T3K 765\nT55J5 684\nKK677 28\nKTJJT 220\nQQQJA 483";
    std::string input = readInputText("input.txt");

    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(input, "\n");
    //std::vector<std::string> splittedInput = splittedExample;

    // Map to assign a strengh for each card 
    std::unordered_map<char, int> strengthMap = {{'A', 13}, {'K', 12}, {'Q', 11}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}, {'J', 1}};

    // Vector that will order the cards to get the rank
    std::vector<Card> rankVector;

    for (std::string cardAndBid: splittedInput){

        Card card;

        // Store the hand and the bid
        card.hand = cardAndBid.substr(0, 5);
        card.bid = stoi(cardAndBid.substr(cardAndBid.find(' ') + 1));

        // Assign every card with its type
        card.type = assignType(card.hand);

        // Insert the card in the rank vector
        camelCardsGame(card, rankVector, strengthMap);
    } 

    // Get the result
    uint64_t result = 0;
    for(int i = 0; i < rankVector.size(); i++){
        result += (rankVector[i].bid * (i + 1));
    }

    std::cout << "The result is " << result << '\n';

    return 0;
}