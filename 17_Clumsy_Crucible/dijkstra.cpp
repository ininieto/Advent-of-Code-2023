#include "dijkstra.h"
#include "Node.h"
#include "utils.h"

#include <iostream>
#include <vector>

/* ---------- We don't need it anymore --------------- 

// This function will ONLY return the adjacent elements position. Won't perform any further calculation
std::vector<coords> getSurroundings(Node* currentNode, int nrows, int ncols){
  
    coords pos = currentNode->getCoords();
    std::vector<coords> surroundings;

    // These variables will act as vectors: they indicate how much do I need to increment x and y
    coords up = {pos.x, pos.y - 1};
    coords down = {pos.x, pos.y + 1};
    coords left = {pos.x - 1, pos.y};
    coords right = {pos.x + 1, pos.y};

    if(pos.x == 0 && pos.y == 0){   // Top left corner
        
        surroundings.push_back(right);
        surroundings.push_back(down); 
    }
    else if(pos.x == ncols - 1 && pos.y == 0){  // Top right corner

        surroundings.push_back(left);
        surroundings.push_back(down); 
    }
    else if(pos.x == 0 && pos.y == nrows - 1){  // Bottom left corner

        surroundings.push_back(right);
        surroundings.push_back(up); 
    }
    else if(pos.x == ncols - 1 && pos.y == nrows - 1){  // Bottom right corner

        surroundings.push_back(left); 
        surroundings.push_back(up); 
    }
    else if(pos.y == 0){   // First row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(down); 
    }
    else if(pos.y == nrows - 1){   // Last row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(up); 
    }
    else if(pos.x == 0){  // First column

        surroundings.push_back(right); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else if(pos.x == ncols - 1){   // Last column

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else{   // No weird cases
        surroundings.push_back(right); 
        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    return surroundings;
    
}
*/

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

    // TODO: With the prevNode, I need to guess the pathId. Before I implement it, we will suppose pathId = 0
    int pathId = 0;
       

    // It is important to know the previous Node to guess the direction that the lava is following
    coords direction      = coords{currentPosition.x - prevPosition.x, currentPosition.y - prevPosition.y};   // We get the vector direction
    coords directionLeft  = coords{direction.x - 1, direction.y};
    coords directionRight = coords{direction.x + 1, direction.y};

    // We check if the Node exists by its coordinates
    if(isInBounds(directionLeft.x, directionLeft.y, grid)){
        possibleJumps.push_back(&grid[directionLeft.y][directionLeft.x]);    // Add the left Node
        currentNode->getPaths()[pathId].countStraightSteps = 0;              // Reset the number of straight steps
    }
    if(isInBounds(directionRight.x, directionRight.y, grid)){
        possibleJumps.push_back(&grid[directionRight.y][directionRight.x]);  // Add the right Node
        currentNode->getPaths()[pathId].countStraightSteps = 0;              // Reset the number of straight steps
    }
    if(isInBounds(direction.x, direction.y, grid) && currentNode->getPaths()[pathId].countStraightSteps < 3) 
        possibleJumps.push_back(&grid[direction.y][direction.x]);            // Add the straight Node
        currentNode->getPaths()[pathId].countStraightSteps++;                // Increase the number of straight steps


    return possibleJumps;
}

/*  Original dijkstra function for Hill Climbing from AoC 2022. Needs to be refactored as iterative instead of recursive 


// This function will be recursive. It will be called for the root node, and then, call itself for each child
int dijkstra(Node* startNode, Node* currentNode, std::vector<Node*> unexploredNodes, std::vector<std::vector <int>> grid, std::pair<int, int> endPosition, int &numNodes){
    


    // Debug
    std::cout << "The current position is (" << currentNode->getPosition().first << ", " << currentNode->getPosition().second << "). The min distance is " << currentNode->getMinDistance() << " and the value is " << currentNode->getValue() << '\n';


    // Check if we have already finished
    if(currentNode->getValue() == 123)
        return currentNode->getMinDistance();


    // Erase element from vector unexploredNodes
    for(int i = 0; i < unexploredNodes.size(); i++){
        if(unexploredNodes[i] == currentNode){
            unexploredNodes.erase(unexploredNodes.begin() + i);
            break;
        }
    }

    // Store in a vector all the surroundings
    std::vector<std::pair<int, int>> surroundings = getSurroundings(currentNode, NROWS, NCOLS);

    // Scan the surroundings and get the ones eligible to jump into
    std::vector<std::pair<int, int>> possibleJumps = getPossibleJumps(currentNode, surroundings, grid);


    // If necessary, create the children nodes
    for(auto jumpPosition : possibleJumps){

        Node* existingNode = NULL;  // If the node already exists, this variable will store it
        checkIfNodeExists(startNode, existingNode, jumpPosition);   // Must search from startNode in order to check the whole graph

        if(!existingNode){ // If hasn't been explored

            Node* newNode = new Node(currentNode, jumpPosition, grid[jumpPosition.first][jumpPosition.second], INT_MAX);    // Create the node
            unexploredNodes.push_back(newNode); 
        }
        else{
            // The node already exists -> Must re-calculathe its minimum distance
            existingNode->setMinDistance(std::min(currentNode->getMinDistance() + 1, existingNode->getMinDistance()));    

            if(currentNode->getMinDistance() + 1 < existingNode->getMinDistance()) // Never happens, but just in case
                existingNode->setParent(currentNode);   
        }
    }

    // Store all the child nodes in a vector
    std::vector<Node*> children = currentNode->getChildren();

    // Calculate the distance for every child
    for(auto &child : children){
        child->setMinDistance(std::min(currentNode->getMinDistance() + 1, child->getMinDistance()));  
    }

    // Find the unexplored Node with the smallest distance
    Node* smallestDistanceNode = unexploredNodes[0]; // Take a random one

    for(auto unexploredNode : unexploredNodes){
        if(unexploredNode->getMinDistance() < smallestDistanceNode->getMinDistance())
            smallestDistanceNode = unexploredNode;
    }   

    // Repeat the algorithm with the smallestDistanceNode
    return dijkstra(startNode, smallestDistanceNode, unexploredNodes, grid, endPosition, numNodes);

    
    
}


*/

// This will be the big boy. It will be iterative instead of recursive :)
void dijkstra(Node* startNode, std::vector<std::vector <Node>> &grid, int nrows, int ncols){

    // Here I will need to define a queue and initialize it with the first Node. Then, perform a while(!queue.empty())
    // It is a good idea to use a priority queue with std::greater<>, so that the smallest element always appears on top

    std::vector<Node*> possibleJumps = getPossibleJumps(startNode, nullptr, grid);

}

