//
//  Day23.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <tuple>
#include <set>
#include <stack>
#include <climits>
#include <utility>


std::vector<std::string> grid23;
std::pair<int, int> start23;
std::pair<int, int> end23;
std::set<std::pair<int,int>> points23;
std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>> graph23;



std::set<std::pair<int, int>> seenDFS;
int dfs(std::pair<int, int> pt){
	if (pt == end23) return 0;
	int m = INT_MIN;
	seenDFS.insert(pt);
	for (auto nx : graph23[pt]){
		if (seenDFS.find(nx.first) == seenDFS.end())
			m = std::max(m, dfs(nx.first) + graph23[pt].at(nx.first));
	}
	seenDFS.erase(pt);
	return m;

}
void day23_1(void){
	std::ifstream input("input.txt");
	std::string line;
	while (getline(input,line)) grid23.push_back(line);
	start23 = std::make_pair(0, grid23.at(0).find('.'));
	end23 = std::make_pair(grid23.size() - 1, grid23.at(grid23.size() - 1).find('.'));
	points23.insert(start23);
	points23.insert(end23);
	
	for (int r = 0; r < grid23.size(); ++r){
		for (int c = 0; c < grid23.size(); ++c){
			if (grid23.at(r).at(c) == '#') continue;
			int neighbors = 0;
			std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
			for (auto x: directions){
				int nr = r + x.first;
				int nc = c + x.second;
				if (nr >= 0 && nr < grid23.size() && nc >= 0 && nc < grid23.at(0).length() && grid23.at(nr).at(nc) != '#') ++neighbors;
				if (neighbors >= 3) points23.insert(std::make_pair(r, c));
			}
		}
	}
	//for (auto x : points) std::cout << x.first << ' ' << x.second << std::endl;
	
	std::map<char, std::vector<std::pair<int, int>>> dirs = {
		{'^', {std::make_pair(-1, 0)}},
		{'v', {std::make_pair(1, 0)}},
		{'<', {std::make_pair(0, -1)}},
		{'>', {std::make_pair(0, 1)}},
		{'.', {std::make_pair(-1, 0), std::make_pair(1, 0), std::make_pair(0, -1), std::make_pair(0, 1)}}
	};
	for (auto x : points23){
		std::stack<std::tuple<int, int, int>> stack;
		std::set<std::pair<int, int>> seen;
		stack.push(std::make_tuple(0, x.first, x.second));
		seen.insert(std::make_pair(x.first, x.second));
		while (!stack.empty()){
			auto [n, r, c] = stack.top();
			stack.pop();
			std::pair<int, int> currentPos(r, c);
			//std::cout << currentPos.first << ' ' << currentPos.second << std::endl;;
			if (n != 0 && points23.find(currentPos) != points23.end()){
				graph23[x][currentPos] = n;
				continue;
			}
			for (std::pair<int, int> dir : dirs.at(grid23.at(r).at(c))) {
				int nr = r + dir.first;
				int nc = c + dir.second;
				std::pair<int, int> newPos(nr, nc);
				//std::cout << newPos.first << ' ' << newPos.second << std::endl;;
				if (nr >= 0 && nr < grid23.size() && nc >= 0 && nc < grid23[0].size() && grid23[nr][nc] != '#' && seen.find(newPos) == seen.end()) {
					stack.push(std::make_tuple(n + 1, nr, nc));
					seen.insert(std::make_pair(nr, nc));
				}
			}
		}
	}
	std::cout << "Part 1: " << dfs(start23) << std::endl;
	input.close();
	grid23.erase(grid23.begin(), grid23.end());
	start23.first = 0;
	start23.second = 0;
	end23.first = 0;
	end23.second = 0;
	points23.erase(points23.begin(), points23.end());
	graph23.erase(graph23.begin(), graph23.end());
}




void day23_2(void){
	std::ifstream input("input.txt");
	std::string line;
	while (getline(input,line)) grid23.push_back(line);
	start23 = std::make_pair(0, grid23.at(0).find('.'));
	end23 = std::make_pair(grid23.size() - 1, grid23.at(grid23.size() - 1).find('.'));
	points23.insert(start23);
	points23.insert(end23);
	
	for (int r = 0; r < grid23.size(); ++r){
		for (int c = 0; c < grid23.size(); ++c){
			if (grid23.at(r).at(c) == '#') continue;
			int neighbors = 0;
			std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
			for (auto x: directions){
				int nr = r + x.first;
				int nc = c + x.second;
				if (nr >= 0 && nr < grid23.size() && nc >= 0 && nc < grid23.at(0).length() && grid23.at(nr).at(nc) != '#') ++neighbors;
				if (neighbors >= 3) points23.insert(std::make_pair(r, c));
			}
		}
	}
	//for (auto x : points) std::cout << x.first << ' ' << x.second << std::endl;

	std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	for (auto x : points23){
		std::stack<std::tuple<int, int, int>> stack;
		std::set<std::pair<int, int>> seen;
		stack.push(std::make_tuple(0, x.first, x.second));
		seen.insert(std::make_pair(x.first, x.second));
		while (!stack.empty()){
			auto [n, r, c] = stack.top();
			stack.pop();
			std::pair<int, int> currentPos(r, c);
			//std::cout << currentPos.first << ' ' << currentPos.second << std::endl;;
			if (n != 0 && points23.find(currentPos) != points23.end()){
				graph23[x][currentPos] = n;
				continue;
			}
			for (std::pair<int, int> dir : directions) {
				int nr = r + dir.first;
				int nc = c + dir.second;
				std::pair<int, int> newPos(nr, nc);
				//std::cout << newPos.first << ' ' << newPos.second << std::endl;;
				if (nr >= 0 && nr < grid23.size() && nc >= 0 && nc < grid23[0].size() && grid23[nr][nc] != '#' && seen.find(newPos) == seen.end()) {
					stack.push(std::make_tuple(n + 1, nr, nc));
					seen.insert(std::make_pair(nr, nc));
				}
			}
		}
	}
	std::cout << "Part 2: " << dfs(start23) << std::endl;
	input.close();
}
void day23(void){
	day23_1();
	day23_2();
}

