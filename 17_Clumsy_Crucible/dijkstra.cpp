#include "dijkstra.h"
#include "Node.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <queue>

// Calculate the number of forward steps that lava has done so far
int getNumForwardSteps(Node* currentNode, coords direction){

    int numForwardSteps = 0;

    // TODO: Implement this function

    return numForwardSteps;
}


// Check the surroundings of the current node and decide which ones are eligible to jump into
std::vector<Node*> getNextJumps(Node* currentNode, Node* prevNode, std::vector<std::vector <Node>> &grid){

    std::vector<Node*> nextJumps;   // This vector will contain all the jump-able nodes 

    // Base case: first Node
    if(prevNode == nullptr){

        nextJumps.push_back(&grid[1][0]);   // We know that in the base case we can jump right or down
        nextJumps.push_back(&grid[0][1]);

        return nextJumps;
    }

    coords currentPosition = currentNode->getCoords();
    coords prevPosition = prevNode->getCoords();
       
    // It is important to know the previous Node to guess the direction that the lava is following
    coords direction = coords{currentPosition.x - prevPosition.x, currentPosition.y - prevPosition.y}; // We get the vector direction

    // Check how many consecutive straight steps the lava has followed
    int numForwardSteps = getNumForwardSteps(currentNode, direction);
    //int numForwardSteps = 0;

    coords posForward = coords{currentPosition.x + direction.x, currentPosition.y + direction.y};
    coords posLeft, posRight;

    // Fill in the left and right position
    getLeftAndRightPositions(currentPosition, direction, posLeft, posRight);
    
    // If not out of bounds and not explored, we add it to nextJumps
    if(isInBounds(posLeft.x, posLeft.y, grid) && grid[posLeft.y][posLeft.x].getExplored() == false){    
        nextJumps.push_back(&grid[posLeft.y][posLeft.x]);    // Add the left Node
    }
    if(isInBounds(posRight.x, posRight.y, grid) && grid[posRight.y][posRight.x].getExplored() == false){
        nextJumps.push_back(&grid[posRight.y][posRight.x]);  // Add the right Node
    }
    if(isInBounds(posForward.x, posForward.y, grid) && grid[posForward.y][posForward.x].getExplored() == false && numForwardSteps < 3) 
        nextJumps.push_back(&grid[posForward.y][posForward.x]); // Add the straight Node

    return nextJumps;
}

    /*  Dijkstra algorithm

        - Set the root node as 'explored' and set its distance to 0
        - Scan the adjacent nodes (getPossibleJumps)
        - Calculate the compound distance to all of them and add them to a priority queue
        - Start the algorithm over with the first element of the queue (the one with the smallest distance)

        - Note that whenever we deal with a node and scan its surroundings, we have already found the minimum distance
          for that Node -> This implies that we can NEVER jump to an explored Node

    */

// This will be the big boy. It will be iterative instead of recursive :)
void dijkstra(Node* startNode, std::vector<std::vector <Node>> &grid, int nrows, int ncols){

    std::priority_queue<Node *, std::vector<Node *>, SmallestDistanceFirst> nextNodesQueue; // The next Nodes to be scanned will be automatically ordered by its distance

    // Set the distance of the start node to 0
    startNode->setMinDistance(0);

    // Include our startNode in the queue and start the loop
    nextNodesQueue.push(startNode);

    while (!nextNodesQueue.empty()){

        // Extract the first Node and remove it from the queue
        Node* currentNode = nextNodesQueue.top();    
        nextNodesQueue.pop();     

        // Set this Node as explored
        currentNode->setAsExplored();                  

        // Get the next possible jumps
        std::vector<Node*> nextJumps = getNextJumps(currentNode, currentNode->getPrevNode(), grid);  

        // Calculate the distance for those Nodes and add to queue
        for(auto& nextJump : nextJumps){

            // The new minimum distance must be the min(what the next node already has, the distance from this node)
            int newMinDistance = std::min(currentNode->getMinDistance() + nextJump->getHeatLoss(), nextJump->getMinDistance());

            // If new distance is smaller than current minDist, update the prevNode
            if(currentNode->getMinDistance() + nextJump->getHeatLoss() < nextJump->getMinDistance()){
                nextJump->setPrevNode(currentNode);
            }

            nextJump->setMinDistance(newMinDistance);  

            // TODO: Must take care of the 3 forward steps rule
            
            // Add this new node to the queue
            nextNodesQueue.push(nextJump);
        }

    }

}

