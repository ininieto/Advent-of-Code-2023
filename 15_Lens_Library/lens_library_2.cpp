/*
    Advent of Code 2023 - 15.12.2023

    Link to the problem: https://adventofcode.com/2023/day/15
    
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
        }
    }
    return inputData;
}

// Function that calculates the hash
int hash(std::string word){

    int currentValue;

    // For every character
    for (char c : word){

        // Get the ascii code
        currentValue += (int)c;

        // Multiply by 17
        currentValue *= 17;

        // Remainder of 256
        currentValue %= 256;
    }

    return currentValue;
}

int main(){

    // Save the example and the input in variables
    //std::string example = "HASH";
    std::string example = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7";
    std::string input = readInputText("input.txt");

    // Debug
    input = example;

    // Split the input by commas
    std::vector<std::string> splittedInput = split(input, ",");

    // Define the hashmaps
    std::unordered_map<std::string, int> labelToBoxNum;
    std::unordered_map<int, std::vector<std::pair<std::string, int>>> boxesMap;

    // Big loop
    for(std::string word: splittedInput){

        // Extract the label and the operation
        std::string label = (word.find('=') != std::string::npos) ? word.substr(0, word.find('=')) : word.substr(0, word.find('-'));
        char operation = (word.find('=') != std::string::npos) ? '=' : '-';
        
        // Get the box number by its HASH
        int boxNum = hash(label);

        // Perform the operation
        if(operation == '-'){

            


        }
        else{


        }

    }



    return 0;
}