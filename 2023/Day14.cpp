//
//  Day14.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <map>

void roll(std::vector<std::string> &dish){
	for (int i = 0; i < dish.size(); ++i){
		for (int j = i - 1; j >= 0; --j){
			std::string south = dish.at(j + 1);
			std::string north = dish.at(j);
			
			for (int k = 0; k < north.size(); ++k){
				if (south.at(k) == 'O'){
					if (north.at(k) == '.') {
						dish.at(j).at(k) = 'O';
						dish.at(j + 1).at(k) = '.';
					}
				}
			}

		}
	}
}


int totalLoad(std::vector<std::string> dish){
	int result = 0;
	int c = dish.size();
	for (std::string str : dish){
		for (char ch: str)
			if (ch == 'O') result += c;
		--c;
	}
	return result;
}

void trans(std::vector<std::string>& dish){
	std::vector <std::string> temp;
	for (int i = 0; i < dish.at(0).size(); ++i){
		std::string currentLine;
		for(int j = dish.size() - 1; j >= 0; --j)
			currentLine.push_back(dish.at(j).at(i));
		temp.push_back(currentLine);
	
	}
	dish = temp;


}
void day14_1(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	std::vector <std::string> dish;
	while (getline(inputFile, currentLine)){
		dish.push_back(currentLine);
		
		
	}
	roll(dish);
   
	/*for (std::string str : dish){
		std::cout << str << std::endl;
	}*/
	std::cout << "Part 1: " << totalLoad(dish) << std::endl;
	inputFile.close();
}
void day14_2(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	std::vector <std::string> dish;
	while (getline(inputFile, currentLine)){
		dish.push_back(currentLine);
	}
		roll(dish);
		long long c = 1;
		int curr = totalLoad(dish);
		std::set <int> pattern;
		pattern.insert(curr);

		int currpc = pattern.size();
		int prevpc = 0;

		int res = 0;

		bool spotedCylce = false;
		std::vector<std::string> startOfCycle;
		std::map <int, int> cycle;
		while (c < 1000000000 && !spotedCylce){
			trans(dish);
			if (c % 4 == 0){
				curr = totalLoad(dish);
				pattern.insert(curr);
				prevpc = currpc;
				currpc = pattern.size();
				if (prevpc == currpc && startOfCycle.size() == 0) {
					 
					startOfCycle = dish;
					cycle[c / 4] = curr;
				}
				else if (prevpc != currpc) {
					cycle.clear();
					startOfCycle.erase(startOfCycle.begin(), startOfCycle.end());
				}
				else if (startOfCycle == dish) spotedCylce = true;
				else cycle[c / 4] = curr;
			}
			roll(dish);
			++c;
		}
		for (auto const& [key, val] : cycle)
			if ((1000000000 - key) % cycle.size() == 0) res = val;
		
		std::cout << "Part 2: "<< res << std::endl;

	
}
void day14(void){
	day14_1();
	day14_2();
}


