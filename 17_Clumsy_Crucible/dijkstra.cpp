#include "dijkstra.h"
#include "Node.h"
#include "utils.h"

#include <iostream>
#include <vector>

// Check the surroundings of the current node and decide which ones are eligible to jump into
std::vector<Node*> getPossibleJumps(Node* currentNode, Node* prevNode, std::vector<std::vector <Node>> &grid){

    std::vector<Node*> possibleJumps;   // This vector will contain all the jump-able nodes 

    // Base case: first Node
    if(prevNode == nullptr){

        possibleJumps.push_back(&grid[1][0]);   // We know that in the base case we can jump right or down
        possibleJumps.push_back(&grid[0][1]);

        return possibleJumps;
    }

    coords currentPosition = currentNode->getCoords();
    coords prevPosition = prevNode->getCoords();
       

    // It is important to know the previous Node to guess the direction that the lava is following
    coords direction      = coords{currentPosition.x - prevPosition.x, currentPosition.y - prevPosition.y};   // We get the vector direction
    coords directionLeft  = coords{direction.x - 1, direction.y};
    coords directionRight = coords{direction.x + 1, direction.y};

    // We check if the Node exists by its coordinates
    if(isInBounds(directionLeft.x, directionLeft.y, grid)){
        possibleJumps.push_back(&grid[directionLeft.y][directionLeft.x]);    // Add the left Node
        currentNode->setCountStraightSteps(0);              // Reset the number of straight steps
    }
    if(isInBounds(directionRight.x, directionRight.y, grid)){
        possibleJumps.push_back(&grid[directionRight.y][directionRight.x]);  // Add the right Node
        currentNode->setCountStraightSteps(0);              // Reset the number of straight steps
    }
    if(isInBounds(direction.x, direction.y, grid) && currentNode->getCountStraightSteps() < 3) 
        possibleJumps.push_back(&grid[direction.y][direction.x]);            // Add the straight Node
        int countStraightSteps = currentNode->getCountStraightSteps();
        currentNode->setCountStraightSteps(countStraightSteps + 1);            // Increase the number of straight steps


    return possibleJumps;
}

// This will be the big boy. It will be iterative instead of recursive :)
void dijkstra(Node* startNode, std::vector<std::vector <Node>> &grid, int nrows, int ncols){

    // Here I will need to define a queue and initialize it with the first Node. Then, perform a while(!queue.empty())
    // It is a good idea to use a priority queue with std::greater<>, so that the smallest element always appears on top

    std::vector<Node*> possibleJumps = getPossibleJumps(startNode, nullptr, grid);

    /*      TODO

        - Create the queue with the next Nodes that need to be scanned
        - Set the new nodes as children of the old ones
        - Linked to that, manage the Paths
        - Go setting the total Heat Loss
    
    
    
    */

}

