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

    std::string example  = "LR\n\n11A = (11B, XXX)\n11B = (XXX, 11Z)\n11Z = (11B, XXX)\n22A = (22B, XXX)\n22B = (22C, 22C)\n22C = (22Z, 22Z)\n22Z = (22B, 22B)\nXXX = (XXX, XXX)";
   std::string input = readInputText("input.txt");

    // Split the inputs
    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(input, "\n");
    //std::vector<std::string> splittedInput = splittedExample;
    
    // Instruction to follow (left, right, left...)
    std::string instructions = splittedInput[0];

    // Vector with all the starting points and all the end points
    std::vector<std::string> currentPositions;
    std::vector<std::string> endPoints;

    // Store the network in a map
    std::unordered_map<std::string, Direction> network;
    for(int i = 2; i < splittedInput.size(); i++){

        std::string line = splittedInput[i];
        Direction dir;

        // Get the Key (three first characters)
        std::string key = line.substr(0, 3);

        // If necessary, add key to the starting/end - Points
        if(key[2] == 'A')
            currentPositions.push_back(key);
        else if(key[2] == 'Z')
            endPoints.push_back(key);

        // Get the two possible directions
        dir.left = line.substr(line.find('(') + 1, 3);
        dir.right = line.substr(line.find(',') + 2, 3);

        // Store in map
        network[key] = dir;
    }

    int instructionsCounter = 0;        // Variable to iterate the instructions position we're reading 
    int numSteps = 0;                   // Variable to count the steps until we reach the end

    bool allPathsFinished = false;      // Will be true when ALL the paths reached the end

    /*
        I've thought of a more elegant approach. For every number I could guess how many steps does it take for it
        to reach an end node. With that information I could get an lcm between all of them

        endPositionFound[0] --> For first path. It is a vector as well because there might be more than one possibility

        We have that:
            - Path 0: Finds QGZ after 16579 steps
            - Path 1: Finds JVZ after 18827 steps
            - Path 2: Finds ZZZ after 19951 steps
            - Path 3: Finds VQZ after 12083 steps
            - Path 4: Finds JNZ after 22199 steps
            - Path 5: Finds MGZ after 17141 steps

        The Least Common Multiple of them all is 16342438708751 --> Our solution
        Sorry but I'm not coding the LCM lol, there are several resources online :)
    */
   std::vector<std::vector<std::pair<std::string, int>>> endPositionFound(currentPositions.size());

    // Big loop
    while(!allPathsFinished){

        // If all the instructions have been read, restart reading 
        if(instructionsCounter == instructions.size())
            instructionsCounter %= instructions.size();
        
        char nextMove = instructions[instructionsCounter];

        // We assume all paths finished. If then we find that AT LEAST one of the paths is not finished, will be set again to false
        allPathsFinished = true;

        // Obtain new position for all the possible paths
        for(int pathsCounter = 0; pathsCounter < currentPositions.size(); pathsCounter ++){
            currentPositions[pathsCounter] = (nextMove == 'L') ? network.at(currentPositions[pathsCounter]).left : network.at(currentPositions[pathsCounter]).right;
            
            // To test the mcm thing
            if(currentPositions[pathsCounter][2] == 'Z')
                endPositionFound[pathsCounter].push_back(std::make_pair(currentPositions[pathsCounter], numSteps + 1));

            // Note that if ANY of the paths is not finished, the condition will still be false
            if(currentPositions[pathsCounter][2] != 'Z')
                allPathsFinished = false;
        }

        // Increase the counters
        instructionsCounter ++;
        numSteps ++;
    }

    return 0;
}