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

// Function to fill in any vector
std::vector<int> fillInVector(std::string strSeeds){

    std::vector<int> seedVector;
    std::string aux;

    for (int i = 0; i < strSeeds.length(); i++){
        if (strSeeds[i] != ' ')
            aux.push_back(strSeeds[i]);
        else{
            if (aux.length() > 0){
                seedVector.push_back(stoi(aux));
                aux.clear();
            }
        }
    }

    seedVector.push_back(stoi(aux));
    return seedVector;
}


int main(){

    // Read the example and input files
    std::string example = readInputText("example.txt");
    std::string input = readInputText("input.txt");

    std::vector<std::string> splittedExample = split(example, "\n");
    // std::vector<std::string> splittedInput = split(input, "\n");
    std::vector<std::string> splittedInput = splittedExample;

    // Define the seeds vector
    std::vector<int> seedVector;

    // Declare all the hashmaps
    std::unordered_map<int, int> seed_to_soil;
    std::unordered_map<int, int> soil_to_fertilizer;
    std::unordered_map<int, int> fertilizer_to_water;
    std::unordered_map<int, int> water_to_light;
    std::unordered_map<int, int> light_to_temperature;
    std::unordered_map<int, int> temperature_to_humidity;
    std::unordered_map<int, int> humidity_to_location;

    // Map of maps to read the input
    std::unordered_map<std::string, std::unordered_map<int, int> *> str_to_map = {{"seed-to-soil map:",             &seed_to_soil},
                                                                                  {"soil-to-fertilizer map:",       &soil_to_fertilizer},
                                                                                  {"fertilizer-to-water map:",      &fertilizer_to_water},
                                                                                  {"water-to-light map:",           &water_to_light},
                                                                                  {"light-to-temperature map:",     &light_to_temperature},
                                                                                  {"temperature-to-humidity map:",  &temperature_to_humidity},
                                                                                  {"humidity-to-location map:",     &humidity_to_location}};

    // Read the input and fill in the maps
    for(int i = 0; i < splittedInput.size(); i++){

        std::string line = splittedInput[i];

        if(line.substr(0, line.find(':')) == "seeds"){
            line = line.substr(line.find(' ') + 1); // Get rid of the letters 
            seedVector = fillInVector(line); 
        }  
        else if(line.length() == 0 || isdigit(line[0]))
            continue;
        else{
            std::unordered_map<int, int>* currentMap = str_to_map[line];
            int jumpIndex = 1;
            
            // Must read all the lines that begin with numbers
            while(i + jumpIndex < splittedInput.size() && isdigit(splittedInput[i + jumpIndex][0])){    // Must check that we're not out of bounds BEFORE checking isdigit
                std::vector<int> nums = fillInVector(splittedInput[i + jumpIndex]);
                (*currentMap)[nums[1]] = nums[0];
                jumpIndex ++;
            }
        }
    }

    // Iterate through the seeds
    for(int seed: seedVector){

        // seed to soil

        // soil to fertilizer

        // ...

    }

    // Maybe I could create another map seed_to_location and find the minimum
    


    return 0;
}