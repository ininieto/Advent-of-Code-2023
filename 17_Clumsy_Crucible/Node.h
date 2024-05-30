#pragma once

#ifndef NODE_H
#define NODE_H

#include <iostream> // Needed for NULL
#include <climits>  // Needed for INT_MAX

// Structure that will replace the coordinates being a std::pair
struct coords{
    int x, y;
};

class Node{

public:

    // Constructors
    Node();
    Node(int x, int y);

    // Getters
    coords getCoords() const;
    int getHeatLoss() const;
    int getCountForwardSteps() const;
    int getMinDistance() const;
    bool getExplored() const;
    Node* getPrevNode() const;

    // Setters
    void setCoords(coords coord);
    void setHeatLoss(int heatLoss);
    void setCountForwardSteps(int numSteps);
    void setMinDistance(int dist);
    void setPrevNode(Node* prevNode);
    
    void setAsExplored();
    
private:

    bool explored = false;
    int heatLoss = -1;
    coords pos;
    Node* prevNode = NULL;
    int minDistance = INT_MAX;
};

#endif  // NODE_H