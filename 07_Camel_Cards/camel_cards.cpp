/*
    Advent of Code 2023 - 07.12.2023

    Link to the problem: https://adventofcode.com/2023/day/7

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#define FIVE_OF_A_KIND 7
#define FOUR_OF_A_KIND 6
#define FULL_HOUSE 5
#define THREE_OF_A_KIND 4
#define TWO_PAIR 3
#define ONE_PAIR 2
#define HIGH_CARD 1

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
*/
int assignType(std::string hand){

    // Count how many times each character appears
    std::unordered_map<char, int> charCount;
    for(char c: hand) charCount[c] ++;  

    /*
        Depending on the number of different characters we can guess the type 
        For example, if there is just 1 different type of character, they are 
        all equal --> Five of a kind. If there are two different chars, we 
        can have either Four of a kind (AAAAJ) or Full House (AAAJJ). And so on
    */

    switch(charCount.size()){

        case 1:          
            return FIVE_OF_A_KIND;  
        case 2:      
            for(auto mapElement: charCount){
                if(mapElement.second == 4)
                    return FOUR_OF_A_KIND; 
            }
            return FULL_HOUSE;   
        case 3:      
            for(auto mapElement: charCount){
                if(mapElement.second == 3)
                    return THREE_OF_A_KIND;  
            }
            return TWO_PAIR;   
        case 4:         
            return ONE_PAIR;   
        case 5:         
            return HIGH_CARD; 
    }

    // Error. Might never reach here
    return -1;
}

// Function to compare the hands and decide the winner
void camelCardsGame(Card card, std::vector<Card> &rankVector){

    // Map to assign a strengh for each card 
    std::unordered_map<char, int> strengthMap = {{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}};
    
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
        camelCardsGame(card, rankVector);
    } 

    // Get the result
    uint64_t result = 0;
    for(int i = 0; i < rankVector.size(); i++){
        result += (rankVector[i].bid * (i + 1));
    }
    
    std::cout << "The result is " << result << '\n';

    return 0;
}