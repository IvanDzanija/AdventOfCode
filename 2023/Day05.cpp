#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <algorithm>


//takes a minute to run
long long solve_part2(){
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	std::string numbers;

	std::map<int, int> seedToLocation;
	long long seeds[20];
	int count[7];
	int numOfSeeds = 0;
	int counter = -1;
	int line = 0;
	while (getline(inputFile, currentLine)) {
		if (line == 0)
		{
			int i = 0;
			int len = currentLine.size();
			long long currentNumber = 0;
			while (i < len){
				if (currentLine[i] >= '0' && currentLine[i] <= '9')
				{
					currentNumber = currentNumber * 10 + (currentLine[i] - '0');
					//std::cout << currentNumber << std::endl;
				}
				if (currentLine[i] < '0' || currentLine[i] > '9' || i == len - 1){
					if ((currentNumber) > 0)
					{
						seedToLocation[currentNumber] = currentNumber;
						seeds[numOfSeeds] = currentNumber;
						++numOfSeeds;
					}
					currentNumber = 0;
				}
				++i;
			}
		}
		else{
			if (currentLine[0] >= '0' && currentLine[0] <= '9'){
				count[counter] += 1;
			}
			else if (currentLine[0] >= 'a' && currentLine[0] <= 'z'){
				counter++;

			}
			int i = 0;
			size_t len = currentLine.size();
			std::string currentNumber;
			while (i < len){
				if (currentLine[i] >= '0' && currentLine[i] <= '9')
				{
					currentNumber += currentLine[i];
					//std::cout << currentNumber << std::endl;
				}
				if ((currentLine[i] < '0' || currentLine[i] > '9' || i == len - 1) && !currentNumber.empty()){
					numbers += currentNumber + " ";
					currentNumber.clear();
				}
				++i;
			}
		}
		++line;
	}
	int len = 0;
	for (int i = 0; i < numbers.size(); i++){
		if (numbers[i] == ' ') len++;
	}
	long long list[len];
	int k = 0;
	long long currentNumber = 0;
	for (int i = 0; i < numbers.size(); i++){
		if (numbers[i] >= '0' && numbers[i] <= '9'){
			currentNumber = currentNumber * 10 + (numbers[i] - '0');
					//std::cout << currentNumber << std::endl;
		}
		else{
			list[k] = currentNumber;
			currentNumber = 0;
			k++;
			//std::cout << list[k - 1] << std::endl;
		}
			 
	}
	for (int i = 1; i < 7; ++i) count[i] += count[i - 1];

	long long originalSeed = 0;
	long long min2 = 9223372036854000000;
	for (int i = 1; i < numOfSeeds; i += 2){
		for (long long l = 0; l < seeds[i]; l += sqrt(seeds[i])){
			long long possibleSeed = seeds[i - 1] + l;
			long long currentSeed = seeds[i - 1] + l;
			int c = 0;
			bool isChanged = false;
			for (int j = 0; j < len; j += 3){
				if (j / 3 == count[c]){
					isChanged = false;
					++c;
				}
				long long first = list[j];
				long long second = list[j + 1];
				long long range = list[j + 2];
				if (currentSeed < second + range && currentSeed >= second && isChanged == false)
				{
					long long dist = currentSeed - second;
					currentSeed = first + dist;
					isChanged = true;
				}


			}
			if (currentSeed < min2){
				min2 = currentSeed;
				originalSeed = possibleSeed;

			}
		}
	}
	long long seed = 0;
	long long range = 0;
	long long min1 = 9223372036854000000;
	for (int i = 0; i < 20; i += 2){
		if (seeds[i] + seeds[i + 1] >= originalSeed && seeds[i] <= originalSeed){
			seed = seeds[i];
			range = seeds[i + 1];
		}
	}
	for (int l = 0; l < range; ++l){
		long long currentSeed = seed + l;
		int c = 0;
		bool isChanged = false;
		for (int j = 0; j < len; j += 3){
			if (j / 3 == count[c]){
				isChanged = false;
				++c;
			}
			long long first = list[j];
			long long second = list[j + 1];
			long long range = list[j + 2];
			if (currentSeed < second + range && currentSeed >= second && isChanged == false)
				{
					long long dist = currentSeed - second;
					currentSeed = first + dist;
					isChanged = true;
				}


			}
			if (currentSeed < min1){
				min1 = currentSeed;
			}
		}
	inputFile.close();
	seedToLocation.erase(seedToLocation.begin(), seedToLocation.end());
	return min1;


}
long long solve_part1(void){
	std::ifstream inputFile("input.txt");
	
	std::string currentLine;
	std::string numbers;

	std::map<int, int> stl;
	long long sds[20];
	int cnt[7];
	int numOfSeeds = 0;
	int counter = -1;
	int line = 0;
	while (getline(inputFile, currentLine)) {
		if (line == 0)
		{
			int i = 0;
			size_t len = currentLine.size();
			long long currentNumber1 = 0;
			while (i < len){
				if (currentLine[i] >= '0' && currentLine[i] <= '9')
				{
					currentNumber1 = currentNumber1 * 10 + (currentLine[i] - '0');
					//std::cout << currentNumber << std::endl;
				}
				if (currentLine[i] < '0' || currentLine[i] > '9' || i == len - 1){
					if ((currentNumber1) > 0)
					{
						stl[currentNumber1] = currentNumber1;
						sds[numOfSeeds] = currentNumber1;
						++numOfSeeds;
					}
					currentNumber1 = 0;
				}
				++i;
			}
		}
		else{
			if (currentLine[0] >= '0' && currentLine[0] <= '9'){
				cnt[counter] += 1;
			}
			else if (currentLine[0] >= 'a' && currentLine[0] <= 'z'){
				counter++;

			}
			int i = 0;
			size_t len = currentLine.size();
			std::string currentNumber;
			while (i < len){
				if (currentLine[i] >= '0' && currentLine[i] <= '9')
				{
					currentNumber += currentLine[i];
					//std::cout << currentNumber << std::endl;
				}
				if ((currentLine[i] < '0' || currentLine[i] > '9' || i == len - 1) && !currentNumber.empty()){
					numbers += currentNumber + " ";
					currentNumber.clear();
				}
				++i;
			}
		}
		++line;
	}
	int len = 0;
	for (int i = 0; i < numbers.size(); i++){
		if (numbers[i] == ' ') len++;
	}
	long long list[len];
	int k = 0;
	long long currentNumber = 0;
	for (int i = 0; i < numbers.size(); i++){
		if (numbers[i] >= '0' && numbers[i] <= '9'){
			currentNumber = currentNumber * 10 + (numbers[i] - '0');
					//std::cout << currentNumber << std::endl;
		}
		else{
			list[k] = currentNumber;
			currentNumber = 0;
			k++;
			//std::cout << list[k - 1] << std::endl;
		}
			 
	}
	for (int i = 0; i < 7; ++i){
		//std::cout << count[i] << std::endl;
	}
	bool list1[20] = {false};

	int c = 0;

	for (int i = 0; i < k; i += 3){
		if (i / 3 == cnt[c])
		{
			for (int m = 0; m < 20; ++m){
				list1[m] = false;
			}
			++c;
			cnt[c] += cnt[c - 1];
		}
		long long first = list[i];
		long long second = list[i + 1];
		long long range = list[i + 2];
		for (int l = 0; l < 20; ++l){
			//if (l == 1)std::cout << l << ' ' << seeds[l] << ' ' << first << ' ' <<range << std::endl;
			if (sds[l] < second + range && sds[l] >= second && list1[l] == false)
			{
				long long dist = sds[l] - second;
				sds[l] = first + dist;
				list1[l] = true;
				
			}
		}
		

	}
	long long min = 9223372036854000000;
	for (int i = 0; i < 20; i++)
	{
		if (sds[i] < min) min = sds[i];
		//std::cout << seeds[i] << std::endl;
	}
	inputFile.close();
	return min;
}
void day5(void){
	long long part2 = solve_part2();
	long long part1 = solve_part1();
	std::cout << "Part 1: " << part1 << std::endl;
	std::cout << "Part 2: " << part2 << std::endl;
}


