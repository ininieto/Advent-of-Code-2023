/*
    Advent of Code 2023 - 03.12.2023

    Link to the problem: https://adventofcode.com/2023/day/3

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

struct Number{

    std::vector<std::pair<int, int>> digitPositions;
    int value;
    bool checked = false;
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
            inputData += "\n";
        }
    }
    return inputData;
}

// This function will ONLY return the position of the adjacent elements. Won't perform any further calculation
std::vector<std::pair<int, int>> getSurroundings(std::pair<int, int> position, int nrows, int ncols){

    std::vector<std::pair<int, int>> surroundings;

    std::pair<int, int> up = std::make_pair(position.first - 1, position.second);
    std::pair<int, int> down = std::make_pair(position.first + 1, position.second);
    std::pair<int, int> left = std::make_pair(position.first, position.second - 1);
    std::pair<int, int> right = std::make_pair(position.first, position.second + 1);
    std::pair<int, int> upLeft = std::make_pair(position.first - 1, position.second - 1);
    std::pair<int, int> upRight = std::make_pair(position.first - 1, position.second + 1);
    std::pair<int, int> downLeft = std::make_pair(position.first + 1, position.second - 1);
    std::pair<int, int> downRight = std::make_pair(position.first + 1, position.second + 1);

    if(position == std::make_pair(0, 0)){   // Top left corner
        
        surroundings.push_back(right);
        surroundings.push_back(down); 
        surroundings.push_back(downRight);
    }
    else if(position == std::make_pair(0, ncols - 1)){  // Top right corner

        surroundings.push_back(left);
        surroundings.push_back(down);
        surroundings.push_back(downLeft); 
    }
    else if(position == std::make_pair(nrows - 1, 0)){  // Bottom left corner

        surroundings.push_back(right);
        surroundings.push_back(up); 
        surroundings.push_back(upRight);
    }
    else if(position == std::make_pair(nrows - 1, ncols - 1)){  // Bottom right corner

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(upLeft);
    }
    else if(position.first == 0){   // First row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(down); 
        surroundings.push_back(downLeft); 
        surroundings.push_back(downRight); 
    }
    else if(position.first == nrows - 1){   // Last row

        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(up);  
        surroundings.push_back(upLeft); 
        surroundings.push_back(upRight);
    }
    else if(position.second == 0){  // First column

        surroundings.push_back(right); 
        surroundings.push_back(up); 
        surroundings.push_back(down);  
        surroundings.push_back(upRight); 
        surroundings.push_back(downRight);
    }
    else if(position.second == ncols - 1){   // Last column

        surroundings.push_back(left); 
        surroundings.push_back(up); 
        surroundings.push_back(down);  
        surroundings.push_back(upLeft); 
        surroundings.push_back(downLeft);
    }
    else{   // No weird cases
        surroundings.push_back(upLeft); 
        surroundings.push_back(up); 
        surroundings.push_back(upRight); 
        surroundings.push_back(left); 
        surroundings.push_back(right); 
        surroundings.push_back(downLeft); 
        surroundings.push_back(down); 
        surroundings.push_back(downRight); 
        
    }
    return surroundings;
}

// Function to store all the numbers of the grid in a vector. This way we don't sum the same number more than once
void readAllNumbers(std::vector<std::string> splittedInput, std::vector<Number> &allNumbers){

    int nrows = splittedInput.size(), ncols = splittedInput[0].size();

    for(int i = 0; i < nrows; i++){
        std::string row = splittedInput[i];
        std::string strNum;
        Number num;

        for(int j = 0; j < ncols; j++){
            char c = row[j];
            if(isdigit(c)){
                strNum.push_back(c);
                num.digitPositions.push_back(std::make_pair(i, j));
            }
            else{
                if(strNum.length() > 0){
                    num.value = stoi(strNum);;
                    allNumbers.push_back(num);
                    num.digitPositions.clear();
                    strNum.clear();
                }
            }
        }

        // Numbers ending in the last column were not read otherwise
        if (strNum.length() > 0){
            num.value = stoi(strNum);
            allNumbers.push_back(num);
            num.digitPositions.clear();
            strNum.clear();
        }
    }
}

// Function that checks the adjacent numbers to the symbol
void checkSurroundings(std::vector<std::vector<char>> grid, std::vector<std::pair<int, int>> surroundings, std::vector<Number> allNumbers, int &result){

    bool numberFoundForThisPos = false;
    std::vector<int> potentialGearRatios;    // I will store in a vector all the adjacent numbers to a *. If the size of the vector is 2 --> Add to result

    // Get all the surrounding values
    for(auto pos: surroundings){
        if(isdigit(grid[pos.first][pos.second])){

            // Find the position in the allNumbers array
            for(Number &num: allNumbers){
                if(num.checked || numberFoundForThisPos){
                    numberFoundForThisPos = false;
                    continue;
                }
                for(auto digitPosition: num.digitPositions){
                    if(digitPosition.first == pos.first && digitPosition.second == pos.second && !num.checked){
                        potentialGearRatios.push_back(num.value);
                        num.checked = true;
                        numberFoundForThisPos = true;
                        break;
                    }
                }
            }
        }

    }

    if(potentialGearRatios.size() == 2)
        result += potentialGearRatios[0] * potentialGearRatios[1];
}


int main(){

    std::string example = "467..114..\n...*......\n..35..633.\n......#...\n617*......\n.....+.58.\n..592.....\n......755.\n...$.*....\n.664.598..";
    std::string inputData = readInputText("input.txt");

    // Split the data
    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(inputData, "\n");
    //std::vector<std::string> splittedInput = splittedExample;
    
    // Store the data in a grid
    int nrows = splittedInput.size(), ncols = splittedInput[0].size();
    std::vector<std::vector<char>> grid(nrows, std::vector<char>(ncols));

    int i = 0;
    for(auto &row: grid){
        for(auto &element: row){
            if(inputData[i] == '\n') 
                i++;
            element = inputData[i];
            i++;
        }
    }

    // Save all the numbers in an array. They belong to a struct with its position and whether they're checked or not
    std::vector<Number> allNumbers;
    readAllNumbers(splittedInput, allNumbers);

    int result = 0;

   // Read the grid looking for symbols. If found, check surroundings
    for (int i = 0; i < nrows; i++){
        std::string row = splittedInput[i];
        for (int j = 0; j < ncols; j++){
            char c = row[j];
            if (c == '*'){ // Symbol detected --> Now the symbols are only *
                std::pair<int, int> position = std::make_pair(i, j);
                std::vector<std::pair<int, int>> surroundings = getSurroundings(position, nrows, ncols);
                checkSurroundings(grid, surroundings, allNumbers, result);
            }
        }
    }

    std::cout << "The result is " << result << '\n';

    return 0;
}
