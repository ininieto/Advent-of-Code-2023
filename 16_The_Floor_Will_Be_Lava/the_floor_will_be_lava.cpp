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

// Function to print the whole grid. Debug purposes
void printGrid(std::vector<std::vector<Node>> &grid){
    for(const auto &row: grid){
        for(const auto &element: row){
            std::cout << element.tile;
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Debug function to print the energized tiles 
void printEnergizedTiles(std::vector<std::vector<Node>> &grid){
    for(const auto &row: grid){
        for(const auto &element: row){
            if(element.energized)
                std::cout << '#';
            else
                std::cout << '.';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// Function that implements the logic of the problem
std::vector<char> decideNextDirections(char direction, char nextTile){

    std::vector<char> nextDirections;

        // If we are moving to the right
        if(direction == 'R'){
            if(nextTile == '/')
                nextDirections.push_back('U');
            else if(nextTile == '\\')   
                nextDirections.push_back('D');
            else if(nextTile == '|'){
                nextDirections.push_back('U');
                nextDirections.push_back('D');
            }
            else    
                nextDirections.push_back('R');
        }
        // If we are moving to the left
        else if(direction == 'L'){
            if(nextTile == '/')
                nextDirections.push_back('D');
            else if(nextTile == '\\')   
                nextDirections.push_back('U');
            else if(nextTile == '|'){
                nextDirections.push_back('U');
                nextDirections.push_back('D');
            }
            else    
                nextDirections.push_back('L');
        }
        // If we are moving up
        else if(direction == 'U'){
            if(nextTile == '/')
                nextDirections.push_back('R');
            else if(nextTile == '\\')   
                nextDirections.push_back('L');
            else if(nextTile == '-'){
                nextDirections.push_back('L');
                nextDirections.push_back('R');
            }
            else    
                nextDirections.push_back('U');
        }
        // If we are moving down
        else if(direction == 'D'){
            if(nextTile == '/')
                nextDirections.push_back('L');
            else if(nextTile == '\\')   
                nextDirections.push_back('R');
            else if(nextTile == '-'){
                nextDirections.push_back('L');
                nextDirections.push_back('R');
            }
            else    
                nextDirections.push_back('D');
        }

        return nextDirections;
}

// Recursive function
void lavaFlow(std::vector<std::vector<Node>> &grid, std::pair<int, int> currentPosition, std::vector<char> nextDirections){

    // If there are no next directions, exit
    if(nextDirections.empty())
        return;
        
    // Debug: Print the grid
    printGrid(grid);
    printEnergizedTiles(grid);

    // Set the current position as energized
    grid[currentPosition.first][currentPosition.second].energized = true;

    // Depending on the next directions, guess the next positions
    for(const auto& direction: nextDirections){
        
        // See the tile of the next position
        std::pair<int, int> nextPosition = std::make_pair(currentPosition.first + move[direction].first, currentPosition.second + move[direction].second);

        // Check if we are out of bounds
        if(nextPosition.first < 0 || nextPosition.first >= grid.size() || nextPosition.second < 0 || nextPosition.second >= grid[0].size())
            continue;

        // Obtain the next tile
        char nextTile = grid[nextPosition.first][nextPosition.second].tile;

        /*
            I found an infinite loop. I need to, somehow, avoid this situations
            The first idea that comes to my mind is to check if I'm in an energized tile and I'm going to another energized, that might be a loop.
        
        */

        // Decide the next direction. Example: if direction == 'R' and nextTile == / --> will go up --> nextDirection = 'U'
        std::vector<char> nextNextDirections = decideNextDirections(direction, nextTile);

        // Call the function for this tile
        lavaFlow(grid, nextPosition, nextNextDirections);
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

   // Start in the origin and move right
   lavaFlow(grid, std::make_pair(0, 0), std::vector<char>{'R'});



    return 0;
}