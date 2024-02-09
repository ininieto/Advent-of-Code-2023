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


// Function to find the number of # in the spring
void countHashtagsAndInterrogants(std::string spring, int &numHashtags, int &numInterrogants){

    for(char c: spring){
        if(c == '#')
            numHashtags ++;
        else if(c == '?')
            numInterrogants ++;
    }
}

// Function to sum all elements of a vector
int sum(std::vector<int> vec){

    int sum = 0;
    for(int element: vec)
        sum += element;
    
    return sum;
}

// Function to find all ? in the spring
std::vector<int> findInterrogants(std::string spring){

    std::vector<int> indexes;
    for(int i = 0; i < spring.size(); i++){
        if(spring[i] == '?')
            indexes.push_back(i);
    }
    return indexes;
}

// Function to generate combinations recursively
void generateCombinations(int n, int k, int idx, std::string current, std::vector<std::string>& combinations) {

    // Base case: If we have placed all k elements
    if (k == 0) {
        // Fill remaining spots with .
        current.append(n - idx, '.');
        // Store current combination
        combinations.push_back(current);
        return;
    }

    // If there are not enough spots remaining
    if (idx >= n)
        return;

    // Place a # and recurse for next position
    generateCombinations(n, k - 1, idx + 1, current + '#', combinations);
    // Skip this position and recurse
    generateCombinations(n, k, idx + 1, current + '.', combinations);
}


// Function to find all the possible combinations given a spring and the total number of #
std::vector<std::string> getAllPossibleCombinations(std::string spring, int numInterrogants, int numAvailableHashtags, std::vector<int> interrogantIndexes){

    // Find all combinations and store them in a vector
    std::vector<std::string> combinations;
    generateCombinations(numInterrogants, numAvailableHashtags, 0, "", combinations);

    // Replace the ? in spring for the combinations of # and store them in a vector
    std::vector<std::string> allPossibleCombinations;

    for (auto combination : combinations){
        for (int i = 0; i < numInterrogants; i++){
            spring[interrogantIndexes[i]] = combination[i];
        }
        allPossibleCombinations.push_back(spring);
    }

    return allPossibleCombinations;
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

    // Am I on new branch?

    // Store the example and the input in variables
    std::string example = "???.### 1,1,3\n.??..??...?##. 1,1,3\n?#?#?#?#?#?#?#? 1,3,1,6\n????.#...#... 4,1,1\n????.######..#####. 1,6,5\n?###???????? 3,2,1\n";
    std::string input = readInputText("input.txt");
    
    // Just to work with example
    //input = example;

    // Split the initial input by lines
    std::vector<std::string> splittedInput = split(input, "\n");

    // Variable that will hold the final result
    int result;

    // Read every line
    for(std::string line: splittedInput){

        // Separate the springs and the numbers
        std::string spring = line.substr(0, line.find(' '));
        std::string strNumbers = line.substr(line.find(' ') + 1);

        // Store the numbers in a vector and obtain the sum
        std::vector<int> hashtagsVector = fillInVector(strNumbers);
        int totalNumHashtags = sum(hashtagsVector);

        // Find all the spots with ?
        std::vector<int> interrogantIndexes = findInterrogants(spring);

        // Count hashtags and interrogants in the spring
        int numHashtagsInSpring = 0, numInterrogants = 0;
        countHashtagsAndInterrogants(spring, numHashtagsInSpring, numInterrogants);

        // Calculate the number of available hashtags (total number - already placed ones)
        int numAvailableHashtags = totalNumHashtags - numHashtagsInSpring;

        // Obtain all the possible combinations 
        std::vector<std::string> allPossibleCombinations = getAllPossibleCombinations(spring, numInterrogants, numAvailableHashtags, interrogantIndexes);

        // Try all the different combinations and check if they're possible or not
        for(auto combination: allPossibleCombinations){

            // If not, check if it is valid
            bool validCombination = checkValidCombination(combination, hashtagsVector);

            // If valid combination, add 1 to the final result
            result += validCombination;
        }
    }

    std::cout << result;

    return 0;
}