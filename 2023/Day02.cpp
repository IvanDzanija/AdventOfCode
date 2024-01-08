//
//  Day02.cpp
//  2023
//
//  Created by Ivan Dzanija on 08.01.2024..
//
#include <iostream>
#include <string>
#include <fstream>


void day2_1(void){
    std::ifstream inputFile("input.txt");
    std::string currentLine;

    int line = 0;
    int result = 0;
    while (std::getline(inputFile, currentLine)){
        ++line;

        currentLine = currentLine.substr(8);
        int i = 0;
        int len = currentLine.size();
        int currentNumber = 0;
        while (i < len){
            if (currentLine[i] >= '0' && currentLine[i] <= '9')
            {
                currentNumber = currentNumber * 10 + (currentLine[i] - '0');
                //std::cout << currentNumber << std::endl;
            }
            else currentNumber = 0;


            if (currentNumber >= 15) i = len;
            else if (currentNumber == 14 && currentLine[i + 2] != 'b') i = len;
            else if (currentNumber == 13 && currentLine[i + 2] == 'r') i = len;
            ++i;
        }
        if (i == len) result += line;
    }
    std::cout << "Part 1: " << result << std::endl;
    inputFile.close();
}

void day2_2(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;

	int line = 0;
	int result = 0;
	while (std::getline(inputFile, currentLine)){
		++line;
		currentLine = currentLine.substr(8);
		int maxRed = 0;
		int maxBlue = 0;
		int maxGreen = 0;

		int i = 0;
		int len = currentLine.size();
		int currentNumber = 0;
		while (i < len){
			if (currentLine[i] >= '0' && currentLine[i] <= '9')
				currentNumber = currentNumber * 10 + (currentLine[i] - '0');

			else if (currentLine[i] > 'a' && currentNumber > 0){
				if (currentLine[i] == 'b' && currentNumber > maxBlue) maxBlue = currentNumber;
				else if (currentLine[i] == 'r' && currentNumber > maxRed) maxRed = currentNumber;
				else if (currentLine[i] == 'g' && currentNumber > maxGreen) maxGreen = currentNumber;
				currentNumber = 0;
			}
			++i;
		}
		result += (maxBlue * maxGreen * maxRed);
	}
	std::cout << "Part 2: " << result << std::endl;
	inputFile.close();
}

void day2(void){
	day2_1();
	day2_2();
}
