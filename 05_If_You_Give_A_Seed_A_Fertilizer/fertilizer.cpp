/*
    Advent of Code 2023 - 05.12.2023

    Link to the problem: https://adventofcode.com/2023/day/5

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
std::vector<uint64_t> fillInVector(std::string str){

    std::vector<std::string> strVector = split(str, " ");
    std::vector<uint64_t> seedVector;

    for(std::string strNum: strVector){
        seedVector.push_back(stoull(strNum));
    }

    return seedVector;
}

// Function to assign the value even though the key is not found
uint64_t tryToAssignFromMap(uint64_t key, std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> map){

    for(auto mapElement: map){  // Iterate all the elements of the map

        int range = mapElement.second.second;   // Covers the amount of numbers in range
        int diff = mapElement.second.first - mapElement.first;  // The relation between the starting points defines all the range

        /*
            Example: In the second line of the example we have 52 50 48
            This means that map[50] = 52, map[51] = 53, map[52] = 54, ..., map[97] = 99
            The relation between the key and value is (52 - 50) = 2 --> diff
        */

        // Check if the key doesn't belong to the map 
        if(key < mapElement.first || key > mapElement.first + range)
            continue;
        // The key is in the map
        else
            return key + diff;
    }

    // If key not found
    return key;

}

int main(){

    // Read the example and input files
    std::string example = readInputText("example.txt");
    std::string input = readInputText("input.txt");

    std::vector<std::string> splittedExample = split(example, "\n");
    std::vector<std::string> splittedInput = split(input, "\n");
    //std::vector<std::string> splittedInput = splittedExample;

    // Define the seeds vector
    std::vector<uint64_t> seedVector;

    // Declare all the hashmaps. Will relate an input int with a std::pair(minValue, range)
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> seed_to_soil;
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> soil_to_fertilizer;
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> fertilizer_to_water;
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> water_to_light;
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> light_to_temperature;
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> temperature_to_humidity;
    std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> humidity_to_location;

    // TODO: Change key for a pair <lowerBound, range>

    // Map of maps to read the input
    std::unordered_map<std::string, std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>> *> str_to_map = {{"seed-to-soil map:", &seed_to_soil},
                                                                                                                 {"soil-to-fertilizer map:", &soil_to_fertilizer},
                                                                                                                 {"fertilizer-to-water map:", &fertilizer_to_water},
                                                                                                                 {"water-to-light map:", &water_to_light},
                                                                                                                 {"light-to-temperature map:", &light_to_temperature},
                                                                                                                 {"temperature-to-humidity map:", &temperature_to_humidity},
                                                                                                                 {"humidity-to-location map:", &humidity_to_location}};

    // Read the input and fill in the maps
    for(uint64_t i = 0; i < splittedInput.size(); i++){

        std::string line = splittedInput[i];

        if(line.substr(0, line.find(':')) == "seeds"){
            line = line.substr(line.find(' ') + 1); // Get rid of the letters 
            seedVector = fillInVector(line); 
        }  
        else if(line.length() == 0 || isdigit(line[0]))
            continue;
        else{
            std::unordered_map<uint64_t, std::pair<uint64_t, uint64_t>>* currentMap = str_to_map[line];
            uint64_t jumpIndex = 1;

            // Must read all the lines that begin with numbers
            while(i + jumpIndex < splittedInput.size() && isdigit(splittedInput[i + jumpIndex][0])){    // Must check that we're not out of bounds BEFORE checking isdigit
                std::vector<uint64_t> nums = fillInVector(splittedInput[i + jumpIndex]);
                (*currentMap)[nums[1]] = std::make_pair(nums[0], nums[2]);
                jumpIndex ++;
            }
        }
    }

    // Make all the conversions and find the minimum location
    uint64_t minLocation = INT_MAX;

    for(uint64_t seed: seedVector){

        uint64_t soil = tryToAssignFromMap(seed, seed_to_soil);
        uint64_t fert = tryToAssignFromMap(soil, soil_to_fertilizer);
        uint64_t water = tryToAssignFromMap(fert, fertilizer_to_water);
        uint64_t light = tryToAssignFromMap(water, water_to_light);
        uint64_t temp = tryToAssignFromMap(light, light_to_temperature);
        uint64_t humid = tryToAssignFromMap(temp, temperature_to_humidity);
        uint64_t location = tryToAssignFromMap(humid, humidity_to_location);

        if(location < minLocation)
            minLocation = location;
    }
    
    std::cout << "The result is " << minLocation << '\n';

    return 0;
}