/*
    Advent of Code 2023 - 16.12.2023

    Link to the problem: https://adventofcode.com/2023/day/16
    
    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Node{

    int x, y;
    char tile;
    bool energized = false;

    // Default constructor
    Node(): x(-1), y(-1), tile('?') {}

    // Constructor with parameters (not sure if I will need this)
    Node(int x_p, int y_p, char tile_p): x(x_p), y(y_p), tile(tile_p) {}

};

std::unordered_map<char, std::pair<int, int>> move = {
    {'U', std::make_pair(-1, 0)},
    {'D', std::make_pair(1, 0)},
    {'L', std::make_pair(0, -1)},
    {'R', std::make_pair(0, 1)} 
};

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

// Function to fill in the grid
void fillGrid(std::vector<std::vector<Node>> &grid, std::string input){

    int nrows = grid.size(), ncols = grid[0].size();
    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            grid[i][j].x = i;
            grid[i][j].y = j;
            grid[i][j].tile = input[strCounter];
            strCounter ++;
        }
    }
}

// Recursive function
void lavaFlow(std::vector<std::vector<Node>> &grid, std::pair<int, int> currentPosition, std::vector<char> nextDirections){

    // Set the current position as energized
    grid[currentPosition.first][currentPosition.second].energized = true;

    // Depending on the next directions, guess the next positions
    for(auto& direction: nextDirections){
        
        // See the tile of the next position
        std::pair<int, int> nextPosition = std::make_pair(currentPosition.first + move[direction].first, currentPosition.second + move[direction].second);
        char nextTile = grid[nextPosition.first][nextPosition.second].tile;

        // Decide the next direction
        

        // Call the function for this tile
    }

    
}


int main(){

    // Read the input
    std::string example = readInputText("example.txt");
    std::string input = readInputText("input.txt");

    // Debug
    input = example;

    // Store the input in a 2d Node grid
    int nrows = 0, ncols = 0;
    getGridDimensions(input, nrows, ncols);

    std::vector<std::vector<Node>> grid(nrows, std::vector<Node>(ncols)); // 2D vector for the rows
    fillGrid(grid, input);

    /*
        Bunch of ideas:
            - Maybe I could define a map relating "up", "down"... to std::pairs like (0, 1), (1, 0)... 
              This way I can say nextCoord = currentCoords + move["up"]

            - Recursive function: lavaFlow(currentPosition, nextPosition)
              Watch out: there could be more that one nextPosition. Maybe it should be a vector nextPositions
    */

   // Start in the origin and move right
   lavaFlow(grid, std::make_pair(0, 0), std::vector<char>{'R'});



    return 0;
}