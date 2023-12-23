/*
    Advent of Code 2023 - 10.12.2023

    Link to the problem: https://adventofcode.com/2023/day/10

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


int main(){

    /*
        - Read the input
        - Store every character in a grid
        - When doing so, find where the S is and save its position in startPosition
        - Then comes the algorithm
        - Scan all the adjacent characters (luckily no diagonal movement)
        - Define a function isPossibleConnection() to see if we can jump to a specific position
        - Still unsure about how to determine the distance. Maybe I could create a class Pipe with its 
          inherited subclasses (all the possible positions of the pipe) and with a member variable "distance"
          I find it a bit too over-engineering but could be a way to refresh subclasses    
    */

    std::string example = "..F7.\n.FJ|.\nSJ.L7\n|F--J\nLJ...";  
    //std::string input = readInputText("input.txt");
    std::string input = example;

    // TODO: Guess the values automatically
    int nrows = 5, ncols = 5;
    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols)); // 2D vector with all the grid
    std::pair<int, int> startingPosition;


    // Save the input in a grid
    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;
            if(input[strCounter] == 'S')
                startingPosition = std::make_pair(i, j);

            grid[i][j] = input[strCounter];
            strCounter ++;
        }
    }

    std::cout << "a";

    return 0;
}