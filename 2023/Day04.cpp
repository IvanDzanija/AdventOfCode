//
//  Day04.cpp
//  2023
//
//  Created by Ivan Dzanija on 08.01.2024..
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cmath>

void day4(void){
	
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	std::map <int,int> gameCount;

	int result = 0;
	int secondPartResult = 0;
	int numOfCard = 0;
	while (getline(inputFile, currentLine)){
		++numOfCard;
		gameCount[numOfCard] += 1;
		int numOfWinning = 0;
		int currentNumberFirst = 0;
		
		//std::string currentLineWinning = currentLine.substr(8, 15);
		std::string currentLineWinning = currentLine.substr(10, 30);
		//if (currentLineWinning[0] == ' ') currentLineWinning = currentLine.substr(11, 29);
		
		//std::string currentLineCheck = currentLine.substr(25, 23);
		std::string currentLineCheck = currentLine.substr(42, 74);
		//if (currentLineCheck[0] == ' ') currentLineCheck = currentLine.substr(43, 74);
		
		for (int i = 0; i < currentLineWinning.size(); ++i){
			if (currentLineWinning[i] >= '0' && currentLineWinning[i] <= '9')
				currentNumberFirst = currentNumberFirst * 10 + currentLineWinning[i] - '0';

			else if (currentNumberFirst != 0) {
				int currentNumberSecond = 0;
				for (int j = 0; j < currentLineCheck.size(); ++j){
					if (currentLineCheck[j] >= '0' && currentLineCheck[j] <= '9')
						currentNumberSecond = currentNumberSecond * 10 + currentLineCheck[j] - '0';
					else{
						if (currentNumberFirst == currentNumberSecond){
							//std::cout << currentNumberFirst << ' ' << currentNumberSecond << std::endl;
							++numOfWinning;
						}
						currentNumberSecond = 0;

					}
					if (j == currentLineCheck.size() - 1){
						if (currentNumberFirst == currentNumberSecond){
							
							++numOfWinning;
						}
					}
				}
				currentNumberFirst = 0;
			}
		}
		for (int k = numOfCard + 1; k <= numOfWinning + numOfCard; ++k)
		{
			
			if (gameCount.find(k) == gameCount.end()) gameCount[k] = gameCount[numOfCard];
			else gameCount[k] += gameCount[numOfCard];
			//std::cout << k << ' ' << gameCount[k] << std::endl;
		}
		secondPartResult += gameCount[numOfCard];
		result += std::pow(2,numOfWinning - 1);

	}
	std::cout << "Part 1: "<<result << std::endl;
	std::cout << "Part 2: "<<secondPartResult << std::endl;
	inputFile.close();
}
