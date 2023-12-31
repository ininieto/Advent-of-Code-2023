#pragma once

#ifndef PIPE_MAZE_H
#define PIPE_MAZE_H

#include <iostream>
#include <vector>

#include "Pipe.h"

void fillGrid(std::vector<std::vector<Pipe>> &grid, std::string input, Pipe &startingPipe);
int pipeMaze(Pipe* currentPipe, std::vector<std::vector<Pipe>> &grid);
int countOuterTiles(std::vector<std::vector<Pipe>> &grid, std::pair<int, int> startingPosition);
int countLoopTiles(std::vector<std::vector<Pipe>> &grid);

#endif