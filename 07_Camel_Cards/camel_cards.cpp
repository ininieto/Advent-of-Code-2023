/*
    Advent of Code 2023 - 07.12.2023

    Link to the problem: https://adventofcode.com/2023/day/7

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

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
int getType(std::string card){

    // Count how many times each character appears
    std::unordered_map<char, int> charCount;
    for(char c: card) charCount[c] ++;  

    switch(charCount.size()){

        case 1:         // Five of a kind
            return 7;   
        case 2:      
            for(auto mapElement: charCount){
                if(mapElement.second == 4)  
                    return 6;   // Four of a kind
            }
            return 5;   // Full house
        case 3:      
            for(auto mapElement: charCount){
                if(mapElement.second == 3)  
                    return 4;   // Three of a kind
            }
            return 3;   // Two pair
        case 4:         
            return 2;   // One pair
        case 5:         
            return 1;   // High card
    }

    // Must never reach here. Error
    return -1;
}

// Function to compare the hands and decide the winner
void camelCardsGame(std::string hand1, std::string hand2){

    // First compare the type

    // If same type, compare the labels in order (first with first, second with second...)

    // Then there is also the bid thing. I guess I should deal with std::pair<std::string hand, int bid> card

    // Then there is the rank thing: I must order all of them. Their position will be the rank

}


int main(){

    std::string example = "32T3K 765\nT55J5 684\nKK677 28\nKTJJT 220\nQQQJA 483";
    std::string input = readInputText("input.txt");

    std::vector<std::string> splittedExample = split(example, "\n");
    //std::vector<std::string> splittedInput = split(input, "\n");
    std::vector<std::string> splittedInput = splittedExample;

    // Map to assign a strengh for each card 
    std::unordered_map<char, int> strengthMap = {{'A', 14}, {'K', 13}, {'Q', 12}, {'J', 11}, {'T', 10}, {'9', 9}, {'8', 8}, {'7', 7}, {'6', 6}, {'5', 5}, {'4', 4}, {'3', 3}, {'2', 2}};


    for (std::string cardAndBid: splittedInput){

        // Separate the card and the bid
        std::string card = cardAndBid.substr(0, 5);
        int bid = stoi(cardAndBid.substr(cardAndBid.find(' ') + 1));

        getType(card);


    } 
    




    return 0;
}