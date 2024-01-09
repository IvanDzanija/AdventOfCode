//
//  Day21.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include <vector>
#include <tuple>
#include <queue>
#include <set>
#include <set>
using ll = int64_t;



ll fill(std::tuple<ll, ll, ll> startCount, std::vector<std::string> grid, std::pair<ll, ll> start, ll steps){
	std::set<std::pair<ll, ll>> ans;
	std::set<std::pair<ll,ll>> seen;
	auto [sr, sc, ss] = startCount;
	seen.insert(std::make_pair(sr, sc));
	std::queue<std::tuple<ll,ll, ll>> q;
	q.push(startCount);
	while (!q.empty()){
		auto [r, c, s] = q.front();
		q.pop();
		if (s % 2 == 0) ans.insert(std::make_pair(r, c));
		if (s == 0) continue;
		std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
		for (const auto x : directions){
			ll nr = r + x.first;
			ll nc = c + x.second;
			if (nr < 0 || nr >= grid.size() || nc < 0 || nc >= grid.at(0).length() || grid.at(nr).at(nc) == '#'
				|| seen.count(std::make_pair(nr, nc)))
				continue;
			seen.insert(std::make_pair(nr, nc));
			q.push(std::make_tuple(nr, nc, s - 1));
		}
	}
	return ans.size();
}
void day21_1(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::string> grid;
	std::pair<ll, ll> start;
	ll i = 0;
	while (getline(input,line)){
		grid.push_back(line);
		for (auto ch : line){
			if (ch == 'S') start = std::make_pair(i, line.find(('S')));
		}
		++i;
	}
	//std::cout << start.first << ' ' << start.second << std::endl;
	std::set<std::pair<ll, ll>> ans;
	std::set<std::pair<ll,ll>> seen;
	seen.insert(start);
	std::deque<std::tuple<ll,ll, ll>> q;
	q.push_back(std::make_tuple(start.first, start.second, 64));
	while (!q.empty()){
		auto [r, c, s] = q.front();
		q.pop_front();
		if (s % 2 == 0) ans.insert(std::make_pair(r, c));
		if (s == 0) continue;
		std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		for (auto x: directions){
			ll nr = r + x.first;
			ll nc = c + x.second;
			if (nr >= 0 && nr < grid.size() && nc >= 0 && nc < grid.at(0).length() && grid.at(nr).at(nc) != '#' && seen.find(std::make_pair(nr, nc)) == seen.end()){
				seen.insert(std::make_pair(nr, nc));
				q.push_back(std::make_tuple(nr, nc, s - 1));
			}
			else continue;
		}
	}
	std::cout <<"Part 1: " << (ans.size()) << std::endl;
	input.close();
}

void day21_2(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::string> grid;
	std::pair<ll, ll> start;
	ll steps;
	ll i = 0;
	steps = 26501365;
	while (getline(input,line)){
		grid.push_back(line);
		for (auto ch : line){
			if (ch == 'S') start = std::make_pair(i, line.find(('S')));
		}
		++i;
	}
	//std::cout << start.first << ' ' << start.second << std::endl;
	ll grid_width = steps / grid.size() - 1;
	ll odd_grids = pow(grid_width / 2 * 2 + 1, 2);
	ll even_grids = pow((grid_width + 1) / 2 * 2, 2);
	//std::cout << grid_width << ' ' << odd_grids << ' ' << even_grids << std::endl;
	
	ll odd_pts = fill(std::make_tuple(start.first, start.second, grid.size() * 2 + 1),grid,start,steps);
	ll even_pts = fill(std::make_tuple(start.first, start.second, grid.size() * 2),grid,start,steps);
	//std::cout << odd_pts << ' ' << even_pts << std::endl;
	
	ll topCorner = fill(std::make_tuple(grid.size() - 1, start.second, grid.size() - 1),grid,start,steps);
	ll bottomCorner = fill(std::make_tuple(0, start.second, grid.size() - 1),grid,start,steps);
	ll rightCorner = fill(std::make_tuple(start.first, 0, grid.size() - 1),grid,start,steps);
	ll leftCorner = fill(std::make_tuple(start.first, grid.size() - 1, grid.size() - 1),grid,start,steps);
	//std::cout << topCorner << ' ' << bottomCorner << ' ' << rightCorner << ' ' << leftCorner << std::endl;
	
	ll trSmall = fill(std::make_tuple(grid.size() - 1, 0, grid.size() / 2 - 1),grid,start,steps);
	ll tlSmall = fill(std::make_tuple(grid.size() - 1, grid.size() - 1, grid.size() / 2 - 1),grid,start,steps);
	ll brSmall = fill(std::make_tuple(0, 0 , grid.size() / 2 - 1),grid,start,steps);
	ll blSmall = fill(std::make_tuple(0, grid.size() - 1, grid.size() / 2 - 1),grid,start,steps);
	//std::cout << trSmall << ' ' << tlSmall << ' ' << brSmall << ' ' << blSmall << std::endl;
	
	ll trLarge = fill(std::make_tuple(grid.size() - 1, 0, grid.size() * 3 / 2 - 1),grid,start,steps);
	ll tlLarge = fill(std::make_tuple(grid.size() - 1, grid.size() - 1, grid.size() * 3 / 2 - 1),grid,start,steps);
	ll brLarge = fill(std::make_tuple(0, 0 , grid.size() * 3 / 2 - 1),grid,start,steps);
	ll blLarge = fill(std::make_tuple(0, grid.size() - 1, grid.size() * 3 / 2 - 1),grid,start,steps);
	//std::cout << trLarge << ' ' << tlLarge << ' ' << blLarge << ' ' << brLarge << std::endl;
	
	ll result = odd_grids * odd_pts + even_grids * even_pts + topCorner + bottomCorner + rightCorner + leftCorner;
	result += (grid_width + 1) * (trSmall + tlSmall + brSmall + blSmall);
	result += grid_width * (trLarge + tlLarge + brLarge + blLarge);
	std::cout << "Part 2: " << result << std::endl;
	input.close();
}

void day21(void){
	day21_1();
	day21_2();
}
