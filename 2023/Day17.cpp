//
//  Day17.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <queue>
#include <map>
#include <tuple>
#include <set>

int dijkstra_part1(std::vector<std::vector<int> > grid){
	int result = 0;
	std::set< std::tuple<int, int, int, int, int> > seen;
	std::priority_queue<std::tuple<int, int, int, int, int, int>, std::vector<std::tuple<int, int, int, int, int, int>>, std::greater<std::tuple<int, int, int, int, int, int> > > pq;
	pq.push(std::make_tuple(0, 0, 0, 0, 0, 0));

	while (!pq.empty()){
		auto [h, r, c, dr, dc, n] = pq.top();
		pq.pop();
		if (r == grid.size() - 1 && c == grid.at(0).size() - 1) return h;

		if (seen.count(std::make_tuple(r, c, dr, dc, n)))
			continue;
		
		seen.insert(std::make_tuple(r, c, dr, dc, n));
		if (n < 3 && (dr != 0 || dc != 0)){
			int nr = r + dr;
			int nc = c + dc;
			if ( nr >= 0 &&  nr < grid.size() && nc >= 0 && nc< grid.at(0).size()){
				pq.push(std::make_tuple(h + grid.at(nr).at(nc), nr, nc, dr, dc, n + 1));
			}
		}
		
		std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
		for (auto [ndr, ndc] : directions) {
			if (std::make_pair(ndr, ndc) != std::make_pair(dr, dc) && std::make_pair(ndr, ndc) != std::make_pair(-dr, -dc)) {
				int nr = r + ndr;
				int nc = c + ndc;
				if (0 <= nr && nr < grid.size() && 0 <= nc && nc < grid[0].size()) {
					pq.push(std::make_tuple(h + grid[nr][nc], nr, nc, ndr, ndc, 1));
				}
			}
		}
	}

	return result;


	

}

int dijkstra_part2(std::vector<std::vector<int> > grid){
	int result = 0;
	std::set< std::tuple<int, int, int, int, int> > seen;
	std::priority_queue<std::tuple<int, int, int, int, int, int>, std::vector<std::tuple<int, int, int, int, int, int>>, std::greater<std::tuple<int, int, int, int, int, int> > > pq;
	pq.push(std::make_tuple(0, 0, 0, 0, 0, 0));

	while (!pq.empty()){
		auto [h, r, c, dr, dc, n] = pq.top();
		pq.pop();
		if (r == grid.size() - 1 && c == grid.at(0).size() - 1 && n > 3) return h;

		if (seen.count(std::make_tuple(r, c, dr, dc, n)))
			continue;
		
		seen.insert(std::make_tuple(r, c, dr, dc, n));
		if (n < 10 && (dr != 0 || dc != 0)){
			int nr = r + dr;
			int nc = c + dc;
			if ( nr >= 0 &&  nr < grid.size() && nc >= 0 && nc< grid.at(0).size()){
				pq.push(std::make_tuple(h + grid.at(nr).at(nc), nr, nc, dr, dc, n + 1));
			}
		}
		if (n >= 4 || std::make_pair(0,0) == std::make_pair(dr,dc)){
			std::vector<std::pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
			for (auto [ndr, ndc] : directions) {
				if (std::make_pair(ndr, ndc) != std::make_pair(dr, dc) && std::make_pair(ndr, ndc) != std::make_pair(-dr, -dc)) {
					int nr = r + ndr;
					int nc = c + ndc;
					if (0 <= nr && nr < grid.size() && 0 <= nc && nc < grid[0].size()) {
						pq.push(std::make_tuple(h + grid[nr][nc], nr, nc, ndr, ndc, 1));
					}
				}
			}
		}
	}
	return result;
}

void day17(void){
	std::ifstream inputFile("input.txt");
	std::string currentLine;
	std::vector <std::vector<int> > fullInput;
	while (getline(inputFile,currentLine)){
		std::vector<int> row;
		for (char c : currentLine) row.push_back(c - '0');
		fullInput.push_back(row);
	}
	std::cout << "Part 1: " << dijkstra_part1(fullInput) << std::endl;
	std::cout << "Part 2: "<< dijkstra_part2(fullInput) << std::endl;
}
