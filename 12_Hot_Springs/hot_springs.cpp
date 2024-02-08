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

// Function to find the regions that have no dots --> could be damaged
std::vector<std::string> findRegionsWithoutDot(std::string spring){

    std::vector<std::string> regionsWithoutDot;
    std::string temp;

    for(char c: spring){
        if(c != '.')
            temp.push_back(c);
        else{
            if(temp.size() == 0)    
                continue;
            regionsWithoutDot.push_back(temp);
            temp.clear();
        }
    }
    if(temp.size() > 0) regionsWithoutDot.push_back(temp);

    return regionsWithoutDot;
}

// Function to find the number of # in the spring
void countHashtagsAndInterrogants(std::string spring, int &numHashtags, int &numInterrogants){

    for(char c: spring){
        if(c == '#')
            numHashtags ++;
        else if(c == '?')
            numInterrogants ++;
    }
}

// Function to compute factorial
int factorial(int num){

    int result = 1;

    for(int i = 1; i <= num; i++){
        result *= i;
    }

    return result;
}

// Function to sum all elements of a vector
int sum(std::vector<int> vec){

    int sum = 0;
    for(int element: vec)
        sum += element;
    
    return sum;
}

// Function that checks if the tried combination is valid
bool checkValidCombination(std::string combination, std::vector<int> hashtagsVector){

    // Get the hashtag vector for our combination
    std::vector<int> combinationHashtags;

    int acc = 0;

    for(char c: combination){
        if(c == '#')
            acc ++;
        else if(c == '.' && acc > 0){
            combinationHashtags.push_back(acc);
            acc = 0;
        }
    }
    if(acc > 0)
        combinationHashtags.push_back(acc);

    // Compare both vectors
    if(combinationHashtags.size() != hashtagsVector.size())
        return false;
    else{
        for(int i = 0; i < combinationHashtags.size(); i++){
            if(combinationHashtags[i] != hashtagsVector[i])
                return false;
        }
    }

    return true;
}


int main(){

    // Store the example and the input in variables
    std::string example = "???.### 1,1,3\n.??..??...?##. 1,1,3\n?#?#?#?#?#?#?#? 1,3,1,6\n????.#...#... 4,1,1\n????.######..#####. 1,6,5\n?###???????? 3,2,1\n";
    std::string input = readInputText("input.txt");
    
    // Just to work with example
    input = example;

    // Split the initial input by lines
    std::vector<std::string> splittedInput = split(input, "\n");

    // Map with all the tried combinations
    std::unordered_map<std::string, int> alreadyTriedCombinations;

    // Read every line
    for(std::string line: splittedInput){

        // Separate the springs and the numbers
        std::string spring = line.substr(0, line.find(' '));
        std::string strNumbers = line.substr(line.find(' ') + 1);

        // Store the numbers in a vector
        std::vector<int> hashtagsVector = fillInVector(strNumbers);
        
        // Identify the regions that have no '.'
        std::vector<std::string> regionsWithoutDot = findRegionsWithoutDot(spring);

        // Count hashtags and interrogants in the spring
        int numHashtagsInSpring = 0, numInterrogants = 0;
        countHashtagsAndInterrogants(spring, numHashtagsInSpring, numInterrogants);

        // Calculate the number of available hashtags (total number - already placed ones)
        int numHashtags = sum(hashtagsVector) - numHashtagsInSpring;

        // Find the total number of combinations: C(n, k) = n! / k! (n - k)!
        int numCombinations = factorial(numInterrogants) / factorial(numHashtags) / factorial(numInterrogants - numHashtags);

        // Try all the different combinations and check if they're possible or not
        for(int i = 0; i < numCombinations; i++){

            // Try a combnation
            std::string combination = "#.#.###";    // TODO: Fill this string with every single combination

            // Check if it has been already tried
            if(alreadyTriedCombinations.find(combination) != alreadyTriedCombinations.end())
                continue;

            // If not, check if it is valid
            bool validCombination = checkValidCombination(combination, hashtagsVector);

            // Save combination in hashmap
            alreadyTriedCombinations[combination] = validCombination;
        }
    }

    // Sum all the possible combinations
    int result = 0;

    for(auto element: alreadyTriedCombinations)
        result += element.second;

    std::cout << result;

    return 0;
}