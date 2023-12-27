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
void fillGrid(std::vector<std::vector<Pipe>> &grid, std::string input, Pipe &startingPipe){

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
void pipeMaze(Pipe currentPipe, std::vector<std::vector<Pipe>> grid, std::vector<Pipe> nextJumps, int &biggestDistance){

    nextJumps.erase(nextJumps.begin()); // Delete the current pipe from the vector

    int nrows = grid.size(), ncols = grid[0].size();    // I could maybe pass them as parameters

    // Call an extern function to get surrounding positions
    std::vector<std::pair<int, int>> surroundingPositions = getSurroundings(currentPipe, nrows, ncols);

    // For each surrounding, calculate the distance (check if it's already calculated)    
    for(auto pos : surroundingPositions){
        Pipe* nextPipe = &grid[pos.first][pos.second];  // Pointer to the position of the grid

        if(possibleJump(currentPipe, *nextPipe)){
            if(currentPipe.getDistance() + 1 < nextPipe->getDistance()){
                nextPipe->setDistance(currentPipe.getDistance() + 1);    // Assign the distance of the next pipe
                biggestDistance = (nextPipe->getDistance() > biggestDistance) ? nextPipe->getDistance() : biggestDistance;
                //std::cout << "Pipe " << nextPipe->getTile() << " in (" << nextPipe->getPosition().first << ", " << nextPipe->getPosition().second <<") has now distance " << nextPipe->getDistance() << '\n';
                addNextJump(nextJumps, *nextPipe);
            }
        }            
    }

    // Debug
    //printDistancesGrid(grid);

    // Call the function again for the next pipes
    for(Pipe nextPipe: nextJumps){
        return pipeMaze(nextPipe, grid, nextJumps, biggestDistance);
    }
}


