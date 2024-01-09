//
//  Day20.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <tuple>
#include <numeric>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <deque>

using ll = int64_t;
class Module{
	
	public:
		char type;
		std::string name;
		std::vector<std::string> outputs;
		std::map<std::string, char> memory;

		Module(char type, std::string name, std::vector<std::string> outputs){
			this -> type = type;
			this -> name = name;
			this -> outputs = outputs;
			if (type == '%') this -> memory[this -> name] = 'l';
		}
		Module(){

		}
};

void day20_1(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::string> brOutputs;
	std::map<std::string, Module*> modules;
	while (getline(input,line)){
		std::string left = line.substr(0, line.find(" -> "));
		std::string right = line.substr(line. find(" ") + 3);
		std::vector <std::string> currentOutputs;
		std::stringstream ss(right);
		while (getline(ss, right, ',')) currentOutputs.push_back(right.substr(1));
		if (left == "broadcaster")
			brOutputs = currentOutputs;
		else{
			char type = left.at(0);
			std::string name = left.substr(1);
			modules[name] = new Module(type, name, currentOutputs);
		}
	}
	for (auto each: modules){
		for (auto out: each.second->outputs){
			if (modules.find(out) != modules.end() && modules[out] -> type == '&'){
				modules[out] -> memory[each.first] = 'l';
			}
		}
	}
	
	ll lo = 0, hi = 0;
	for (int i = 0; i < 1000; ++i){
		std::deque<std::tuple<std::string, std::string, char>> q;
		for (auto out: brOutputs) q.push_back(std::make_tuple("broadcaster", out, 'l'));
		++lo;
		while (!q.empty()){
			std::tuple<std::string, std::string, char> cur = q.front();
			q.pop_front();
			std::string origin = std::get<0>(cur);
			std::string target = std::get<1>(cur);
			char signal = std::get<2>(cur);

			if (signal == 'l') ++lo;
			else ++hi;

			if (modules.find(target) == modules.end())
				continue;
			
			Module* currentMod = modules.at(target);

			if (currentMod -> type == '%'){
				if (signal == 'l'){
					if (currentMod -> memory.at(currentMod -> name) == 'l'){
					currentMod -> memory.at(currentMod -> name) = 'h';
					for (auto targ: currentMod -> outputs) q.push_back(std::make_tuple(currentMod -> name, targ, 'h'));
				}
					else if (currentMod -> memory.at(currentMod -> name) == 'h'){
					currentMod -> memory.at(currentMod -> name) = 'l';
					for (auto targ: currentMod -> outputs) q.push_back(std::make_tuple(currentMod -> name, targ, 'l'));
				}
				}
			}
			else {
				currentMod -> memory[origin] = signal;
				char out;
				ll highs = 0;
				for (auto x: currentMod -> memory)
					if (x.second == 'h') ++highs;
				if (highs == currentMod -> memory.size()) out = 'l';
				else out = 'h';
				for (auto x: currentMod -> outputs) q.push_back(std::make_tuple(currentMod -> name, x, out));
			}

		}
	}
	std::cout << "Part 1: "<< lo * hi << std::endl;
	input.close();
}

void day20_2(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::string> brOutputs;
	std::map<std::string, Module*> modules;
	while (getline(input,line)){
		std::string left = line.substr(0, line.find(" -> "));
		std::string right = line.substr(line. find(" ") + 3);
		std::vector <std::string> currentOutputs;
		std::stringstream ss(right);
		while (getline(ss, right, ',')) currentOutputs.push_back(right.substr(1));
		if (left == "broadcaster")
			brOutputs = currentOutputs;
		else{
			char type = left.at(0);
			std::string name = left.substr(1);
			modules[name] = new Module(type, name, currentOutputs);
		}
	}
	for (auto each: modules){
		for (auto out: each.second->outputs){
			if (modules.find(out) != modules.end() && modules[out] -> type == '&'){
				modules[out] -> memory[each.first] = 'l';
			}
		}
	}
	ll i = 0;
	std::map<std::string, ll> inputMods;
	while (inputMods.size() < 4){
		++i;
		std::deque<std::tuple<std::string, std::string, char>> q;
		for (auto out: brOutputs) q.push_back(std::make_tuple("broadcaster", out, 'l'));
		while (!q.empty()){
			std::tuple<std::string, std::string, char> cur = q.front();
			q.pop_front();
			std::string origin = std::get<0>(cur);
			std::string target = std::get<1>(cur);
			char signal = std::get<2>(cur);

			if (modules.find(target) == modules.end())
				continue;
			
			Module* currentMod = modules.at(target);

			if (currentMod -> type == '%'){
				if (signal == 'l'){
					if (currentMod -> memory.at(currentMod -> name) == 'l'){
					currentMod -> memory.at(currentMod -> name) = 'h';
					for (auto targ: currentMod -> outputs) q.push_back(std::make_tuple(currentMod -> name, targ, 'h'));
				}
					else if (currentMod -> memory.at(currentMod -> name) == 'h'){
					currentMod -> memory.at(currentMod -> name) = 'l';
					for (auto targ: currentMod -> outputs) q.push_back(std::make_tuple(currentMod -> name, targ, 'l'));
				}
				}
			}
			else {
				currentMod -> memory[origin] = signal;
				char out;
				ll highs = 0;
				for (auto x: currentMod -> memory)
					if (x.second == 'h') ++highs;
				if (highs == currentMod -> memory.size()) out = 'l';
				else out = 'h';
				for (auto x: currentMod -> outputs) q.push_back(std::make_tuple(currentMod -> name, x, out));
				if (currentMod -> name == "ll"){
					for (auto x: currentMod -> memory)
						if (x.second == 'h'){
							if (inputMods.find(x.first) == inputMods.end()){
								inputMods.insert(std::make_pair(x.first, i));
							}
						}
				}
			}

		}
	}
	ll ans = 1;
	for (auto x: inputMods) ans = std::lcm(ans, x.second);
	std::cout << "Part 2: " << ans << std::endl;
	input.close();
}
void day20(void){
	day20_1();
	day20_2();
}
