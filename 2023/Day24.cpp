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
 
Eigen::Matrix3d crossMatrix(Eigen::Vector3d v)
{
	Eigen::Matrix3d result;
	result << 0, -v[2], v[1],
		v[2], 0, -v[0],
		-v[1], v[0], 0;
	return result;
}
 
void day24()
{
	struct Hailstone
	{
		Eigen::Vector3d p;
		Eigen::Vector3d v;
	};
 
	std::vector<Hailstone> hailstones;
	std::ifstream input("input.txt");
	std::string line;
	while (getline(input,line)){
		line.at(line.find('@')) = ',';
		std::stringstream startPos(line);
		std::string temp;
		std::vector<ll> currentHail;
		Hailstone h;
		while (getline(startPos, temp, ',')){
			ll currCoord = std::stoll(temp);
			currentHail.push_back(currCoord);
		}
		Eigen::Vector3d tempP;
		Eigen::Vector3d tempV;
		h.p[0] = currentHail.at(0);
		h.p[1] = currentHail.at(2);
		h.p[2] = currentHail.at(2);
		h.v[0] = currentHail.at(3);
		h.v[1] = currentHail.at(4);
		h.v[2] = currentHail.at(5);
		hailstones.push_back(h);
	}
	
	Eigen::MatrixXd M(6, 6);
	Eigen::VectorXd rhs(6);
	rhs.segment<3>(0) = -hailstones[0].p.cross(hailstones[0].v) + hailstones[1].p.cross(hailstones[1].v);
	rhs.segment<3>(3) = -hailstones[0].p.cross(hailstones[0].v) + hailstones[2].p.cross(hailstones[2].v);
	M.block<3, 3>(0, 0) = crossMatrix(hailstones[0].v) - crossMatrix(hailstones[1].v);
	M.block<3, 3>(3, 0) = crossMatrix(hailstones[0].v) - crossMatrix(hailstones[2].v);
	M.block<3, 3>(0, 3) = -crossMatrix(hailstones[0].p) + crossMatrix(hailstones[1].p);
	M.block<3, 3>(3, 3) = -crossMatrix(hailstones[0].p) + crossMatrix(hailstones[2].p);
	Eigen::Vector3d result = M.inverse() * rhs;
	std::cout << "pos: " << result.segment<3>(0) << " vel: " << result.segment<3>(3) << std::endl;
	ll sum = 0;
	for (int i = 0; i < 3; i++)
		sum += ll(result[i]);
	std::cout<< "Part 2: " << sum << std::endl;
}
