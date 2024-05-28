/*
    Advent of Code 2023 - 16.12.2023

    Link to the problem: https://adventofcode.com/2023/day/16
    
    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

#include "Node.h"
#include "utils.h"
#include "dijkstra.h"

int main(){

   // Read the input data and example
    std::string example = "2413432311323\n3215453535623\n3255245654254\n3446585845452\n4546657867536\n1438598798454\n4457876987766\n3637877979653\n4654967986887\n4564679986453\n1224686865563\n2546548887735\n4322674655533\n";
    std::string inputData = readInputText("input.txt");
    inputData = example;    // Comment for real problem, uncomment for example

    // Store all the input in a grid
    int nrows = 0, ncols = 0;
    getGridDimensions(inputData, nrows, ncols);
    std::vector<std::vector <Node>> grid(nrows, std::vector<Node>(ncols));
    fillGrid(grid, inputData);

    // Create the root node and launch the algorithm
    Node* startNode = new Node();
    startNode = &grid[0][0];
    


    // Debug
    printGrid(grid);

    return 0;
}