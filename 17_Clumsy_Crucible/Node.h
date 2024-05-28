#pragma once

#ifndef NODE_H
#define NODE_H

#include <vector>
#include <stack>

// Structure that will replace the coordinates being a std::pair
struct coords{
    int x, y;
};

struct history{
    std::vector<std::stack<Node*>> prevNodes;
    int distance;
};

class Node{

public:

    // Constructors
    Node();
    Node(int x, int y);

    // Getters
    coords getCoords() const;
    int getHeatLoss() const;

    // Setters
    void setCoords(coords coord);
    void setHeatLoss(int heatLoss);

private:

    int heatLoss = -1;
    coords pos;
    int minDistance = __INT_MAX__;
    history hist;   // The best way I found to track multiple paths. Every path will have its associated distance 
};

#endif  // NODE_H