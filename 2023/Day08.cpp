//
//  Day08.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <algorithm>

long long gcd(long long a, long long b) {
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

long long lcm(long long a, long long b) {
	return (a * b) / gcd(a, b);
}

long long findLCM(std::vector<int>& numbers) {
	long long result = 1;
	for (int i = 0; i < numbers.size(); i++) {
		result = lcm(result, numbers[i]);
	}
	return result;
}

void day8(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	
	std::vector<int> steps;
	std::map<std::string, std::vector<std::string> > nodes;
	getline(inputFile, currentLine);
	for (int i = 0; i < currentLine.size(); ++i){
		if (currentLine[i] == 'R') steps.push_back(1);
		else steps.push_back(0);
	}
	getline(inputFile, currentLine);
	std::vector<std::string> currentHeads;
	while (getline(inputFile, currentLine)){
		std::string head;
		std::string left;
		std::string right;
		std::vector<std::string> lr;
		head = currentLine[0] ;
		head += currentLine[1];
		head += currentLine[2];
		left = currentLine[7];
		left += currentLine[8];
		left += currentLine[9];
		right = currentLine[12];
		right += currentLine[13];
		right += currentLine[14];
		lr.push_back(left);
		lr.push_back(right);
		nodes[head] = lr;
		if (head[2] == 'A') currentHeads.push_back(head);
	}
	int step = 0;
	std::vector <int> lcm;
	std::set <int> finished;
	while (currentHeads.size() > finished.size()){
		for (int i = 0; i < currentHeads.size(); ++i)
		{
			std::string currentHead = currentHeads.at(i);
			currentHead = nodes[currentHead].at(steps[step % steps.size()]);
			currentHeads.at(i) = currentHead;
			if (currentHead[2] == 'Z'){
				lcm.push_back(step + 1);
				finished.insert(i);
			}
			
		}
		++step;
	}
	std::cout << "Part 2: "<< findLCM(lcm) << std::endl;
}
