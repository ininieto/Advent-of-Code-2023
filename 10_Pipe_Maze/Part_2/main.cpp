#include <iostream>
#include <vector>

#include "Pipe.h"
#include "pipe_maze.h"
#include "utils.h"

int main(){

    std::string example = "..F7.\n.FJ|.\nSJ.L7\n|F--J\nLJ...\n";  
    std::string example2 = "FF7FSF7F7F7F7F7F---7\nL|LJ||||||||||||F--J\nFL-7LJLJ||||||LJL-77\nF--JF--7||LJLJIF7FJ-\nL---JF-JLJIIIIFJLJJ7\n|F|F-JF---7IIIL7L|7|\n|FFJF7L7F-JF7IIL---7\n7-L-JL7||F7|L7F-7F7|\nL.L7LFJ|||||FJL7||LJ\nL7JLJL-JLJLJL--JLJ.L\n";
    std::string example3 = ".F----7F7F7F7F-7....\n.|F--7||||||||FJ....\n.||.FJ||||||||L7....\nFJL7L7LJLJ||LJ.L-7..\nL--J.L7...LJS7F-7L7.\n....F-J..F7FJ|L7L7L7\n....L7.F7||L7|.L7L7|\n.....|FJLJ|FJ|F7|.LJ\n....FJL-7.||.||||...\n....L---J.LJ.LJLJ...\n";
    //std::string input = readInputText("input.txt");
    std::string input = example3;

    // Define the grid 
    int nrows = 0, ncols = 0;
    getGridDimensions(input, nrows, ncols);
    std::vector<std::vector<Pipe>> grid(nrows, std::vector<Pipe>(ncols, Pipe(' ', std::make_pair(-1, -1), 0))); // 2D vector with all the grid
    
    // Save the input in a grid
    std::pair<int, int> initialPosition = std::make_pair(-1, -1);
    Pipe* startingPipe = new Pipe('S', initialPosition, 0);
    fillGrid(grid, input, *startingPipe);

    // Call the algorithm
    int biggestDistance = pipeMaze(startingPipe, grid);

    // Draw the loop in the grid (assign every tile a * or a ., depending on if they belong to the loop or not)
    drawLoopInGrid(grid);

    // Count the number of outer tiles. Must be done in two times, as there is a hole in the middle
    int numOuterTiles1 = countOuterTiles(grid, std::make_pair(0, 0));
    //int numOuterTiles2 = countOuterTiles(grid, std::make_pair(70, 70)); // For real problem set to (70, 70)
    int numOuterTiles2 = countOuterTiles(grid, std::make_pair(0, ncols - 1));
    int numOuterTiles3 = countOuterTiles(grid, std::make_pair(nrows - 1, 0));
    int numOuterTiles4 = countOuterTiles(grid, std::make_pair(nrows - 1, ncols - 1));
    
    // Count the tiles that form the loop
    int numLoopTiles = countLoopTiles(grid);

    // Obtain the number of tiles inside the loop
    int totalNumTiles = nrows * ncols;
    int numInnerTiles = totalNumTiles - numOuterTiles1 - numOuterTiles2 - numOuterTiles3 - numOuterTiles4 - numLoopTiles;

    // Print the grid
    printGrid(grid);

    // 31.12.2023 - I got a result of 396 and it is too low

    std::cout << "The number of inner tiles is " << numInnerTiles << '\n';

    return 0;
}