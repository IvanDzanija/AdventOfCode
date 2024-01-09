//
//  Day16.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <queue>
#include <set>
#include <deque>
#include <utility>

int energized2(std::vector<std::string> grid, int a, int b, int c, int d){
	int startq[4] = {a, b, c, d};
	std::deque< int > q (startq, startq + 4);
	std::set< std::vector<int> > seen;

	while (!q.empty()){
		int r = q.front();
		q.pop_front();
		int c = q.front();
		q.pop_front();
		int dr = q.front();
		q.pop_front();
		int dc = q.front();
		q.pop_front();

		r += dr;
		c += dc;

		if (r < 0 || r >= grid.size() || c < 0 || c >= grid.at(0).size()) continue;

		char ch = grid.at(r).at(c);
		//std::cout << ch << ' '<< r << ' ' << c << ' '<<dr << ' ' << dc << std::endl;

		if (ch == '.' || ch == '-' and dc || ch == '|' and dr){
			int currentV[4] = {r, c, dr, dc};
			std::vector<int> current(currentV, currentV + 4);
			if (seen.find(current) == seen.end()){
				seen.insert(current);
				q.push_back(r);
				q.push_back(c);
				q.push_back(dr);
				q.push_back(dc);
			}
		}
		else if (ch == '/'){
			int temp = dr;
			dr = - dc;
			dc = - temp;
			int currentV[4] = {r, c, dr, dc};
			std::vector<int> current(currentV, currentV + 4);
			if (seen.find(current) == seen.end()){
				seen.insert(current);
				q.push_back(r);
				q.push_back(c);
				q.push_back(dr);
				q.push_back(dc);
			}
		}
		else if (ch == '\\'){
			int temp = dr;
			dr = dc;
			dc = temp;
			int currentV[4] = {r, c, dr, dc};
			std::vector<int> current(currentV, currentV + 4);
			if (seen.find(current) == seen.end()){
				seen.insert(current);
				q.push_back(r);
				q.push_back(c);
				q.push_back(dr);
				q.push_back(dc);
			}
		}
		else{
			if (ch == '|'){
				dr = - 1;
				dc = 0;
				int currentV1[4] = {r, c, dr, dc};
				std::vector<int> current(currentV1, currentV1 + 4);
				if (seen.find(current) == seen.end()){
					seen.insert(current);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}
				dr = 1;
				dc = 0;
				int currentV2[4] = {r, c, dr, dc};
				std::vector<int> current2(currentV2, currentV2 + 4);
				if (seen.find(current2) == seen.end()){
					seen.insert(current2);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}
			}
			else{
				dr = 0;
				dc = -1;
				int currentV1[4] = {r, c, dr, dc};
				std::vector<int> current1(currentV1, currentV1 + 4);
				if (seen.find(current1) == seen.end()){
					seen.insert(current1);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}
				dr = 0;
				dc = 1;
				int currentV2[4] = {r, c, dr, dc};
				std::vector<int> current2(currentV2, currentV2 + 4);
				if (seen.find(current2) == seen.end()){
					seen.insert(current2);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}

			}

		}
	}
	std::set<std::pair<int, int> > set;
	for (auto el : seen)
		set.insert(std::make_pair(el.at(0), el.at(1)));
	return set.size();
}

int energized1(std::vector<std::string> grid){
	int startq[4] = {0, -1, 0, 1};
	std::deque< int > q (startq, startq + 4);
	std::set< std::vector<int> > seen;

	while (!q.empty()){
		int r = q.front();
		q.pop_front();
		int c = q.front();
		q.pop_front();
		int dr = q.front();
		q.pop_front();
		int dc = q.front();
		q.pop_front();

		r += dr;
		c += dc;

		if (r < 0 || r >= grid.size() || c < 0 || c >= grid.at(0).size()) continue;

		char ch = grid.at(r).at(c);
		//std::cout << ch << ' '<< r << ' ' << c << ' '<<dr << ' ' << dc << std::endl;

		if (ch == '.' || ch == '-' and dc || ch == '|' and dr){
			int currentV[4] = {r, c, dr, dc};
			std::vector<int> current(currentV, currentV + 4);
			if (seen.find(current) == seen.end()){
				seen.insert(current);
				q.push_back(r);
				q.push_back(c);
				q.push_back(dr);
				q.push_back(dc);
			}
		}
		else if (ch == '/'){
			int temp = dr;
			dr = - dc;
			dc = - temp;
			int currentV[4] = {r, c, dr, dc};
			std::vector<int> current(currentV, currentV + 4);
			if (seen.find(current) == seen.end()){
				seen.insert(current);
				q.push_back(r);
				q.push_back(c);
				q.push_back(dr);
				q.push_back(dc);
			}
		}
		else if (ch == '\\'){
			int temp = dr;
			dr = dc;
			dc = temp;
			int currentV[4] = {r, c, dr, dc};
			std::vector<int> current(currentV, currentV + 4);
			if (seen.find(current) == seen.end()){
				seen.insert(current);
				q.push_back(r);
				q.push_back(c);
				q.push_back(dr);
				q.push_back(dc);
			}
		}
		else{
			if (ch == '|'){
				dr = - 1;
				dc = 0;
				int currentV1[4] = {r, c, dr, dc};
				std::vector<int> current(currentV1, currentV1 + 4);
				if (seen.find(current) == seen.end()){
					seen.insert(current);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}
				dr = 1;
				dc = 0;
				int currentV2[4] = {r, c, dr, dc};
				std::vector<int> current2(currentV2, currentV2 + 4);
				if (seen.find(current2) == seen.end()){
					seen.insert(current2);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}
			}
			else{
				dr = 0;
				dc = -1;
				int currentV1[4] = {r, c, dr, dc};
				std::vector<int> current1(currentV1, currentV1 + 4);
				if (seen.find(current1) == seen.end()){
					seen.insert(current1);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}
				dr = 0;
				dc = 1;
				int currentV2[4] = {r, c, dr, dc};
				std::vector<int> current2(currentV2, currentV2 + 4);
				if (seen.find(current2) == seen.end()){
					seen.insert(current2);
					q.push_back(r);
					q.push_back(c);
					q.push_back(dr);
					q.push_back(dc);
				}

			}

		}
	}
	std::set<std::pair<int, int> > set;
	for (auto el : seen)
		set.insert(std::make_pair(el.at(0), el.at(1)));
	return set.size();
}
void day16(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector <std::string> fullSample;
	int result = 0;
	while (getline(input, line)) fullSample.push_back(line);
	for (int i = 0; i < fullSample.size(); ++i){
		result = std::max(result, energized2(fullSample, i, -1, 0, 1));
		result = std::max(result, energized2(fullSample, i, fullSample.at(0).size(), 0, -1));
	}
	for (int i = 0; i < fullSample.at(0).size(); ++i){
		result = std::max(result, energized2(fullSample, -1, i, 1, 0));
		result = std::max(result, energized2(fullSample, fullSample.size(), i, -1, 0));
	}
	std::cout << "Part 1: " << energized1(fullSample) << std::endl;
	std::cout << "Part 2: " << result << std::endl;

}

