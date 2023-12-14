/*
    Advent of Code 2023 - 04.12.2023

    Link to the problem: https://adventofcode.com/2023/day/4

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // To use sort()
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

// Simple fnuction to extract the number of the card
int getCardNumber(std::string strCard){

    strCard = strCard.substr(0, strCard.find(':'));
    strCard = strCard.substr(strCard.find(' ') + 1);

    return stoi(strCard);
}

std::vector<int> fillVector(std::string strNumbers){

    std::vector<int> numbersVector;
    std::string aux;

    for(int i = 0; i < strNumbers.length(); i++){
        if(strNumbers[i] != ' ')
            aux.push_back(strNumbers[i]);
        else{
            if(aux.length() > 0){
                numbersVector.push_back(stoi(aux));
                aux.clear();
            }
        }
    }
    numbersVector.push_back(stoi(aux));
    return numbersVector;
}

int main(){

    std::string example = readInputText("example.txt");
    std::string inputData = readInputText("input.txt");

    // Split the data
    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(inputData, "\n");
    //std::vector<std::string> splittedInput = splittedExample;

    // This map will store the result of every card. Will avoid redundances
    std::unordered_map<int, std::vector<int>> alreadySolvedCard;

    // This map will know how many copies of a Card have been created
    std::unordered_map<int, int> howManyCards;

    // Initialize the map
    int totalNumCards = splittedInput.size();
    for(int i = 0; i < splittedInput.size(); i++)   howManyCards[i + 1] = 1;

    for(int i = 0; i < splittedInput.size(); i++){

        std::string card = splittedInput[i];
        int numCard = getCardNumber(card);
        std::vector<int> coincidences = alreadySolvedCard[numCard];

        // Debug
        std::cout << splittedInput.size() << "  Card Number: " << numCard << '\n';

        if(coincidences.size() == 0){

            card = card.substr(card.find(':') + 2); // Trim the beginning of the string

            // Store the winning numbers in a vector
            std::string strWinningNumbers = card.substr(0, card.find('|') - 1);
            std::vector<int> wininnigNumbers = fillVector(strWinningNumbers);

            // Store your numbers in another vector
            std::string strMyNumbers = card.substr(card.find('|') + 2);
            std::vector<int> myNumbers = fillVector(strMyNumbers);

            // The first obvious approach is to double-for loop the arrays, but that's not very efficient. I will use
            // the built-in set_intersection() function

            // In order to use this function, the arrays must be sorted
            sort(wininnigNumbers.begin(), wininnigNumbers.end());
            sort(myNumbers.begin(), myNumbers.end());

            // Store the matching numbers in the coincidences vector
            std::set_intersection(wininnigNumbers.begin(), wininnigNumbers.end(), myNumbers.begin(), myNumbers.end(),
                                  std::back_inserter(coincidences));

            // Store the result in the map
            alreadySolvedCard[numCard] = coincidences;
        }   

        // TODO: I guess I could, in a clever way, erase unnecessary parts of the vector and simply increase the "size" in a variable

        int desiredCardNumber = numCard;

        for(int j = 0; j < coincidences.size(); j++){

            int indexJump = 0;
            desiredCardNumber ++;

            for (int l = numCard - 1; l < desiredCardNumber - 1; l++) indexJump += howManyCards[l + 1];

            splittedInput.insert(splittedInput.begin() + indexJump, splittedInput[indexJump]);
            howManyCards[desiredCardNumber]++;
        }
        // Erase the card that we've already read
        splittedInput.erase(splittedInput.begin());
        i--;    // We make sure to take the first element of the array
    }

    int finalResult = 0;
    for(int l = 0; l < totalNumCards; l++)  finalResult += howManyCards[l + 1];

    std::cout << "The result is " << finalResult << '\n';

    return 0;
}