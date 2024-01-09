//
//  Day09.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <set>

int prediction(std::vector <int> inputLine){
	std::vector<int> prevTemp(inputLine);
	std::set <int> currentDiff;
	std::vector<int> lastNumbers;
	std::vector<int> firstNumbers;
	lastNumbers.push_back(prevTemp.at(prevTemp.size() - 1));
	firstNumbers.push_back(prevTemp.at(0));
	while (currentDiff.size() != 1 ){
		std::vector<int> newTemp;
		currentDiff.erase(currentDiff.begin(), currentDiff.end());
		for (int i = 1; i < prevTemp.size(); ++i){
			currentDiff.insert(prevTemp.at(i) - prevTemp.at(i - 1));
			newTemp.push_back(prevTemp.at(i) - prevTemp.at(i - 1));
			//std::cout << newTemp.at(i - 1) << ' ' << std::endl;
			if (i == prevTemp.size() - 1) lastNumbers.push_back(newTemp.at(i - 1));
			if (i == 1) firstNumbers.push_back(newTemp.at(i - 1));
		}
		prevTemp = newTemp;
	}
	int res = 0;
	for (int i = 0; i < lastNumbers.size(); ++i)
	{   res += lastNumbers.at(i);

	}
	int currentMargin = firstNumbers.at(firstNumbers.size() - 1);
	
	for (int i = firstNumbers.size() - 2; i >= 0; --i){
		currentMargin = firstNumbers.at(i) - currentMargin;
	}
	return currentMargin;
}
void day9(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	int result = 0;

	while (getline(inputFile, currentLine)){
		int currentNumber = 0;
		bool isNegative = false;
		std::vector<int> inputLine;
		for (int i = 0; i < currentLine.size(); ++i){
			if (currentLine[i] >= '0' && currentLine[i] <= '9'){
				currentNumber = currentNumber * 10 + currentLine[i] - '0';
			}
			if (currentLine[i] == ' ' || i == currentLine.size() - 1){
				if (isNegative) inputLine.push_back(currentNumber * -1);
				else inputLine.push_back(currentNumber);
				isNegative = false;
				currentNumber = 0;
				
			}
			else if (currentLine[i] == '-') isNegative = true;
		}
		result += prediction(inputLine);

	}
	std::cout <<"Part 2: " << result << std::endl;
}
