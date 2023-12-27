/*
    Advent of Code 2023 - 10.12.2023

    Link to the problem: https://adventofcode.com/2023/day/10

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

#include "Pipe.h"

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
void fillGrid(std::vector<std::vector<Pipe>> &grid, std::string input, Pipe startingPipe){ // 2D vector with all the grid

    int nrows = grid.size(), ncols = grid[0].size();

    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;
            if(input[strCounter] == 'S'){
                startingPipe.setPosition(std::make_pair(i, j));
                grid[i][j] = startingPipe;
                strCounter ++;
                continue;
            }

            grid[i][j].setTile(input[strCounter]);
            grid[i][j].setDistance(INT_MAX);
            grid[i][j].setPosition(std::make_pair(i, j)); // not sure if I need this. Probably not
            strCounter ++;
        }
    }
}

/*
// This function will ONLY return the adjacent elements. Won't perform any further calculation
std::vector<Pipe> getSurroundings(Pipe currentPipe, int nrows, int ncols){

    std::pair<int, int> position = currentPipe.position;
    std::vector<Pipe> surroundings;

    std::pair<int, int> up = std::make_pair(position.first - 1, position.second);
    std::pair<int, int> down = std::make_pair(position.first + 1, position.second);
    std::pair<int, int> left = std::make_pair(position.first, position.second - 1);
    std::pair<int, int> right = std::make_pair(position.first, position.second + 1);

    if(position == std::make_pair(0, 0)){   // Top left corner

        Pipe rightPipe;
        
        surroundings.push_back(right);
        surroundings.push_back(down); 
    }
    else if(position == std::make_pair(0, ncols - 1)){  // Top right corner

        surroundings.push_back(left);
        surroundings.push_back(down); 
    }
    else if(position == std::make_pair(nrows - 1, 0)){  // Bottom left corner

        surroundings.push_back(right);
        surroundings.push_back(up); 
    }
    else if(position == std::make_pair(nrows - 1, ncols - 1)){  // Bottom right corner

        surroundings.push_back(left); 
        surroundings.push_back(up); 
    }
    else if(position.first == 0){   // First row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(down); 
    }
    else if(position.first == nrows - 1){   // Last row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(up); 
    }
    else if(position.second == 0){  // First column

        surroundings.push_back(right); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else if(position.second == ncols - 1){   // Last column

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else{   // No weird cases
        surroundings.push_back(right); 
        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    return surroundings;
}
*/


// The big boy. I want this to be a recursive function that obtains the distance for every position
void pipeMaze(Pipe currentPipe, std::vector<std::vector<Pipe>> grid){

    int nrows = grid.size(), ncols = grid[0].size();    // I could maybe pass them as parameters

    // Call an extern function to get surroundings
    //std::vector<Pipe> surroundings = getSurroundings(currentPipe, nrows, ncols);

    // For each surrounding, calculate the distance (check if it's already calculated)

    // If there are no possible jumps, end the process



    std::cout << "a";
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
    std::vector<std::vector<Pipe>> grid(nrows, std::vector<Pipe>(ncols, Pipe(' ', std::make_pair(-1, -1), 0))); // 2D vector with all the grid
    
    // Save the input in a grid
    std::pair<int, int> initialPosition = std::make_pair(-1, -1);
    Pipe startingPipe('S', initialPosition, 0);
    fillGrid(grid, input, startingPipe);

    // I guess the algorithm comes here
    pipeMaze(startingPipe, grid);


    return 0;
}