//
//  Day10.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>
#include <utility>
#include <set>
#include <tuple>
using ll = int64_t;

std::vector<std::string> grid;
std::set<std::pair<ll, ll>> seen;
ll sr, sc;
char sCh;

ll bfs(){
	std::vector<ll> start (6,0);
	std::deque<std::pair<ll, ll>> q;
	q.push_back(std::make_pair(sr, sc));
	while (!q.empty()){
		std::pair<ll, ll> pos = q.front();
		ll r = pos.first;
		ll c = pos.second;
		char currentCh = grid.at(r).at(c);
		q.pop_front();

		// std::cout << currentCh << std::endl;
		if (seen.count(pos)) continue;
		seen.insert(pos);
		if (r > 0 and (currentCh == 'S' || currentCh == '|' or currentCh == 'J' or currentCh == 'L') &&
			(grid.at(r - 1).at(c) == 'F' || grid.at(r - 1).at(c) == '|' || grid.at(r - 1).at(c) == '7')){
			q.push_back(std::make_pair(r - 1, c));
			if (currentCh == 'S'){
				start[0] += 1;
				start[3] += 1;
				start[2] += 1;
			}
				

		}
		if (r < grid.size() - 1 and (currentCh == 'S' || currentCh == '|' or currentCh == '7' or currentCh == 'F') &&
			(grid.at(r + 1).at(c) == 'J' || grid.at(r + 1).at(c) == '|' || grid.at(r + 1).at(c) == 'L')){
			q.push_back(std::make_pair(r + 1, c));
			if (currentCh == 'S'){
				start[0] += 1;
				start[4] += 1;
				start[5] += 1;
			}
		}
		if (c > 0 and (currentCh == 'S' || currentCh == '-' or currentCh == '7' or currentCh == 'J') &&
			(grid.at(r).at(c - 1) == 'F' || grid.at(r).at(c - 1) == '-' || grid.at(r).at(c - 1) == 'L')){
			q.push_back(std::make_pair(r, c - 1));
			if (currentCh == 'S'){
				start[1] += 1;
				start[3] += 1;
				start[4] += 1;
			}
				
		}
		if (c < grid.at(0).length() - 1 and (currentCh == 'S' || currentCh == '-' or currentCh == 'L' or currentCh == 'F') &&
			(grid.at(r).at(c + 1) == 'J' || grid.at(r).at(c + 1) == '-' || grid.at(r).at(c + 1) == '7')){
			q.push_back(std::make_pair(r, c + 1));
			if (currentCh == 'S'){
				start[1] += 1;
				start[5] += 1;
				start[2] += 1;
			}
				
		}
	}
	int max = 0;
	int index = 0;
	for (int i = 0; i < start.size(); ++i){
		if (start.at(i) > max){
			max = start.at(i);
			index = i;
		}
	}
	if (index == 0) sCh = '|';
	if (index == 1) sCh = '-';
	if (index == 2) sCh = 'L';
	if (index == 3) sCh = 'J';
	if (index == 4) sCh = '7';
	if (index == 5) sCh = 'F';
	return seen.size() / 2;
}


void day10(void){
	std::ifstream input("input.txt");
	std::string line;
	while (getline(input,line)){
		if (line.find('S') != std::string::npos){
			sr = grid.size();
			sc = line.find('S');
		}
		grid.push_back(line);
	}
	std::cout <<"Part 1: " << bfs() << std::endl;
	grid.at(sr).at(sc) = sCh;
	for (ll i = 0; i < grid.size(); ++i){
		for (ll j = 0; j < grid.size(); ++j){
			std::pair<ll,ll> currentPos = std::make_pair(i,j);
			if (seen.count(currentPos)) continue;
			else grid.at(i).at(j) = '.';
		}
	}
	// add solution using shoelaces formula and Pick's theorem
	std::set<std::pair<ll, ll>> out;
	for (int i = 0; i < grid.size(); ++i){
		std::string row = grid.at(i);
		bool inside = false;
		bool along = false;
		for (int j = 0; j < grid.size(); ++j){
			char ch = row.at(j);
			if (ch == '|'){
				inside = !inside;
			}
			else if (ch == '-'){
			}
			else if ((ch == 'L' || ch == 'F')){
				along = (ch == 'L');
			}
			else if ((ch == '7' || ch == 'J')){
				if (along && ch != 'J' || !along && ch != '7') inside = !inside;
				along = false;
			}
			if (!inside){
				out.insert(std::make_pair(i,j));
			}
		}
	}
	int count = 0;
	for (int i = 0; i < grid.size(); ++i){
		for (int j = 0; j < grid.size(); ++j){
			std::pair <int, int> currentP (i,j);
			if (seen.count(currentP) || out.count(currentP)) ++count;
		}
	}
	std::cout << "Part 2: " << (grid.size() * grid.at(0).size()) - count << std::endl;

}
