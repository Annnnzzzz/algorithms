#include <iostream>
#include <vector>
#include<string>
#include<queue>
#include <deque>
#include <algorithm>
using namespace std;

void adjacency_matrix(vector<vector<int>>& M, int u, int v, int a){
	M[v][u] = a;
}

void adjacency_set(vector<vector<int>>& M, int u, int v, int a) {
	M[v].push_back(u);
}

void DFS(vector<vector<int>>& M, vector<int>&used, int v) {
	used[v] = true;
	for (auto u : M[v]) {
		if (!used[u]) {
			DFS(M, used, u);
		}
	}
}

