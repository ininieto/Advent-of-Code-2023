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

int Node::getCountForwardSteps() const{
    return countForwardSteps;
}

int Node::getMinDistance() const{
    return minDistance;
}

bool Node::getExplored() const{
    return explored;
}

Node* Node::getPrevNode() const{
    return prevNode;
}

// Setters
void Node::setCoords(coords coord){
    pos.x = coord.x;
    pos.y = coord.y;
}

void Node::setHeatLoss(int heatLoss){
    this->heatLoss = heatLoss;
}

void Node::setCountForwardSteps(int numSteps){
    this->countForwardSteps = numSteps;
}

void Node::setMinDistance(int dist){
    this->minDistance = dist;
}

void Node::setPrevNode(Node* prevNode){
    this->prevNode = prevNode;
}

// Mark Node as explored
void Node::setAsExplored(){
    this->explored = true;
}
