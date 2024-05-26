#pragma once

#ifndef NODE_H
#define NODE_H

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

    // Setters
    void setCoords(coords coord);
    void setHeatLoss(int heatLoss);

private:

    int heatLoss = -1;
    coords pos;
};

#endif  // NODE_H