/*
    Advent of Code 2023 - 04.12.2023

    Link to the problem: https://adventofcode.com/2023/day/4

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // To use sort()


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

    int finalResult = 0;

    for(std::string card: splittedInput){

        card = card.substr(card.find(':') + 2); // Trim the beginning of the string

        // Store the winning numbers in a vector
        std::string strWinningNumbers = card.substr(0, card.find('|') - 1);
        std::vector<int> wininnigNumbers = fillVector(strWinningNumbers);

        // Store your numbers in another vector
        std::string strMyNumbers = card.substr(card.find('|') + 2);
        std::vector<int> myNumbers = fillVector(strMyNumbers);

        // The first obvious approach is to double-for loop the arrays, but that's not very efficient. I will use
        // the built-in set_intersection() function

        // First, we define a third vector who will hold all the repeated numbers
        std::vector<int> coincidences;

        // In order to use this function, the arrays must be sorted
        sort(wininnigNumbers.begin(), wininnigNumbers.end());
        sort(myNumbers.begin(), myNumbers.end());

        std::set_intersection(wininnigNumbers.begin(), wininnigNumbers.end(), myNumbers.begin(), myNumbers.end(), 
                              std::back_inserter(coincidences));

        // Calculate the result
        int result = 1;

        if(coincidences.size() <= 1)    // If it's 0 or 1
            result = coincidences.size();
        else{
            for(int i = 0; i < coincidences.size() - 1; i++){
                result *= 2;
            }
        }
        finalResult += result;
    }

    std::cout << "The result is " << finalResult << '\n';

    return 0;
}