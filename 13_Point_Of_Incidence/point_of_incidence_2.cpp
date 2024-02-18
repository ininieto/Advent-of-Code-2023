/*
    Advent of Code 2023 - 13.12.2023

    Link to the problem: https://adventofcode.com/2023/day/13
    
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
    nrows ++;   // We must apply this correction
}

// Debug function to print a 2d vector
void printGrid(std::vector<std::vector<char>> grid){
    for(auto row: grid){
        for(auto element: row){
            std::cout << element;
        }
        std::cout << '\n';
    }
}

// Function to fill in the rows
void fillRows(std::vector<std::vector<char>> &rows, std::string input){

    int nrows = rows.size(), ncols = rows[0].size();
    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            rows[i][j] = input[strCounter];
            strCounter ++;
        }
    }
}

// Function to transpose a rows vector into a columns one
void fillCols(std::vector<std::vector<char>> &cols, std::vector<std::vector<char>> rows){

    for(int i = 0; i < rows.size(); i++){
        for(int j = 0; j < rows[0].size(); j++)
            cols[j][i] = rows[i][j];
        
    } 
}

// Recursive function to check a possible reflection
bool checkPossibleReflection(std::vector<std::vector<char>> grid, int currentIndex, int nextIndex, bool possibleReflection){

    // Base case: we ran out of rows/columns
    if (currentIndex < 0 || currentIndex >= grid.size() || nextIndex < 0 || nextIndex >= grid.size())
        return possibleReflection;

    // Take the current and next row 
    std::vector<char> currentRow = grid[currentIndex];
    std::vector<char> nextRow = grid[nextIndex];

    // Check if the two rows are equal
    bool equalRows = true;
    for (int i = 0; i < currentRow.size(); i++){
        if (currentRow[i] != nextRow[i]){
            equalRows = false;
            break;
        }
    }

    // If they are equal, start the recursion with the adjacent rows. If not, simply return false
    if (equalRows)
        return checkPossibleReflection(grid, currentIndex - 1, nextIndex + 1, true);
    else
        return false;
}

// Function that reads a block and checks if two lines are equal. If they are, calls a recursive function to check if we have a reflection
int getReflectedRowsCols(std::vector<std::vector<char>> grid){

    for(int i = 0; i < grid.size() - 1; i++){

        // We mustn't iterate the whole grid, as it would be senseless to compare the last row to nothing
        if(checkPossibleReflection(grid, i, i + 1, true))
            return i + 1;
    }
    
    // If we reach here means we don't have reflexes
    return 0;
}

int main(){

   // Store the example and the input in variables
    std::string example = "#.##..##.\n..#.##.#.\n##......#\n##......#\n..#.##.#.\n..##..##.\n#.#.##.#.\n\n#...##..#\n#....#..#\n..##..###\n#####.##.\n#####.##.\n..##..###\n#....#..#\n\n";
    std::string input = readInputText("input.txt");

    // Just to work with example. Might comment out
    //input = example;

    // Separate every block and store it in a vector. Still string, not grid
    std::vector<std::string> blocksVector = split(input, "\n\n");

    // Variable to hold the result
    uint64_t result = 0;

    // Big loop
    for(auto block: blocksVector){

        // Guess the size of the grid
        int nrows = 0, ncols = 0;
        getGridDimensions(block, nrows, ncols);

        // Define a vector for the rows and another for the columns. Will be easier to perform the algorithm
        std::vector<std::vector<char>> rows(nrows, std::vector<char>(ncols)); // 2D vector for the rows
        std::vector<std::vector<char>> cols(ncols, std::vector<char>(nrows)); // 2D vector for the cols
        
        // Fill the rows vector and find reflections
        fillRows(rows, block);
        result += (100 * getReflectedRowsCols(rows));

        // Fill the rows vector and find reflections. We separate them in case we found a smudge in the rows
        fillCols(cols, rows);  // TODO: Fill column vector based on the rows one
        result += getReflectedRowsCols(cols);
    }

    // Log the result
    std::cout << result << '\n';
    return 0;
}