#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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


// Function to count the number of possible arrangements for a given row
int countArrangements(const std::string& row, const std::vector<int>& groupSizes) {
    // Base case: if there are no group sizes left, return 1
    if (groupSizes.empty()) {
        return 1;
    }

    int totalArrangements = 0;
    int groupSize = groupSizes.front(); // Get the size of the first group
    std::vector<int> remainingGroupSizes(groupSizes.begin() + 1, groupSizes.end()); // Get remaining group sizes

    // Try placing the current group of damaged springs at different positions in the row
    for (int i = 0; i <= row.size() - groupSize; ++i) {
        bool isValidPlacement = true;
        
        // Check if the current group of springs can be placed at position i
        for (int j = i; j < i + groupSize; ++j) {
            if (row[j] == '#') { // If there's already a damaged spring in this position, placement is invalid
                isValidPlacement = false;
                break;
            }
        }
        
        // If the placement is valid, recurse to count arrangements for the remaining groups
        if (isValidPlacement) {
            std::string newRow = row;
            for (int j = i; j < i + groupSize; ++j) {
                newRow[j] = '#'; // Mark the positions of the damaged springs
            }
            totalArrangements += countArrangements(newRow, remainingGroupSizes);
        }
    }
    
    return totalArrangements;
}

int main() {
    // Read input
    std::vector<std::string> rows;
    std::string line;
    
    std::string input = readInputText("input.txt");
    std::vector<std::string> splittedInput = split(input, "\n");

    // Process each row
    int totalArrangements = 0;
    for (const std::string& row : splittedInput) {
        std::string rowCopy = row; // Create a copy of the row
        std::vector<int> groupSizes; // Store the sizes of damaged spring groups
        size_t startPos = 0;

        // Parse the row to extract group sizes
        size_t found = rowCopy.find_first_of("?");
        while (found != std::string::npos) {
            if (found != startPos) {
                groupSizes.push_back(found - startPos);
            }
            startPos = found + 1;
            found = rowCopy.find_first_not_of("?", startPos);
        }
        if (startPos != rowCopy.size()) {
            groupSizes.push_back(rowCopy.size() - startPos);
        }

        // Count arrangements for the current row
        totalArrangements += countArrangements(row, groupSizes);
    }

    // Output the total number of arrangements
    std::cout << "Total arrangements: " << totalArrangements << std::endl;

    return 0;
}