#include <iostream>
#include <vector>

#include "Pipe.h"
#include "pipe_maze.h"
#include "utils.h"

int main(){

    std::string example = "..F7.\n.FJ|.\nSJ.L7\n|F--J\nLJ...\n";  
    std::string input = readInputText("input.txt");
    //std::string input = example;

    // Define the grid 
    int nrows = 0, ncols = 0;
    getGridDimensions(input, nrows, ncols);
    std::vector<std::vector<Pipe>> grid(nrows, std::vector<Pipe>(ncols, Pipe(' ', std::make_pair(-1, -1), 0))); // 2D vector with all the grid
    
    // Save the input in a grid
    std::pair<int, int> initialPosition = std::make_pair(-1, -1);
    Pipe startingPipe('S', initialPosition, 0);
    fillGrid(grid, input, startingPipe);

    // Vector that will contain the Pipes we want to jump to
    std::vector<Pipe> nextJumps;
    nextJumps.push_back(startingPipe);

    // Variable that will contain the biggest distance
    int biggestDistance = 0;

    // Big algorithm
    pipeMaze(startingPipe, grid, nextJumps, biggestDistance);
    printDistancesGrid(grid);

    std::cout << "The biggest distance is " << biggestDistance << '\n';

    return 0;
}