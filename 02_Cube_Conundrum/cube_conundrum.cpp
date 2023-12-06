/*
    Advent of Code 2023 - 02.12.2023

    Link to the problem: https://adventofcode.com/2023/day/2

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

int main(){

    const int maxRed = 12, maxGreen = 13, maxBlue = 14;

    std::string example = readInputText("example.txt");
    std::string inputData = readInputText("input.txt");

    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(inputData, "\n");

    int result = 0;

    std::unordered_map<std::string, int> colorCounter = {{"blue", 0}, {"red", 0}, {"green", 0}};

    for(int i = 0; i < splittedInput.size(); i++){

        std::string game = splittedInput[i];
        game = game.substr(game.find(':') + 2); // We don't need the Game i part

        bool possibleGame = true;
        
        // Separate the cubes
        std::vector<std::string> cubes = split(game, ";");  
        for(std::string cube: cubes){
            std::vector<std::string> sets = split(cube, ",");
            for(std::string set: sets){
                if(set[0] == ' ')  set.erase(set.begin());   // Trim the string
                
                int numCubes = stoi(set.substr(0, set.find(' ')));
                std::string color = set.substr(set.find(' ') + 1);

                // Increase the color count
                colorCounter[color] += numCubes;
            }

            // Check if the set is possible
            if(colorCounter["red"] > maxRed || colorCounter["blue"] > maxBlue || colorCounter["green"] > maxGreen){
                possibleGame = false;
                // std::cout << "Game " << i + 1 << " is not possible\n";
                break;
            }

            // Reset colorCounter
            colorCounter.clear();
        }
        if(possibleGame)    result += (i + 1);
        possibleGame = true;
        colorCounter.clear();
    }

    std::cout << result << '\n';
    return 0;
}
    size_t pos = 0;