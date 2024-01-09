//
//  Day18.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
#include <sstream>
#include <map>
#include <utility>
#include <cmath>

long long dig(std::vector<char> dir, std::vector<long long> len){
	std::map<char, std::pair<long long, long long> > dirs;
	dirs['U'] = std::make_pair(-1, 0);
	dirs['D'] = std::make_pair(1, 0);
	dirs['L'] = std::make_pair(0, -1);
	dirs['R'] = std::make_pair(0, 1);
	std::vector<std::pair<long long, long long> > coords;
	coords.push_back(std::make_pair(0, 0));
	for (long long i = 0; i < len.size(); ++i){
		long long dr = dirs.at(dir.at(i)).first;
		long dc = dirs.at(dir.at(i)).second;
		long long n = len.at(i);
		long long r = coords.at(coords.size() - 1).first;
		long long c = coords.at(coords.size() - 1).second;
		coords.push_back(std::make_pair(r + dr * n, c + dc * n));
	}
	long long A = 0;
	for (long long i = 0; i < coords.size(); ++i)
		A += coords.at(i).first * ((coords).at((i - 1 + coords.size()) % coords.size()).second - (coords).at((i + 1 + coords.size()) % coords.size()).second);
	A = std::abs(A) / 2;
	long long b = 0;
	for (auto el: len) b += el;
	long long i = A - b / 2 + 1;
	return b + i;
	



}
void day18(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<char> dir;
	std::vector<long long> len;
	std::vector<char> color;
	std::vector<long long> len1;
	while (getline(input,line)){
		std::stringstream ss(line);
		std::string str;
		long long c = 0;
		while (getline(ss,str,' ')){
			if (c % 3 == 0) dir.push_back(str.at(0));
			else if (c % 3 == 1) len.push_back(std::stoi(str));
			else if (c % 3 == 2){
				str = str.substr(2, str.length() - 3);
				char c = str.at(str.size() - 1);
				str = str.substr(0, str.length() - 1);
				if (c == '0') color.push_back('R');
				else if (c == '1') color.push_back('D');
				else if (c == '2') color.push_back('L');
				else if (c == '3') color.push_back('U');
				len1.push_back(std::stoi(str, nullptr, 16));
			}
			++c;
		}
	}
	std::cout << "Part 1 = " <<  dig(dir, len) << std::endl;
	std::cout << "Part 2 = " <<  dig(color, len1) << std::endl;
}
