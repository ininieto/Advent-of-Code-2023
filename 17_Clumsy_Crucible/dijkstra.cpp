#include "dijkstra.h"
#include "Node.h"
#include "utils.h"

#include <iostream>
#include <vector>
#include <queue>


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
    }
    if(isInBounds(directionRight.x, directionRight.y, grid)){
        possibleJumps.push_back(&grid[directionRight.y][directionRight.x]);  // Add the right Node
    }
    if(isInBounds(direction.x, direction.y, grid) && currentNode->getCountStraightSteps() < 3) 
        possibleJumps.push_back(&grid[direction.y][direction.x]);            // Add the straight Node

    return possibleJumps;
}

// This will be the big boy. It will be iterative instead of recursive :)
void dijkstra(Node* startNode, std::vector<std::vector <Node>> &grid, int nrows, int ncols){

    std::priority_queue<Node *, std::vector<Node *>, SmallestDistanceFirst> nextNodes; // The next Nodes to be scanned will be automatically ordered by its distance

    startNode->setMinDistance(0);
    startNode->markAsExplored();

    // Include our startNode in the queue and start the loop
    nextNodes.push(startNode);

    /*  Dijkstra algorithm

        - Set the root node as 'explored' and set its distance to 0
        - Scan the adjacent nodes (getPossibleJumps)
        - Calculate the compound distance to all of them and add them to a priority queue
        - Start the algorithm over with the first element of the queue (the one with the smallest distance)

        - Note that whenever we deal with a node and scan its surroundings, we have already found the minimum distance
          for that Node -> This implies that we can NEVER jump to an explored Node

    */

    while (!nextNodes.empty()){

        Node* currentNode = nextNodes.top();    // Extract the first node in the queue
        nextNodes.pop();                        // Eliminate the current Node from the queue

        std::vector<Node *> possibleJumps = getPossibleJumps(startNode, nullptr, grid);

        // Dijkstra algorithm here
    }

    /*      TODO

        - Create the queue with the next Nodes that need to be scanned
        - Set the new nodes as children of the old ones
        - Linked to that, manage the Paths
        - Go setting the total Heat Loss
    
    
    
    */

}

