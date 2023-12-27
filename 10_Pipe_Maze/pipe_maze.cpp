/*
    Advent of Code 2023 - 10.12.2023

    Link to the problem: https://adventofcode.com/2023/day/10

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

#include "Pipe.h"
#include "utils.h"

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Pipe>> &grid, std::string input, Pipe &startingPipe){ // 2D vector with all the grid

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


// The big boy. I want this to be a recursive function that obtains the distance for every position
void pipeMaze(Pipe currentPipe, std::vector<std::vector<Pipe>> grid){

    int nrows = grid.size(), ncols = grid[0].size();    // I could maybe pass them as parameters

    // Call an extern function to get surrounding positions
    std::vector<std::pair<int, int>> surroundingPositions = getSurroundings(currentPipe, nrows, ncols);

    // Vector that will contain the Pipes we want to jump to
    std::vector<Pipe> nextJumps;

    // For each surrounding, calculate the distance (check if it's already calculated)    
    for(auto pos : surroundingPositions){
        Pipe* nextPipe = &grid[pos.first][pos.second];  // Pointer to the position of the grid

        if(possibleJump(currentPipe, *nextPipe)){
            if(currentPipe.getDistance() + 1 < nextPipe->getDistance()){
                nextPipe->setDistance(currentPipe.getDistance() + 1);    // Assign the distance of the next pipe
                std::cout << "Pipe " << nextPipe->getTile() << " in (" << nextPipe->getPosition().first << ", " << nextPipe->getPosition().second <<") has now distance " << nextPipe->getDistance() << '\n';
                nextJumps.push_back(*nextPipe);
            }
        }            
    }

    // TODO: Start with the Pipes with the lowest distance

    // Call the function again for the next pipes
    for(Pipe nextPipe: nextJumps){
        return pipeMaze(nextPipe, grid);
    }

    // If there are no possible jumps, end the process
    return;
}


int main(){

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

    // Big algorithm
    pipeMaze(startingPipe, grid);

    std::cout << "a";


    return 0;
}