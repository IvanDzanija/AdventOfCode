//
//  Day1.cpp
//  2023
//
//  Created by Ivan Dzanija on 08.01.2024..
//

#include <iostream>
#include <fstream>
#include <string>



void day1(void){
    std::ifstream currentFile("input.txt");
    std::string currentLine;
    std::string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    int result = 0;

    while (getline(currentFile, currentLine)){
        int firstDigit = 10;
        int secondDigit = 10;
        for (int i = 0; currentLine[i] != '\0'; ++i)
        {
            if (currentLine[i] >= '0' && currentLine[i] <= '9'){
                if (firstDigit == 10)
                    firstDigit = currentLine[i] - '0';
                else
                    secondDigit = currentLine[i] - '0';
            }
            for (int j = 0; j < 9; ++j){
                if (numbers[j] == currentLine.substr(i,numbers[j].size())){
                    if (firstDigit == 10)
                        firstDigit = j + 1;
                    else
                        secondDigit = j + 1;
                }
            }
        }
        if (secondDigit < 10)
            result += firstDigit * 10 + secondDigit;
        else
            result += firstDigit * 10 + firstDigit;
    }
    currentFile.close();
    std::cout << "Part 2: " << result << std::endl;
}



