#include <iostream>
#include <fstream>
#include <vector>

#include "utils.h"
#include "Pipe.h"

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
            inputData += "\n";
        }
    }
    return inputData;
}

// This function will ONLY return the adjacent positions. Won't perform any further calculation
std::vector<std::pair<int, int>> getSurroundings(Pipe currentPipe, int nrows, int ncols){

    std::pair<int, int> position = currentPipe.getPosition();
    std::vector<std::pair<int, int>> surroundings;

    std::pair<int, int> up = std::make_pair(position.first - 1, position.second);
    std::pair<int, int> down = std::make_pair(position.first + 1, position.second);
    std::pair<int, int> left = std::make_pair(position.first, position.second - 1);
    std::pair<int, int> right = std::make_pair(position.first, position.second + 1);

    if(position == std::make_pair(0, 0)){   // Top left corner
        
        surroundings.push_back(right);
        surroundings.push_back(down); 
    }
    else if(position == std::make_pair(0, ncols - 1)){  // Top right corner

        surroundings.push_back(left);
        surroundings.push_back(down); 
    }
    else if(position == std::make_pair(nrows - 1, 0)){  // Bottom left corner

        surroundings.push_back(right);
        surroundings.push_back(up); 
    }
    else if(position == std::make_pair(nrows - 1, ncols - 1)){  // Bottom right corner

        surroundings.push_back(left); 
        surroundings.push_back(up); 
    }
    else if(position.first == 0){   // First row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(down); 
    }
    else if(position.first == nrows - 1){   // Last row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(up); 
    }
    else if(position.second == 0){  // First column

        surroundings.push_back(right); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else if(position.second == ncols - 1){   // Last column

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    else{   // No weird cases
        surroundings.push_back(right); 
        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down); 
    }
    return surroundings;
}

// Function that checks if we can jump to a surrounding pipe
bool possibleJump(Pipe currentPipe, Pipe nextPipe){

    if (nextPipe.getTile() == '.') // We cannot jump to . positions
        return false;

    // TODO: For the example we know it must be 'F' but for the problem it could be 'J' or '7'
    if(currentPipe.getTile() == 'S')   // Starting node
        currentPipe.setTile('F');
    
    // Pipe matching
    if (currentPipe.getTile() == '|'){ // Vertical

        if((nextPipe.getTile() == 'L' && nextPipe.getPosition().first > currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'J' && nextPipe.getPosition().first > currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'F' && nextPipe.getPosition().first < currentPipe.getPosition().first) ||
           (nextPipe.getTile() == '7' && nextPipe.getPosition().first < currentPipe.getPosition().first))

           return true;
    }
    else if (currentPipe.getTile() == '-'){ // Horizontal

        if((nextPipe.getTile() == 'L' && nextPipe.getPosition().second < currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'F' && nextPipe.getPosition().second < currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'J' && nextPipe.getPosition().second > currentPipe.getPosition().second) ||
           (nextPipe.getTile() == '7' && nextPipe.getPosition().second > currentPipe.getPosition().second))

           return true;
    }
    else if (currentPipe.getTile() == 'L'){ // 90º bend north-east

        if((nextPipe.getTile() == '|' && nextPipe.getPosition().first < currentPipe.getPosition().first) ||
           (nextPipe.getTile() == '-' && nextPipe.getPosition().second > currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'F' && nextPipe.getPosition().first < currentPipe.getPosition().first) ||
           (nextPipe.getTile() == '7' && nextPipe.getPosition().second > currentPipe.getPosition().second) ||
           (nextPipe.getTile() == '7' && nextPipe.getPosition().first < currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'J' && nextPipe.getPosition().second > currentPipe.getPosition().second))

           return true;
    }
    else if (currentPipe.getTile() == 'J'){ // 90º bend north-west

        if((nextPipe.getTile() == '|' && nextPipe.getPosition().first < currentPipe.getPosition().first) ||
           (nextPipe.getTile() == '-' && nextPipe.getPosition().second < currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'F' && nextPipe.getPosition().first < currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'F' && nextPipe.getPosition().second < currentPipe.getPosition().second) ||
           (nextPipe.getTile() == '7' && nextPipe.getPosition().first < currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'L' && nextPipe.getPosition().second < currentPipe.getPosition().second))

           return true;
    }
    else if (currentPipe.getTile() == '7'){ // 90º bend north-east

        if((nextPipe.getTile() == '|' && nextPipe.getPosition().first > currentPipe.getPosition().first) ||
           (nextPipe.getTile() == '-' && nextPipe.getPosition().second < currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'F' && nextPipe.getPosition().second < currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'J' && nextPipe.getPosition().first > currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'L' && nextPipe.getPosition().first > currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'L' && nextPipe.getPosition().second < currentPipe.getPosition().second))

           return true;
    }
    else if (currentPipe.getTile() == 'F'){ // 90º bend north-east

        if((nextPipe.getTile() == '|' && nextPipe.getPosition().first > currentPipe.getPosition().first) ||
           (nextPipe.getTile() == '-' && nextPipe.getPosition().second > currentPipe.getPosition().second) ||
           (nextPipe.getTile() == '7' && nextPipe.getPosition().second > currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'J' && nextPipe.getPosition().first > currentPipe.getPosition().first) ||
           (nextPipe.getTile() == 'J' && nextPipe.getPosition().second > currentPipe.getPosition().second) ||
           (nextPipe.getTile() == 'L' && nextPipe.getPosition().first > currentPipe.getPosition().first))

           return true;
    }

    return false;
}