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


// The big boy. First was implemented as a recursive function, but it was consuming too much memory. A queue had to be implemented
int pipeMaze(Pipe startingPipe, std::vector<std::vector<Pipe>> &grid) {

    int nrows = grid.size();
    int ncols = grid[0].size();

    // Variable with the biggest distance
    int biggestDistance = 0;

    // Vector with the possible next pipes to scan
    std::vector<Pipe> pipeVector;

    // Initialize the distance of the starting pipe
    pipeVector.push_back(startingPipe);

    while (!pipeVector.empty()) {

        Pipe currentPipe = pipeVector[0];
        pipeVector.erase(pipeVector.begin());

        // Call an extern function to get surrounding positions
        std::vector<std::pair<int, int>> surroundingPositions = getSurroundings(currentPipe, nrows, ncols);

        // For each surrounding, calculate the distance and add to pipeVector
        for (auto pos : surroundingPositions) {
            Pipe *nextPipe = &grid[pos.first][pos.second];

            if (possibleJump(currentPipe, *nextPipe)) {
                if (currentPipe.getDistance() + 1 < nextPipe->getDistance()) {
                    nextPipe->setDistance(currentPipe.getDistance() + 1);
                    biggestDistance = (nextPipe->getDistance() > biggestDistance) ? nextPipe->getDistance() : biggestDistance;
                    std::cout << "Pipe " << nextPipe->getTile() << " in (" << nextPipe->getPosition().first << ", " << nextPipe->getPosition().second << ") has now distance " << nextPipe->getDistance() << '\n';
                    addNextJump(pipeVector, *nextPipe);
                }
            }
        }
    }
    return biggestDistance;
}

