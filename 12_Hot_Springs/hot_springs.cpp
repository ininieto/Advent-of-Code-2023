/*
    Advent of Code 2023 - 12.12.2023

    Link to the problem: https://adventofcode.com/2023/day/12

    Author of the solution: Íñigo Nieto Cuadrado

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

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

// Function to fill in a int vector given a string
std::vector<int> fillInVector(std::string str){

    std::vector<std::string> strVector = split(str, ",");
    std::vector<int> numVector;

    for(std::string strNum: strVector){
        numVector.push_back(stoull(strNum));
    }

    return numVector;
}


// Recursive function that checks if a combination is valid or not
void countValidCombinations(std::string combination, std::vector<int> nums, int &result){

    // Base cases
    if(combination.length() == 0){   // If we have read the whole combination, check if there are no more numbers to satisfy
        if(nums.size() == 0){
            result ++;
            return;
        }
    }

    if(nums.size() == 0){
        if(combination.find('#') == std::string::npos){  // If there are no more numbers, check that there are no more # left
            result ++;
            return;
        }
    }

    // If next character is a dot
    if(combination[0] == '.')
       return countValidCombinations(combination.erase(0, 1), nums, result); // Call the function removing the first character

    // If next character is # or ? --> Start of block
    if(combination[0] == '#' || combination[0] == '?'){

        std::string block = combination.substr(0, nums[0]); // The next n positions

        if (nums[0] <= combination.length() &&                                // Make sure there are enough characters left to check
            block.find('.') == std::string::npos &&                           // Check that there are no dots in the next positions
            (nums[0] == combination.length() || combination[nums[0]] != '#')){ // We can't have 2 consecutive blocks --> The next one must be a dot (or ? converted to dot)

            // Jump to the end of the block and pop the first number of the vector

            std::string next = "";

            if(combination.length() > nums[0])
                next = combination.substr(nums[0] + 1);
            
            nums.erase(nums.begin());
            return countValidCombinations(next, nums, result);

        }
    }
}

// Function to count all the possible combinations

int countPossibilities(const std::string& cfg, const std::vector<int>& nums, int index = 0) {
    // Base case: if the index reaches the end of cfg, return 1
    if (index >= cfg.length()) {
        return 1;
    }

    int possibilities = 0;

    // If the current character is '?', we have two possibilities: '#' or '.'
    if (cfg[index] == '?') {
        // Calculate possibilities if '?' is replaced by '#'
        possibilities += countPossibilities(cfg, nums, index + 1);

        // Replace '?' by '.' and count possibilities
        std::string cfg_copy = cfg;
        cfg_copy[index] = '.';
        possibilities += countPossibilities(cfg_copy, nums, index + 1);
    } else {
        // If current character is not '?', move to the next index
        possibilities += countPossibilities(cfg, nums, index + 1);
    }

    return possibilities;
}


int main(){

    // Store the example and the input in variables
    std::string example = "???.### 1,1,3\n.??..??...?##. 1,1,3\n?#?#?#?#?#?#?#? 1,3,1,6\n????.#...#... 4,1,1\n????.######..#####. 1,6,5\n?###???????? 3,2,1\n";
    std::string input = readInputText("input.txt");
    
    // Just to work with example
    input = example;

    // Split the initial input by lines
    std::vector<std::string> splittedInput = split(input, "\n");

    // Variable that will hold the final result
    int result = 0;

    // Read every line
    for(std::string line: splittedInput){

        // Separate the springs and the numbers
        std::string spring = line.substr(0, line.find(' '));
        std::string strNumbers = line.substr(line.find(' ') + 1);

        // Store the numbers in a vector and obtain the sum
        std::vector<int> hashtagsVector = fillInVector(strNumbers);

        // Count how many valid combinations exist
        result += countPossibilities(spring, hashtagsVector);
        std::cout << "a";
    }

    std::cout << result;

    return 0;
}