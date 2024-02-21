/*
    Advent of Code 2023 - 13.12.2023

    Link to the problem: https://adventofcode.com/2023/day/13
    
    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>

int getReflectedRowsCols(std::vector<std::vector<char>> grid, bool &alreadyCorrectedSmudge);

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

// Function to fill in the rows
void fillRows(std::vector<std::vector<char>> &grid, std::string input){

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

// Function to fill in the columns
void fillCols(std::vector<std::vector<char>> &grid, std::string input){

    int nrows = grid[0].size(), ncols = grid.size(); // Transpose it for the columns

    int strCounter = 0;

    for (int i = 0; i < nrows; i++){
        for (int j = 0; j < ncols; j++){

            if (input[strCounter] == '\n')
                strCounter ++;

            grid[j][i] = input[strCounter];
            strCounter ++;
        }
    }
}

// Recursive function to check a possible reflection
bool checkPossibleReflection(std::vector<std::vector<char>> grid, int currentIndex, int nextIndex, bool possibleReflection, bool &alreadyCorrectedSmudge, int &finalResult){

    // Base case: we ran out of rows/columns
    if (currentIndex < 0 || currentIndex >= grid.size() || nextIndex < 0 || nextIndex >= grid.size())
        return possibleReflection;

    // Take the current and next row 
    std::vector<char> currentRow = grid[currentIndex];
    std::vector<char> nextRow = grid[nextIndex];

    // Check if the two rows are equal
    std::vector<int> differentIndexes;  // I define a vector that contains the indexes of the different elements. Like that I can count them
    for (int i = 0; i < currentRow.size(); i++){
        if (currentRow[i] != nextRow[i])
            differentIndexes.push_back(i); 
    }

    bool equalRows = differentIndexes.empty();

    // Here comes the magic
    if(differentIndexes.size() == 1){

        int idx = differentIndexes[0];

        // Create a temporary grid and change the different spot
        std::vector<std::vector<char>> tempGrid = grid;

        tempGrid[currentIndex][idx] = (tempGrid[currentIndex][idx] == '#') ? '.' : '#'; // If it was a #, set it to . and vice versa
        bool tempAlreadyCorrectedSmudge = true;

        finalResult = getReflectedRowsCols(tempGrid, tempAlreadyCorrectedSmudge);

        if(finalResult > 0){
            std::cout << "Tenemos el smudge" << '\n';
            return true;
        }

    }

    // If they are equal, start the recursion with the adjacent rows. If not, simply return false
    if (equalRows)
        return checkPossibleReflection(grid, currentIndex - 1, nextIndex + 1, true, alreadyCorrectedSmudge, finalResult);
    else
        return false;
}

// Function that reads a block and checks if two lines are equal. If they are, calls a recursive function to check if we have a reflection
int getReflectedRowsCols(std::vector<std::vector<char>> grid, bool &alreadyCorrectedSmudge){

    int finalResult = -1;

    // We mustn't iterate the whole grid, as it would be senseless to compare the last row to nothing
    for(int i = 0; i < grid.size() - 1; i++){

        bool possibleReflection = checkPossibleReflection(grid, i, i + 1, true, alreadyCorrectedSmudge, finalResult);
        
        if(possibleReflection && alreadyCorrectedSmudge)
            return i + 1;
        else if(possibleReflection && !alreadyCorrectedSmudge && finalResult > -1)
            return finalResult;
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

        // Debug
        std::cout << "Nueva linea" << '\n';

        // Guess the size of the grid
        int nrows = 0, ncols = 0;
        getGridDimensions(block, nrows, ncols);

        // Define a vector for the rows and another for the columns. Will be easier to perform the algorithm
        std::vector<std::vector<char>> rows(nrows, std::vector<char>(ncols)); // 2D vector for the rows
        std::vector<std::vector<char>> cols(ncols, std::vector<char>(nrows)); // 2D vector for the cols
        
        fillRows(rows, block);
        fillCols(cols, block);

        bool alreadyCorrectedSmudge = false;

        // Find the reflected rows and cols
        result += (100 * getReflectedRowsCols(rows, alreadyCorrectedSmudge));
        alreadyCorrectedSmudge = false;
        result += getReflectedRowsCols(cols, alreadyCorrectedSmudge);
    }

    // Log the result
    std::cout << result << '\n';
    return 0;
}