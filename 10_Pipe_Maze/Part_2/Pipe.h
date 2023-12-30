#pragma once

#ifndef PIPE 
#define PIPE

#include <iostream>

class Pipe{

private:
    char tile;
    std::pair<int, int> position;
    int distance;

    Pipe* previousPipe;

public:

    // Constructor
    Pipe(Pipe* previousPipe, char tile, std::pair<int, int> position, int distance);

    // Destructor
    virtual ~Pipe(){};

    // Getters and setters
    void setTile(char tile);
    void setDistance(int distance);
    void setPosition(std::pair<int, int> position);
    int getDistance();
    std::pair<int, int> getPosition();
    char getTile();
    void setPreviousPipe(Pipe* previousPipe);
    Pipe* getPreviousPipe();
};

#endif