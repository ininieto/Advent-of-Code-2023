/*
    Advent of Code 2023 - 03.12.2023

    Link to the problem: https://adventofcode.com/2023/day/3

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

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

// Debug function to print the grid
void printGrid(std::vector<std::vector<char>> grid){
    
    std::cout << std::endl;

    for (auto row : grid){
        for (auto element : row)
            std::cout << element;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Function that 
int main(){

    std::string example = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
    std::string inputData = readInputText("input.txt");

    // Split the data
    std::vector<std::string> splittedExample = split(example, "\n");
    //std::vector<std::string> splittedInput = split(example, "\n");
    std::vector<std::string> splittedInput = splittedExample;
    
    // Store the data in a grid
    int high = splittedInput.size(), wide = splittedInput[0].size();
    std::vector<std::vector<char>> grid(high, std::vector<char>(wide));

    // Store the data in a grid
    int i = 0;
    for(auto &row: grid){
        for(auto &element: row){
            
            if(example[i] == '\n') i++;
            element = example[i];
            i++;
        }
    }

   // Read the grid looking for symbols. If found, check surroundings. If digit found, try to read the whole number (somehow)
    for(std::string row: splittedInput){
        for(char c: row){
            if(!isdigit(c) && c != '.'){    // Symbol detected
                // surroundings = getSurroundings()
                // checkSurroundings(surroundings)
            }
        }
    }

    return 0;
}
