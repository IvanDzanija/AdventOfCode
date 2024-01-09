//
//  Day25.cpp
//  2023
//
//  Created by Ivan Dzanija on 09.01.2024..
//

#include <iostream>
#include <vector>
#include <vector>
#include <map>
#include <queue>
#include <deque>
#include <numeric>
#include <limits>
#include <fstream>
#include <cmath>
#include <sstream>

class Graph {
private:
	std::unordered_map<int, std::unordered_map<int, int>> G;
	std::unordered_map<int, int> parent;

public:
	Graph(std::unordered_map<int, std::unordered_map<int, int>> G) {
		this->G = G;
		this->parent = {};
		for (auto& n : this->G) {
			this->parent[n.first] = -1;
		}
	}

	bool bfs(int s, int t) {
		this->parent.clear();
		for (auto& n : this->G) {
			this->parent[n.first] = -1;
		}
		this->parent[s] = s;
		std::queue<int> Q;
		Q.push(s);
		while (!Q.empty()) {
			int n = Q.front();
			Q.pop();
			for (auto& e : this->G[n]) {
				int c = e.second;
				if (c > 0 && this->parent[e.first] == -1) {
					this->parent[e.first] = n;
					Q.push(e.first);
				}
			}
		}
		return this->parent[t] != -1;
	}

	int minCut(int s, int t) {
		for (auto& v : this->G) {
			for (auto& k : v.second) {
				this->G[v.first][k.first] = 1;
			}
		}
		int maxFlow = 0;
		while (this->bfs(s, t)) {
			int flow = std::numeric_limits<int>::max();
			int n = t;
			while (n != s) {
				flow = std::min(flow, this->G[this->parent[n]][n]);
				n = this->parent[n];
			}
			maxFlow += flow;
			int v = t;
			while (v != s) {
				int u = this->parent[v];
				this->G[u][v] -= flow;
				this->G[v][u] += flow;
				v = u;
			}
		}
		return maxFlow;
	}

	int solve() {
		int g1 = 0;
		for (auto& p : this->parent) {
			if (p.second != -1) {
				g1++;
			}
		}
		return (this->G.size() - g1) * g1;
	}
};
void day25(void){
	std::ifstream input("input.txt");
	std::string line;
	std
	while (getline(input,line)){
		std::string node = line.substr(0, line.find(':'));
		std::string connectingNodes = line.substr(line.find(':') + 1);
		std::stringstream ss(connectingNodes);
		while(get)
	}
}

