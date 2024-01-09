//
//  Day19.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//
#include <iostream>
#include <fstream>
#include <tuple>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <sstream>
#include<unistd.h>

long long func(std::map<std::string, std::pair<std::vector<std::tuple<char, char, int, std::string>>, std::string>> wf, std::map<char, std::pair<int, int>> ranges, std::string name = "in"){
	if (name == "R") return 0;
	if (name == "A"){
		long long r = 1;
		for (auto i: ranges) r *= (i.second.second - i.second.first + 1);
		return r;
	}
	long long result = 0;
	std::vector<std::tuple<char, char, int, std::string>> rules = wf[name].first;
	std::string fallback = wf[name].second;
	bool passed = true;
	std::map<char, std::pair<int, int>> range(ranges);
	for (auto rule: rules){
		char k = std::get<0>(rule);
		char cmp = std::get<1>(rule);
		int value = std::get<2>(rule);
		std::string pNext = std::get<3>(rule);
		int lo = range.at(k).first;
		int hi = range.at(k).second;
		std::pair<int, int> tRange, fRange;
		if (cmp == '<' ){
			tRange = std::make_pair(lo, std::min(value - 1, hi));
			fRange = std::make_pair(std::max(value, lo), hi);
		}
		else{
			tRange = std::make_pair(std::max(value + 1, lo), hi);
			fRange = std::make_pair(lo, std::min(value,hi));
		}
		if (tRange.first <= tRange.second){
			std::map<char, std::pair<int, int>> tmp(range);
			tmp.at(k) = tRange;
			result += func(wf, tmp, pNext);
		}
		if (fRange.first <= fRange.second)
			range.at(k) = fRange;
		else if (passed = false)
			break;
	}
	if (passed) result+= func(wf, range, fallback);
	return result;
}

bool hasPassed(std::vector<int> nums, std::map<std::string, std::string> wf){
	std::string name = "in";
	std::map<char, int> condName = {{'x', 0}, {'m', 1}, {'a', 2}, {'s', 3}};

	while (name.length() > 1){
		std::string cond;
		std::stringstream ss(wf[name]);
		// std::cout << name << std::endl;;
		std::string newName = name;
		while (getline(ss, cond, ',') && name == newName){
			if (cond.find(':') == std::string::npos) newName = cond;
			else{
				char c1 = cond.at(0);
				char c2 = cond.at(1);
				int c3 = std::stoi(cond.substr(2, cond.find(':') - 2));
				std::string pNext = cond.substr(cond.find(':') + 1);
				// std::cout << c1 << ' ' << c2 <<' ' << c3 << ' ' << pNext << ' ' <<nums.at(condName.at(c1))<< std::endl;
				if (c2 == '<'){
					if (nums.at(condName.at(c1)) < c3) newName = pNext;
				}
				else{
					if (nums.at(condName.at(c1)) > c3) newName = pNext;
				}
			}
		}
		name = newName;
	}
	if (name == "A") return true;
	else return false;
}

void day19_1(void){
	std::ifstream input("input.txt");
	std::string line;
	std::map<std::string, std::string> wf;
	std::vector <std::vector<int> > parts;
	int result = 0;
	while (getline(input, line)){
		if (line.empty()) continue;
		else if (line.at(0) != '{'){
			std::string name = line.substr(0, line.find('{'));
			std::string conds = line.substr(line.find('{') + 1, line.find('}') - name.length() - 1);
			wf[name] = conds;
		}

		else{
			int c = 0;
			std::vector<int> nums;
			for (char ch : line){
				if (ch >= '0' && ch <= '9') c = c * 10 + ch - '0';
				else if (c > 0){
					nums.push_back(c);
					c = 0;
				}
			}
			if (hasPassed(nums, wf)){
				for (int n : nums) result+=n;
			};
		}
	}
	std::cout<< "Part 1: " << result << std::endl;
}


void day19_2(void){
	std::ifstream input("input.txt");
	std::string line;
	std::map<std::string, std::pair<std::vector<std::tuple<char, char, int, std::string>>, std::string>> wf;
	while (getline(input, line)){
		if (line.empty()) break;
		else if (line.at(0) != '{'){
			std::string name = line.substr(0, line.find('{'));
			std::string conds = line.substr(line.find('{') + 1, line.find('}') - name.length() - 1);
			std::string cond;
			std::string fallback;
			std::vector<std::tuple<char, char, int, std::string>> currentCond;
			std::stringstream ss(conds);
			while (getline(ss, cond, ',')){
				if (cond.find(':') == std::string::npos) fallback = cond;
				else{
					char c1 = cond.at(0);
					char c2 = cond.at(1);
					int c3 = std::stoi(cond.substr(2, cond.find(':') - 2));
					std::string pNext = cond.substr(cond.find(':') + 1);
					currentCond.push_back(std::make_tuple(c1, c2, c3, pNext));
				}
			}
			wf[name] = std::make_pair(currentCond, fallback);
		}
	}
	std::map<char, std::pair<int, int>> ranges = {{'x', std::make_pair(1,4000)},
												{'m', std::make_pair(1,4000)},
												{'a', std::make_pair(1,4000)},
												{'s', std::make_pair(1,4000)}};
	std::cout << "Part 2: "<< func(wf, ranges) << std::endl;
}
void day19(void){
	day19_1();
	day19_2();
}
