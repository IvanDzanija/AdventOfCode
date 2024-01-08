//
//  Day03.cpp
//  2023
//
//  Created by Ivan Dzanija on 08.01.2024..
//

#include <iostream>
#include <string>
#include <map>
#include <fstream>


void day3(void){
	std::ifstream inputFile ("input.txt");
	std::string currentLine;
	std::string fullFile;

	std::map <int, int> gearPosition;

	int result;
	int secondPartResult;
	int lenOfLine;
	while (getline(inputFile, currentLine)){
		fullFile += currentLine;
		lenOfLine = currentLine.size();
	}
	
	for (int i = 0; i < fullFile.size()/lenOfLine ; ++i){
		int currentNumber = 0;
		bool adjacentToSign = false;
		bool possibleGear = false;
		int asteriksPosition;
		for (int j = 0; j < lenOfLine; ++j){
			int currentPosition = i * lenOfLine + j;
			if (fullFile[currentPosition] >= '0' && fullFile[currentPosition] <= '9'){
				currentNumber = currentNumber * 10 + fullFile[currentPosition] - '0';
				for (int checkRow = -1; checkRow < 2; ++checkRow){
					for (int checkColumn = -1; checkColumn < 2; ++checkColumn){
						if (checkRow + i >= 0 && checkColumn + j >= 0 && checkRow + i < fullFile.size()/lenOfLine && checkColumn + j < lenOfLine){
							char currentChar = fullFile[currentPosition + checkRow * lenOfLine + checkColumn];
							if (currentChar != '.' && (currentChar < '0' || currentChar > '9')){
								adjacentToSign = true;
							}
							if (currentChar == '*')
							{
								asteriksPosition = currentPosition + checkRow * lenOfLine + checkColumn;
								possibleGear = true;
							}
						}
					}
				}
			}
			else if (possibleGear){
				if (gearPosition.find(asteriksPosition) != gearPosition.end())
					secondPartResult += gearPosition[asteriksPosition] * currentNumber;
				else gearPosition[asteriksPosition] = currentNumber;
				result += currentNumber;
				adjacentToSign = false;
				possibleGear = false;
				currentNumber = 0;
			}
			else if (adjacentToSign){
				result += currentNumber;
				adjacentToSign = false;
				currentNumber = 0;
			}
			else{
				adjacentToSign = false;
				currentNumber = 0;
			}
			if (j == lenOfLine - 1 && adjacentToSign){
				result += currentNumber;
			}
			if (j == lenOfLine - 1 && possibleGear){
				if (gearPosition.find(asteriksPosition) != gearPosition.end())
					secondPartResult += gearPosition[asteriksPosition] * currentNumber;
				else gearPosition[asteriksPosition] = currentNumber;
			}
		}
	}
	std::cout << "Part 1: " << result << std::endl;
	std::cout << "Part 2: " << secondPartResult << std::endl;

}


