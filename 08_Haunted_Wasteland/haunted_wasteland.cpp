/*
    Advent of Code 2023 - 08.12.2023

    Link to the problem: https://adventofcode.com/2023/day/8

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Direction{

    std::string left;
    std::string right;
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

int main(){

    std::string example1  = "RL\n\nAAA = (BBB, CCC)\nBBB = (DDD, EEE)\nCCC = (ZZZ, GGG)\nDDD = (DDD, DDD)\nEEE = (EEE, EEE)\nGGG = (GGG, GGG)\nZZZ = (ZZZ, ZZZ)";
    std::string example2  = "LLR\n\nAAA = (BBB, BBB)\nBBB = (AAA, ZZZ)\nZZZ = (ZZZ, ZZZ)";
    std::string input = readInputText("input.txt");

    // Split the inputs
    std::vector<std::string> splittedExample1 = split(example1, "\n");
    std::vector<std::string> splittedExample2 = split(example2, "\n");
    std::vector<std::string> splittedInput = split(input, "\n");
    //std::vector<std::string> splittedInput = splittedExample2;
    

    // Instruction to follow (left, right, left...)
    std::string instructions = splittedInput[0];

    // Store the network in a map
    std::unordered_map<std::string, Direction> network;
    for(int i = 2; i < splittedInput.size(); i++){

        std::string line = splittedInput[i];
        Direction dir;

        // Get the Key (three first characters)
        std::string key = line.substr(0, 3);

        // Get the two possible directions
        dir.left = line.substr(line.find('(') + 1, 3);
        dir.right = line.substr(line.find(',') + 2, 3);

        // Store in map
        network[key] = dir;
    }

    // Define starting and end point
    std::string startinPoint = "AAA";
    std::string endPosition  = "ZZZ";
    std::string currentPosition = startinPoint;

    int counter = 0;
    int numSteps = 0;

    // Big loop
    while(currentPosition != endPosition){

        // If all the instructions have been read, restart reading 
        if(counter == instructions.size())
            counter = counter % (instructions.size());

        char nextMove = instructions[counter];
        currentPosition = (nextMove == 'L') ? network.at(currentPosition).left : network.at(currentPosition).right;
        counter ++;
        numSteps ++;
    }

    std::cout << "The result is " << numSteps << '\n';

    return 0;
}