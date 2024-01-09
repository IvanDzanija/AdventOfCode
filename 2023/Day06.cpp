//
//  Day06.cpp
//  2023
//
//  Created by Ivan Dzanija on 08.01.2024..
//
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int binarySearch(long time, long distance){
	int result = 0;
	int possible = 0;
	long mid;
	if (time % 2 == 1) mid = time / 2;
	else {
		if (time / 2 * time / 2 > distance ) possible = 1;
		mid = time / 2 - 1;
	}
	long counter = time - mid;
	while (counter * mid > distance){
		result += 1;
		counter++;
		mid--;
	}


	return result * 2 + possible;
}

void day6(void){
	std::ifstream inputFile("input.txt");
	std::string firstLine;
	std::string secondLine;

	getline(inputFile, firstLine);
	getline(inputFile, secondLine);
	firstLine = firstLine.substr(13);
	secondLine = secondLine.substr(12);
	int len = 1;
	for (int i = 1; i < firstLine.size(); ++i)
		if (firstLine[i] == ' ' && firstLine[i - 1] != ' ') ++len;

	int time[len];
	int distance[len];
	int c = 0;
	int currentNumber;
	for (int i = 0; i < firstLine.size(); ++i){
		if (firstLine[i] >= '0' && firstLine[i] <= '9'){
			currentNumber = currentNumber * 10 + firstLine[i] - '0';
		}
		else if (firstLine[i - 1] != ' '){
			time[c] = currentNumber;
			++c;
			currentNumber = 0;
		}
		if (i == firstLine.size() - 1){
			time[c] = currentNumber;
		}
	}
	c = 0;
	currentNumber = 0;
	for (int i = 0; i < secondLine.size(); ++i){
		if (secondLine[i] >= '0' && secondLine[i] <= '9'){
			currentNumber = currentNumber * 10 + secondLine[i] - '0';
		}
		else if (secondLine[i - 1] != ' '){
			distance[c] = currentNumber;
			++c;
			currentNumber = 0;
		}
		if (i == secondLine.size() - 1){
			distance[c] = currentNumber;
		}
	}
	for (int i = 0; i < len; ++i)
	{
		std::cout << time [i] << ' ' << distance[i] << std::endl;
	}
	int result = 1;
	for (int i = 0; i < len; ++i)
		result *= binarySearch(time[i], distance[i]);
	std::cout<< "Part 1: " << result << std::endl;
	
	long long timeVar = 0;
	long long distanceVar = 0;
		for (int i = 0; i < firstLine.size(); ++i)
			if (firstLine[i] >= '0' && firstLine[i] <= '9')
				timeVar = timeVar * 10 + firstLine[i] - '0';
		for (int i = 0; i < secondLine.size(); ++i)
			if (secondLine[i] >= '0' && secondLine[i] <= '9')
				distanceVar = distanceVar * 10 + secondLine[i] - '0';
		result = binarySearch(timeVar, distanceVar);
		std::cout<<"Part 2: " << result << std::endl;

}
