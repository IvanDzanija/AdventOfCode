//
//  Day22.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <algorithm>
#include <sstream>

bool overlaps(std::vector<int> firstBrick, std::vector<int> secondBrick){
	if (std::max(firstBrick.at(0), secondBrick.at(0)) <= std::min(firstBrick.at(3), secondBrick.at(3))
		&& std::max(firstBrick.at(1), secondBrick.at(1)) <= std::min(firstBrick.at(4), secondBrick.at(4)))
			return true;
	else return false;

}

void day22_1(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::vector<int>> bricks;
	while (getline(input,line)){
		line.at(line.find('~')) = ',';
		std::stringstream ss(line);
		std::string coord;
		std::vector<int> brick;
		while (getline(ss, coord, ',')){
			brick.push_back(std::stoi(coord));
		}
		bricks.push_back(brick);
	}
	std::sort(bricks.begin(), bricks.end(), [](const std::vector<int>& a, const std::vector<int>& b) {return a.at(2) < b.at(2);});
	// for (auto x : bricks){
	//     for (auto y : x){
	//         std::cout << y << ' ';
	//     }
	//     std::cout << std::endl;
	// }
	for (int i = 0; i < bricks.size(); ++i){
		int max_z = 1;
		std::vector<int> brick = bricks.at(i);
		std::vector<std::vector<int>> current (bricks.begin(), bricks.begin() + i);
		for (auto x : current){
			if (overlaps(brick, x)){
				max_z = std::max(x.at(5) + 1, max_z);
			}
		}
		bricks.at(i).at(5) += max_z - bricks.at(i).at(2);
		bricks.at(i).at(2) = max_z;
	}
	//posibly need to sort again, no need!
	std::map<int, std::set<int>> brickSupportsBricks;
	std::map<int, std::set<int>> brickSupportedByBricks;

	for (int i = 0; i < bricks.size(); ++i){
		std::vector<int> above = bricks.at(i);
		for (int j = 0; j < i; ++j){
			 std::vector<int> belove = bricks.at(j);
			 if (overlaps(above, belove) && above.at(2) - 1 == belove.at(5)){
				brickSupportsBricks[j].insert(i);
				brickSupportedByBricks[i].insert(j);
			 }
		}
	}
	// for (auto x : brickSupportedByBricks){
	//     std::cout << x.first << ": ";
	//     for (auto y: x.second) std::cout << y << ' ';
	//     std::cout << std::endl;
	// }

	int result = 0;
	for (int i = 0; i < bricks.size(); ++i){
		bool check = true;
		for (const auto x: brickSupportsBricks[i]){
			if (brickSupportedByBricks[x].size() < 2){
				check = false;
				break;
			}
		}
		if (check) ++result;
	}
	std::cout << "Part 1: " << result << std::endl;
	input.close();
}

void day22_2(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<std::vector<int>> bricks;
	while (getline(input,line)){
		line.at(line.find('~')) = ',';
		std::stringstream ss(line);
		std::string coord;
		std::vector<int> brick;
		while (getline(ss, coord, ',')){
			brick.push_back(std::stoi(coord));
		}
		bricks.push_back(brick);
	}
	std::sort(bricks.begin(), bricks.end(), [](const std::vector<int>& a, const std::vector<int>& b) {return a.at(2) < b.at(2);});
	// for (auto x : bricks){
	//     for (auto y : x){
	//         std::cout << y << ' ';
	//     }
	//     std::cout << std::endl;
	// }
	for (int i = 0; i < bricks.size(); ++i){
		int max_z = 1;
		std::vector<int> brick = bricks.at(i);
		std::vector<std::vector<int>> current (bricks.begin(), bricks.begin() + i);
		for (auto x : current){
			if (overlaps(brick, x)){
				max_z = std::max(x.at(5) + 1, max_z);
			}
		}
		bricks.at(i).at(5) += max_z - bricks.at(i).at(2);
		bricks.at(i).at(2) = max_z;
	}
	//posibly need to sort again, no need!
	std::map<int, std::set<int>> brickSupportsBricks;
	std::map<int, std::set<int>> brickSupportedByBricks;

	for (int i = 0; i < bricks.size(); ++i){
		std::vector<int> above = bricks.at(i);
		for (int j = 0; j < i; ++j){
			 std::vector<int> belove = bricks.at(j);
			 if (overlaps(above, belove) && above.at(2) - 1 == belove.at(5)){
				brickSupportsBricks[j].insert(i);
				brickSupportedByBricks[i].insert(j);
			 }
		}
	}
	// for (auto x : brickSupportedByBricks){
	//     std::cout << x.first << ": ";
	//     for (auto y: x.second) std::cout << y << ' ';
	//     std::cout << std::endl;
	// }

	int result = 0;
	for (int i = 0; i < bricks.size(); ++i){
		std::deque<int> q;
		for (const int& j: brickSupportsBricks[i]){
			if (brickSupportedByBricks[j].size() == 1) q.push_back(j);

		}
		std::set<int> seen(q.begin(), q.end());
		seen.insert(i);
		while (!q.empty()){
			int j = q.front();
			q.pop_front();
			for (const int& k: brickSupportsBricks[j]){
				if (!seen.count(k)){
					bool check = true;
					for (const int& l: brickSupportedByBricks[k]){
						if (!seen.count(l)) check = false;
					}
					if (check){
						q.push_back(k);
						seen.insert(k);
					}
				}
			}
		}
		result += seen.size() - 1;
	}
	std::cout << "Part 2: " << result << std::endl;
	input.close();
}
void day22(){
	day22_1();
	day22_2();
}
