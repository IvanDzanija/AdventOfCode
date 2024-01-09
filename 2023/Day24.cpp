//
//  Day24.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//
#define EIGEN_NO_DEBUG
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <array>
#include <algorithm>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>
#include <unordered_set>
#include <cassert>
#include <sstream>
#include <queue>
#include <bitset>
#include <Eigen/Core>
#include <Eigen/Dense>

using ll = int64_t;

class Hailstone{

	public:
		double sx, sy, sz, vx, vy, vz, a, b, c;
		Hailstone(double sx, double sy, double sz, double vx, double vy, double vz){
			this -> sx = sx;
			this -> sy = sy;
			this -> sz = sz;
			this -> vx = vx;
			this -> vy = vy;
			this -> vz = vz;
			this -> a = vy;
			this -> b = -vx;
			this -> c = vy * sx - vx * sy;
		}
		Hailstone(){

		}
};
void day24_1(void){
	std::ifstream input("input.txt");
	std::string line;
	std::vector<Hailstone> hailstones;
	ll ans = 0;
	while (getline(input,line)){
		line.at(line.find('@')) = ',';
		std::stringstream startPos(line);
		std::string temp;
		std::vector<ll> currentHail;
		while (getline(startPos, temp, ',')){
			ll currCoord = std::stoll(temp);
			currentHail.push_back(currCoord);
			// std::cout << currCoord << std::endl;
		}
		double sx = currentHail.at(0);
		double sy = currentHail.at(1);
		double sz = currentHail.at(2);
		double vx = currentHail.at(3);
		double vy = currentHail.at(4);
		double vz = currentHail.at(5);
		hailstones.push_back(Hailstone(sx, sy, sz, vx, vy, vz));
	}
	// for (auto x : hailstones){
	//     std::cout << x.a << ' ' << x.b << ' ' <<x.c << std::endl;
	// }
	for (ll i = 0; i < hailstones.size(); ++i){
		Hailstone h1 = hailstones.at(i);
		for (ll j = 0;  j < i; ++j){
			Hailstone h2 = hailstones.at(j);
			if (h1.a * h2.b == h2.a * h1.b) continue;
			double x = (h1.c * h2.b - h2.c * h1.b) / (h1.a * h2.b - h2.a * h1.b);
			double y = -(h1.c * h2.a - h2.c * h1.a) / (h1.a * h2.b - h2.a * h1.b);
			//std::cout << x << ' ' << y << std::endl;
			if (x >= 200000000000000 && x <= 400000000000000 && y >= 200000000000000 && y <= 400000000000000 &&
				(x - h1.sx) * h1.vx >= 0 && (y - h1.sy) * h1.vy >= 0 && (x - h2.sx) * h2.vx >= 0 && (y - h2.sy) * h2.vy >= 0){
				++ans;
			}
		}
	}
	std::cout << "Part 1: " << ans << std::endl;
}
void day24(void){
	day24_1();
}
