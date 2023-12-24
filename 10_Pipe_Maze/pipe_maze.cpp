/*
    Advent of Code 2023 - 10.12.2023

    Link to the problem: https://adventofcode.com/2023/day/10

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

// Every pipe will have its position and its distance
struct Pipe{

    std::pair<int, int> position;   // not sure if I need this. Probably not    
    char tile;  // Will contain the character (F, 7, |, ...)
    int distance;
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

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Pipe>> &grid, std::string input, std::pair<int, int> &startingPosition){ // 2D vector with all the grid

    int nrows = grid.size(), ncols = grid[0].size();

    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;
            if(input[strCounter] == 'S')
                startingPosition = std::make_pair(i, j);

            grid[i][j].tile = input[strCounter];
            grid[i][j].distance = INT_MAX;
            grid[i][j].position = std::make_pair(i, j); // not sure if I need this. Probably not
            strCounter ++;
        }
    }
}

// The big boy. I want this to be a recursive function that obtains the distance for every position
void pipeMaze(std::pair<int, int> startingPosition, std::vector<std::vector<Pipe>> grid){


    // Call an extern function to get boundaries
    // For each boundary, calculate the distance (check if it's already calculated)
    // If there are no possible jumps, end the process
}


int main(){

    /*
        - Read the input
        - Store every character in a grid
        - When doing so, find where the S is and save its position in startPosition
        - Then comes the algorithm
        - Scan all the adjacent characters (luckily no diagonal movement)
        - Define a function isPossibleConnection() to see if we can jump to a specific position
        - Not sure if, first of all, I should find the loop and discard the rest
        - Still unsure about how to determine the distance. Maybe I could create a class Pipe with its 
          inherited subclasses (all the possible positions of the pipe) and with a member variable "distance"
          I find it a bit too over-engineering but could be a way to refresh subclasses    
    */

    std::string example = "..F7.\n.FJ|.\nSJ.L7\n|F--J\nLJ...";  
    //std::string input = readInputText("input.txt");
    std::string input = example;

    // TODO: Guess the values automatically
    int nrows = 5, ncols = 5;
    std::vector<std::vector<Pipe>> grid(nrows, std::vector<Pipe>(ncols)); // 2D vector with all the grid
    
    // Save the input in a grid
    std::pair<int, int> startingPosition;   // Will contain the position of S, the point from which we start counting the distance
    fillGrid(grid, input, startingPosition);

    // I guess the algorithm comes here
    pipeMaze(startingPosition, grid);



    std::cout << "a";

    return 0;
}