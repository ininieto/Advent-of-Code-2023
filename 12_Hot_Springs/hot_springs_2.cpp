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



// Recursive function to count how many different ways exist to arrange the #
int count(std::string config, std::vector<int> nums) {

    // Base cases

    if(config.empty()) // If we've read the whole string, the configuration is positive if there are no more blocks to assign --> empty vector
        return nums.empty() ? 1 : 0;

    if(nums.empty())   // Otherwise, if the vector is empty, we'll return true if there are no more # in the configuration
        return (config.find('#') == std::string::npos) ? 1 : 0;

    int result = 0;

    // If we find a dot or ? (treated as dot) --> Repeat the algorithm starting with the next character
    if(config[0] == '.' || config[0] == '?') 
        result += count(config.substr(1), nums);

    // If we find a # or a ? (treated as a #)
    if(config[0] == '#' || config[0] == '?') {

        if(nums[0] <= config.length()  // Make sure there are enough characters left to check
        && config.substr(0, nums[0]).find('.') == std::string::npos   // Check that there are no dots in the next positions 
        && (nums[0] == config.length() || config[nums[0]] != '#')){   // We can't have 2 consecutive blocks --> The next one must be a dot (or ? converted to dot)

            // We want to start the algorithm after this block. This is a prevention measure to avoid exceptions
            std::string next = "";

            if (config.length() > nums[0])
                next = config.substr(nums[0] + 1);

            // Restart the algorithm after the current block. We also want to get rid of the first element of the nums vector, as it is alredy checked
            result += count(next, std::vector<int>(nums.begin() + 1, nums.end()));
        }
    }

    return result;
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
    uint64_t result = 0;

    // Read every line
    for(std::string line: splittedInput){

        // Separate the springs and the numbers
        std::string spring = line.substr(0, line.find(' '));
        std::string strNums = line.substr(line.find(' ') + 1);

        // Unfold the springs
        std::string originalSpring = spring;
        std::string originalStrNums = strNums;
        for(int i = 0; i < 4; i++){
            spring.push_back('?');
            spring.append(originalSpring);

            strNums.push_back(',');
            strNums.append(originalStrNums);
        }



        // Store the numbers in a vector and obtain the sum
        std::vector<int> nums = fillInVector(strNums);

        // Count how many valid combinations exist
        result += count(spring, nums);
    }

    std::cout << result;

    return 0;
}