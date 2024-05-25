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
    int getX() const;
    int getY() const;

    // Setters
    void setX(int x);
    void setY(int y);

private:

    coords pos;
};

#endif  // NODE_H