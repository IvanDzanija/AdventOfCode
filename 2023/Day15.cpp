//
//  Day15.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <algorithm>

std::string label;

int hash(std::string currentString){
	int hashValue = 0;
	for (char ch : currentString) hashValue = (hashValue + ch) * 17 % 256;
	return hashValue;
}
bool isLabel(const std::pair<std::string, int>& x){
	return x.first == label;
}
void day15(void){
	long long result = 0;
	long long part1 = 0;
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	std::vector <std::vector <std::pair<std::string, int> > > boxes(256);
	while (getline(inputFile, currentLine)){
		std::stringstream curr(currentLine);
		std::string toHash;
		
		while(std::getline(curr,toHash,',') ){
			part1 += hash(toHash);
			if (toHash.find('-') != std::string::npos){
				label = toHash.substr(0,toHash.find('-'));
				size_t boxIndex = hash(label);
				auto lens = std::find_if(boxes.at(boxIndex).begin(), boxes.at(boxIndex).end(), isLabel);

				if (lens != boxes.at(boxIndex).end()) {
					size_t index = distance(boxes.at(boxIndex).begin(), lens);
					boxes.at(boxIndex).erase(boxes.at(boxIndex).begin() + index);
				}
			}
			else {
				
				label = toHash.substr(0,toHash.find('='));
				int focalLength = std::stoi(toHash.substr(toHash.find("=") + 1));
				size_t boxIndex = hash(label);
				
				auto lens = find_if(
					boxes.at(boxIndex).begin(), boxes.at(boxIndex).end(), isLabel);
				if (lens != boxes.at(boxIndex).end()) {
					size_t idx = distance(boxes.at(boxIndex).begin(), lens);
					boxes.at(boxIndex).at(idx).second = focalLength;
				} else boxes.at(boxIndex).push_back(std::make_pair(label,focalLength));

			}
	   }
	}
	inputFile.close();
	for (int i = 0; i < 256; ++i){
		int slot = 1;
		for (int j = 0; j < boxes.at(i).size(); ++j, ++slot)
			result += ((i + 1) * slot * boxes.at(i).at(j).second);
	}
	std::cout << "Part 1: " << part1 << std::endl;
	std::cout << "Part 2: "<< result << std::endl;
	
}
