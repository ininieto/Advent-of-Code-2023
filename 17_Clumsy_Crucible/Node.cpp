#include "Node.h"

/*
    This class will be adapted for the problem of Advent of Code 12/12/2022
    The member variables could be altered

    In this case, the nodes will be letters. The adjacent nodes will be treated as children,
    being the root node the S node. 

    How to use:
        - Create a root node like: Node* root = new Node(NULL, startPosition, value, INT_MAX;
        - Create children like: Node* child1 = new Node(root, position, value, root->getMinDistance() + 1);
*/

// Default constructor
Node::Node() : pos{0, 0} {}

// Parameterized constructor
Node::Node(int x, int y) : pos{x, y} {}


// Getters
coords Node::getCoords() const{
    return pos;
}

int Node::getHeatLoss() const{
    return heatLoss;
}

std::vector<Node::Path> Node::getPaths() const{
    return paths;
}

// ------ Modify the Path of a Node ---------

// Add previous Node to a specific path
void Node::addprevNodeToPath(Node* node, int pathId){
    paths[pathId].prevNodes.push(node);
}

// Set the total amount of heat loss of a Node in a specific path
void Node::setDistance(int dist, int pathId){
    paths[pathId].distance = dist;
}

// Set the number of straight steps that a path has followed
void Node::setCountStraightSteps(int numSteps, int pathId){     // Maybe I should split that into increaseNumSteps() and resetNumSteps() ??
    paths[pathId].countStraightSteps = numSteps;
}

// Setters
void Node::setCoords(coords coord){
    pos.x = coord.x;
    pos.y = coord.y;
}

void Node::setHeatLoss(int heatLoss){
    this->heatLoss = heatLoss;
}


