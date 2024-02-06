/*
    Advent of Code 2023 - 11.12.2023

    Link to the problem: https://adventofcode.com/2023/day/11

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

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

// Function to get automatically the number of rows and columns
void getGridDimensions(std::string input, int &nrows, int &ncols){

    for(int i = 0; i < input.length(); i++){
        if(input[i] == '\n' && ncols == 0)
            ncols = i;
        if(input[i] == '\n' && ncols > 0)
            nrows ++;
    }
    //nrows ++;   // We must apply this correction
}

// Function to fill in the grid
void fillGrid(std::vector<std::vector<char>> &grid, std::string input){

    int nrows = grid.size(), ncols = grid[0].size();

    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            grid[i][j] = input[strCounter];
            strCounter ++;
        }
    }
}

// Function to find the empty rows and columns
void findEmptyRowsCols(std::vector<std::vector<char>> &grid, std::vector<int> &emptyRows, std::vector<int> &emptyCols){

    // Find empty rows
    for(int i = 0; i < grid.size(); i++){

        std::vector<char> row = grid[i];
        bool isRowEmpty = true;

        // Check if the row is empty
        for(auto element: row){
            if(element == '#'){
                isRowEmpty = false;
                break;
            }
        }

        // If row is empty, save the index of the row
        if(isRowEmpty)  
            emptyRows.push_back(i);   
    }

    // Find empty columns
    for(int i = 0; i < grid[0].size(); i++){

        std::vector<char> column;
        bool isColumnEmpty = true;

        // Fill the column
        for(int j = 0; j < grid.size(); j++)
            column.push_back(grid[j][i]);

        // Check if column is empty
        for(char c: column){
            if(c != '.'){
                isColumnEmpty = false;
                break;
            }
        }

        // If column is empty, save the index of the column
        if(isColumnEmpty)
            emptyCols.push_back(i);
    }
}


// Function to find all the galaxies in the grid and save the coordinates
std::vector<std::pair<int, int>> getGalaxiesCoords(std::vector<std::vector<char>> grid){

    std::vector<std::pair<int, int>> galaxiesCoords;

    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            if(grid[i][j] == '#')
                galaxiesCoords.push_back(std::make_pair(i, j));
        }
    }

    return galaxiesCoords;
}

// Function to apply the space expansion
void expandSpace(std::vector<std::pair<int, int>> &galaxiesCoords, std::vector<int> emptyRows, std::vector<int> emptyCols, int expansionRate){

    for(auto &coord: galaxiesCoords){

        int numExpansions = 0;

        // Correction on rows
        for(int rowIndex: emptyRows){
            if(coord.first > rowIndex)  // If the coordinate is bigger, then it will suffer an expansion
                numExpansions ++;
            else    
                break;
        }
        coord.first += numExpansions * expansionRate;

        numExpansions = 0; // Reset the number of corrections

        // Correction on columns
        for(int colIndex: emptyCols){
            if(coord.second > colIndex) // If the coordinate is bigger, then it will suffer an expansion
                numExpansions ++;
            else 
                break;
        }
        coord.second +=  numExpansions * expansionRate;
    }
}


// Function to compute the Manhattan distance
int manhattanDist(std::pair<int, int> coords1, std::pair<int, int> coords2){

    return abs(coords2.first - coords1.first) + abs(coords2.second - coords1.second);
}

int main(){

    // Define the input
    std::string example = "...#......\n.......#..\n#.........\n..........\n......#...\n.#........\n.........#\n..........\n.......#..\n#...#.....\n";
    std::string input = readInputText("input.txt");

    // Get the number of rows and columns
    int nrows = 0, ncols = 0;
    getGridDimensions(input, nrows, ncols);

    // Define the grid and fill it
    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols)); // 2D vector with all the grid
    fillGrid(grid, input);

    // Find all empty rows and columns
    std::vector<int> emptyRows;  // Array that contains the indexes of the empty rows
    std::vector<int> emptyCols;  // Array that contains the indexes of the empty cols
    findEmptyRowsCols(grid, emptyRows, emptyCols);

    // Store the coordinates of all galaxies (no expansion yet)
    std::vector<std::pair<int, int>> galaxiesCoords = getGalaxiesCoords(grid);

    // Apply the Space Expansion
    int expansionRate = 1000000 - 1;    // We need to substract 1 to the expansionRate because we already have a row/col
    expandSpace(galaxiesCoords, emptyRows, emptyCols, expansionRate);

    // As we can only jump up, down, left and right, we are dealing with MANHATTAN DISTANCES
    // The general formula to compute this distance is |x2 - x1| + |y2 - y1|

    uint64_t result = 0;    // The result will be huge, an int is not enough

    // Calculate all the distances
    for(int i = 0; i < galaxiesCoords.size(); i++){
        for(int j = i + 1; j < galaxiesCoords.size(); j++)
            result += manhattanDist(galaxiesCoords[i], galaxiesCoords[j]);
    }

    // Print the result
    std::cout << result << '\n';

    return 0;
}