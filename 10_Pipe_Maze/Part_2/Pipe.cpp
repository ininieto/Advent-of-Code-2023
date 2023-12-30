#include <iostream>

#include "Pipe.h"

// Constructor
Pipe::Pipe(Pipe* previousPipe, char tile, std::pair<int, int> position, int distance){

    this->previousPipe = previousPipe;
    this->tile = tile;
    this->position = position;
    this->distance = distance;
}

// Getters and setters
void Pipe::setTile(char tile){
    this->tile = tile;
}

void Pipe::setDistance(int distance){
    this->distance = distance;
}

void Pipe::setPosition(std::pair<int, int> position){
    this->position = position;
}

int Pipe::getDistance(){
    return this->distance;
}

std::pair<int, int> Pipe::getPosition(){
    return this->position;
}

char Pipe::getTile(){
    return this->tile;
}

void Pipe::setPreviousPipe(Pipe* previousPipe){
    this->previousPipe = previousPipe;
}

Pipe* Pipe::getPreviousPipe(){
    return this->previousPipe;
}