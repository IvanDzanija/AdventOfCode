//
//  Day13.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

bool offByOne(std::string first, std::string second){
	int c = 0;
	for (int i = 0; i < first.size(); ++i){
		if (first[i] != second[i]) ++c;
		if (c == 2) return false;
	}
	return true;

}
int checkHorizontal(std::vector<std::string>& currentPattern){
	std::string prev = currentPattern.at(0);
	for (int i = 1; i < currentPattern.size(); ++i){
		std::string curr = currentPattern.at(i);
		if (prev == curr){
			bool used = false;
			int c = 0;
			std::string nextL;
			std::string nextR;
			bool isMirrored = true;
			while (isMirrored && i + c < currentPattern.size() && i - c > 0 ){
				nextL = currentPattern.at(i - c - 1);
				nextR = currentPattern.at(i + c);
				if (nextL != nextR && !used) {
					if (!offByOne(nextL, nextR)) isMirrored = false;
					else used = true;
				}
				else if (nextL != nextR && used) isMirrored = false;
				++c;
				
			}
			if (isMirrored && used) return i;
		}
		else if (offByOne(prev,curr)){
			std::cout << "tu" << std::endl;
			std::cout << prev << std::endl;

			std::cout << curr << std::endl;
			int c = 1;
			std::string nextL;
			std::string nextR;
			bool isMirrored = true;
			while (isMirrored && i + c < currentPattern.size() && i - c > 0 ){
				nextL = currentPattern.at(i - c - 1);
				nextR = currentPattern.at(i + c);
				if (nextL != nextR ) isMirrored = false;
				++c;
				
			}
			if (isMirrored) return i;


		}
		prev = curr;
	}
	return 0;
}
int checkVertical(std::vector<std::string>& currentPattern){
	int numOfRows = currentPattern.size();
	int numOfColls = currentPattern.at(0).size();
	std::vector<std::string> temp;
	//transpose matrix and use horizontal algo;
	for (int i = 0; i < numOfColls; ++i){
		std::string currentLine;
		for (int j = 0; j < numOfRows; ++j)
			currentLine.push_back(currentPattern.at(j).at(i));
		temp.push_back(currentLine);
	}
	int res = checkHorizontal(temp);
	return res;
}

void day13(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	std::vector <std::string> currentPattern;
	int result;
	int h = 0;
	int v = 0;
	while (getline(inputFile, currentLine)){
		if (currentLine.size() == 0){
			/*for (int i = 0; i < currentPattern.size(); ++i){
				std::cout << currentPattern.at(i) << std::endl;
			}*/
			int h = checkHorizontal(currentPattern);
			int v = checkVertical(currentPattern);
			result += v + (h * 100);
			currentPattern.erase(currentPattern.begin(), currentPattern.end());
		}
		else currentPattern.push_back(currentLine);
	}
	std::cout << "Part 2: "<< result << std::endl;
}
