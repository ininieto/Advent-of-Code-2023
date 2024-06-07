/*
    Advent of Code 2023 - 17.12.2023

    Link to the problem: https://adventofcode.com/2023/day/17
    
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
    Node* startNode = &grid[0][0]; 
    
    // Call the big function
    dijkstra(startNode, grid, nrows, ncols);

    // Check the minDistance of the endNode
    Node* endNode = &grid[ncols - 1][nrows - 1];
    std::cout << endNode->getMinDistance() << "\n\n";

    // Debug: Try to paint the lava flow with 0s
    Node* nextNode = endNode;
    while(nextNode != nullptr){
        nextNode->setHeatLoss(0);
        nextNode = nextNode->getPrevNode();
    }
    printGrid(grid);

    return 0;
}