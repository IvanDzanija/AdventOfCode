#include <iostream>
#include <fstream>
#include <cmath>
#include <set>
#include <vector>
#include <map>
#include <array>

std::vector<std::string> cosmicExpansion2 (std::vector<std::string> inputMatrix){
	for (int i = 0; i < inputMatrix.size(); ++i){
		bool lineEmpty = true;
		for (int j = 0; j < inputMatrix.at(i).size(); ++j)
			if (inputMatrix.at(i)[j] == '#') lineEmpty = false;
		if (lineEmpty)
			for (int j = 0; j < inputMatrix.at(i).size(); ++j) inputMatrix.at(i)[j] = '-';
	}
	for (int i = 0; i < inputMatrix.at(0).size(); ++i){
		bool lineEmpty = true;
		for (int j = 0; j < inputMatrix.size(); ++j){
			if (inputMatrix.at(j)[i] == '#'){
				lineEmpty = false;
			}
		}
		if (lineEmpty){
			for (int j = 0; j < inputMatrix.size(); ++j){
				std::string currentRow = inputMatrix.at(j);
				currentRow[i] = '_';
				inputMatrix.at(j) = currentRow;
			}
		}
	}
	return inputMatrix;
}
std::vector<std::string > cosmicExpansion1 (std::vector<std::string>& inputMatrix){
	for (int i = 0; i < inputMatrix.size(); ++i){
		bool lineEmpty = true;
		for (int j = 0; j < inputMatrix.at(i).size(); ++j){
			if (inputMatrix.at(i)[j] != '.'){
				lineEmpty = false;
			}
		}
		if (lineEmpty){
			inputMatrix.insert(inputMatrix.begin() + i,inputMatrix.at(i));
			++i;
		}
	}
	for (int i = 0; i < inputMatrix.at(0).size(); ++i){
		bool lineEmpty = true;
		for (int j = 0; j < inputMatrix.size(); ++j){
			if (inputMatrix.at(j)[i] != '.'){
				lineEmpty = false;
			}
		}
		if (lineEmpty){
			for (int j = 0; j < inputMatrix.size(); ++j){
				std::string currentRow = inputMatrix.at(j);
				currentRow.insert(currentRow.begin() + i, '.');
				inputMatrix.at(j) = currentRow;
			}
			++i;
		}
	}
	return inputMatrix;

}

std::vector<std::array<long long, 2> > positions(std::vector<std::string> expandedMatrix){
	int rowSize = expandedMatrix.at(0).size();
	int columnSize = expandedMatrix.size();
	std::vector<std::array<long long, 2> > pos;
	long long currentI = 0;
	for(int i = 0; i < columnSize; ++i){
		long long currentJ = 0;
		for (int j = 0; j < rowSize; ++j){
			
			if (expandedMatrix.at(i).at(j) == '_') currentJ += 999999;
			std::array<long long, 2> currentPosition;
			currentPosition.at(0) = currentI;
			currentPosition.at(1) = currentJ;
			if (expandedMatrix.at(i)[j] == '#') pos.push_back(currentPosition);
			++currentJ;
		}
		if (expandedMatrix.at(i).at(0) == '-') currentI += 999999;
		currentI++;
	}
	return pos;

}
void day11_2(void){
	std::ifstream inputFile ("input.txt");
	std::string currentLine;
	std::vector<std::string> inputMatrix;

	while (getline(inputFile, currentLine)){
		inputMatrix.push_back(currentLine);
	}
	std::vector <std::string> expandedMatrix = cosmicExpansion2(inputMatrix);
	std::vector<std::array<long long, 2> > pos = positions(expandedMatrix);
	
	long long result = 0;
	for (int i = 0; i < pos.size(); ++i){
		//std::cout<< pos.at(i).at(0) << ' ' <<  pos.at(i).at(1) <<' ' << i + 1 << std::endl;
		for (int j = i + 1; j < pos.size(); ++j){
			
			result +=  abs(pos.at(j).at(0) - pos.at(i).at(0)) + abs(pos.at(j).at(1) - pos.at(i).at(1));
		}
	}
	std::cout << "Part 2: "<< result << std::endl;
}

void day11_1(void){
	std::ifstream inputFile ("input.txt");
	std::string currentLine;
	std::vector<std::string> inputMatrix;

	while (getline(inputFile, currentLine)){
		inputMatrix.push_back(currentLine);
	}
	std::vector <std::string> expandedMatrix = cosmicExpansion1(inputMatrix);
	int rowSize = expandedMatrix.at(0).size();
	int columnSize = expandedMatrix.size();

	std::vector<std::array<int, 2> > positions;
	for(int i = 0; i < columnSize; ++i){
		for (int j = 0; j < rowSize; ++j){
			std::array<int, 2> currentPosition;
			currentPosition.at(0) = i;
			currentPosition.at(1) = j;
			if (expandedMatrix.at(i)[j] != '.') positions.push_back(currentPosition);
		}
	}

	int result = 0;
	for (int i = 0; i < positions.size(); ++i){
		//std::cout<< positions.at(i).at(0) << ' ' <<  positions.at(i).at(1) <<' ' << i + 1 << std::endl;
		for (int j = i + 1; j < positions.size(); ++j){
			
			result +=  abs(positions.at(j).at(0) - positions.at(i).at(0)) + abs(positions.at(j).at(1) - positions.at(i).at(1));
		}
	}
	std::cout << "Part 1: "<< result << std::endl;
}
void day11(void){
	day11_1();
	day11_2();
}
