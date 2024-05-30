#pragma once

#ifndef NODE_H
#define NODE_H

#include <climits>  // Needed for INT_MAX
#include <stack>

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
    int getCountStraightSteps() const;
    int getMinDistance() const;
    bool getExplored() const;

    // Setters
    void setCoords(coords coord);
    void setHeatLoss(int heatLoss);
    void setCountStraightSteps(int numSteps);
    void setMinDistance(int dist);
    
    void markAsExplored();


private:

    bool explored = false;
    int heatLoss = -1;
    coords pos;
    int countStraightSteps = 0;
    int minDistance = INT_MAX;
};

#endif  // NODE_H