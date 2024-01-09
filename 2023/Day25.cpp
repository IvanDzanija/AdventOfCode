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
public:
	std::map<std::string, std::map<std::string, int>> graph;
	std::map<std::string, std::string> parent;
	Graph(std::map<std::string, std::map<std::string, int>> graph) {
		this->graph = graph;
		for (auto& n : this->graph) {
			this->parent[n.first] = "";
		}
	}

	bool bfs(std::string source, std::string sink) {
		for (auto& n : this->graph) {
			this->parent[n.first] = "";
		}
		this->parent[source] = source;
		std::queue<std::string> Q;
		Q.push(source);
		while (!Q.empty()) {
			std::string n = Q.front();
			Q.pop();
			for (auto& e : this->graph[n]) {
				int c = e.second;
				if (c > 0 && this->parent[e.first] == "") {
					this->parent[e.first] = n;
					Q.push(e.first);
				}
			}
		}
		return this->parent[sink] != "";
	}

	int minCut(std::string source, std::string sink) {
		for (auto& v : this->graph) {
			for (auto& k : v.second) {
				this->graph[v.first][k.first] = 1;
			}
		}
		int maxFlow = 0;
		while (this->bfs(source, sink)) {
			int flow = std::numeric_limits<int>::max();
			std::string n = sink;
			while (n != source) {
				flow = std::min(flow, this->graph.at(this -> parent.at(n)).at(n));
				n = this->parent[n];
			}
			maxFlow += flow;
			std::string v = sink;
			while (v != source) {
				std::string u = this->parent[v];
				this->graph[u][v] -= flow;
				this->graph[v][u] += flow;
				v = u;
			}
		}
		return maxFlow;
	}

	int solve() {
		int g1 = 0;
		for (auto& p : this->parent) {
			if (p.second != "") {
				g1++;
			}
		}
		return (this->graph.size() - g1) * g1;
	}
};
void day25(void){
	std::ifstream input("input.txt");
	std::string line;
	std::map<std::string , std::map<std::string, int>> G;
	while (getline(input,line)){
		std::string node = line.substr(0, line.find(':'));
		std::string connectingNodes = line.substr(line.find(':') + 2);
		std::stringstream ss(connectingNodes);
		std::string connectingNode;
		while(getline(ss, connectingNode, ' ')){
			G[node][connectingNode] = 1;
			G[connectingNode][node] = 1;
		}
	}
//	for (auto x : G){
//		std::cout << x.first << ": ";
//		for (auto y : x.second){
//			std::cout << y.first << "- " << y.second << ", ";
//		}
//		std::cout << std::endl;
//	}
	Graph g(G);
	std::string source = "";
	std::vector<std::string> others;
	for (auto node : g.graph){
		if (source == ""){
			source = node.first;
		}
		else{
			others.push_back(node.first);
		}
	}
	for (std::string sink : others){
		if (g.minCut(source, sink) == 3) break;
	}
	int ans = g.solve();
	std::cout << "Part 1: " << ans << std::endl;
	
}

