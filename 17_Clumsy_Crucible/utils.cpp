#include <iostream>
#include <vector>
#include <fstream>

#include "Node.h"

// Function to split a std::string by a specific delimitator
std::vector<std::string> split(std::string text, std::string delim){

    std::vector<std::string> splittedText;
    size_t pos = 0;
    std::string token;

    while((pos = text.find(delim)) != std::string::npos){
        token = text.substr(0, pos);
        splittedText.push_back(token);
        text.erase(0, pos + delim.length());
    }

    if(text.length() > 0)
        splittedText.push_back(text);

    return splittedText;
}

// Read input data from txt file
std::string readInputText(std::string inputText){

    std::fstream inputfile;
    std::string inputData;

    inputfile.open(inputText, std::ios::in);
    if (inputfile.is_open()){
        std::string tp;

        while (getline(inputfile, tp)){
            inputData += tp;
            inputData += '\n';
        }
    }
    return inputData;
}

// Function to get automatically the number of rows and columns
void getGridDimensions(std::string input, int &nrows, int &ncols){

    for(int i = 0; i < input.length(); i++){
        if(input[i] == '\n' && ncols == 0)
            ncols = i;
        if(input[i] == '\n' && ncols > 0)
            nrows ++;
    }
}

// Function to print the whole grid. Debug purposes
void printGrid(std::vector<std::vector<Node>> &grid){
    for(const auto &row: grid){
        for(const auto &element: row){
            std::cout << element.getHeatLoss();
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

void fillGrid(std::vector<std::vector<Node>> &grid, std::string input){

    int nrows = grid.size(), ncols = grid[0].size();
    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            grid[i][j].setCoords(coords{j, i}); // x is horizontal, y is vertical
            grid[i][j].setHeatLoss(static_cast<int>(input[strCounter]) - 48);   // Convert number from char to int
            strCounter ++;
        }
    }
}

// Function to check if a position is in bounds
bool isInBounds(int x, int y, std::vector<std::vector<Node>> &grid){    

    int nrows = grid.size(), ncols = grid[0].size(); // Honestly, I don't like to recalculate nrows and ncols all the times. Might find a way to improve that 

    return x >= 0 && x < ncols && y >= 0 && y < nrows;
}

// Function to find the left and right positions given a point and forward direction
void getLeftAndRightPositions(coords position, coords direction, coords &leftPosition, coords &rightPosition){

    /*
    Essentially I want to rotate 90 degrees the direction vector. For that, I will use the 2x2 rotation matrix. 
    The problem is that my y axis grows downwards: (0, 1) points down! So the rotation is a bit different

    For 90 degrees (left):
                             x' = y,  y' = -x

    For -90 degrees (right):
                              x' = -y, y' = x
    */

    coords vecLeft{direction.y, (-1) * direction.x};
    coords vecRight{(-1) * direction.y, direction.x};

    leftPosition = coords{position.x + vecLeft.x, position.y + vecLeft.y};
    rightPosition = coords{position.x + vecRight.x, position.y + vecRight.y};
}