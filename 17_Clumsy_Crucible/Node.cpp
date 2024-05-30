#include "Node.h"


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

int Node::getCountStraightSteps() const{
    return countStraightSteps;
}

int Node::getMinDistance() const{
    return minDistance;
}

// Setters
void Node::setCoords(coords coord){
    pos.x = coord.x;
    pos.y = coord.y;
}

void Node::setHeatLoss(int heatLoss){
    this->heatLoss = heatLoss;
}

void Node::setCountStraightSteps(int numSteps){
    this->countStraightSteps = numSteps;
}

void Node::setMinDistance(int dist){
    this->minDistance = dist;
}
