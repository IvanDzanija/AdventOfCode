//
//  Day12.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>


std::map <std::pair<std::string, std::vector<int> >, long long> cache;

long long count(std::string cfg, std::vector<int> nums) {
	if (cfg.empty()) {
		return nums.empty() ? 1 : 0;
	}
	if (nums.empty()){
		if (cfg.find("#") != std::string::npos) return 0;
		else return 1;
	}
	std::pair<std::string, std::vector<int> > key = std::make_pair(cfg,nums);
	if (cache.find(key) != cache.end()) return cache.at(key);

	long long result = 0;
	if (cfg[0] == '.' || cfg[0] == '?') {
		result += count(cfg.substr(1), nums);
	}
	if (cfg[0] == '#' || cfg[0] == '?') {
		if (nums[0] <= cfg.length() && cfg.substr(0, nums.at(0)).find('.') == std::string::npos && (nums[0] == cfg.length() || cfg[nums[0]] != '#')) {
			if (nums[0] < cfg.length())
				result += count(cfg.substr(nums[0] + 1), std::vector<int>(nums.begin() + 1, nums.end()));
			else
				result += count(cfg.substr(nums[0]), std::vector<int>(nums.begin() + 1, nums.end()));
		}
	}
	cache[key] = result;
	return result;
}
void day12_1(void){
	std::ifstream input("input.txt");
	std::string line;
	int result = 0;
	
	while(getline(input, line)){
		std::string pattern = line.substr(0, line.find(' '));
		std::string num;
		std::vector <int> lens;
		std::stringstream nums (line.substr(line.find(' ') + 1));
		while (getline(nums, num, ',')){
			lens.push_back(std::stoi(num));
		}
		result += count(pattern, lens);

	}
	std::cout << "Part 1: " << result << std::endl;
	input.close();
}

void day12_2(void){
	std::ifstream input("input.txt");
	std::string line;
	long long result = 0;
	while(getline(input, line)){
		std::string pattern = line.substr(0, line.find(' '));
		std::string num;
		std::vector <int> lens;
		std::stringstream nums (line.substr(line.find(' ') + 1));
		while (getline(nums, num, ',')){
			lens.push_back(std::stoi(num));
		}
		std::string newPattern = pattern;
		for (int i = 0; i < 4; ++i) newPattern.append('?' + pattern);
		std::vector <int> newLens = lens;
		for (int i = 0; i < 4; ++i) {
			for (auto el: lens)
				newLens.push_back(el);
		}
		//std::cout << newPattern << std::endl;
		//for (auto el: newLens) std::cout << el;
		result += count(newPattern, newLens);
	}
	std::cout << "Part 2: " << result << std::endl;
}
void day12(void){
	day12_1();
	day12_2();
}
