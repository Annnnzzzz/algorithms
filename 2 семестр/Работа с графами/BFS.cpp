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

//обычный BFS с поиском кратчайшего пути
void BFS(vector<vector<int>>& M, vector<int>& used, vector<int>& t,  int s) {
	//cout << v<<" ";
	queue< int> q;
	q.push(s);
	used[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (auto u : M[v]) {
			t[u] = min(t[u], t[v] + 1);
			if (!used[u]) {
				used[u] = true;
				q.push(u);
			}
		}
	}
}

//u.first - вершина, u.second - вес
void BFS_0_1(int s, vector<bool>& used, vector<vector<pair<int, int>>>& M) {
	deque<int> q;
	q.push_back(s);
	used[s] = true;
	while (!q.empty()) {
		int v = q.front();
		q.pop_front();
		for (auto u : M[v]) {
			if (!used[u.first]) {
				used[u.first] = true;
				if (u.second == 0) {
					q.push_front(u.first);
				}
				else {
					q.push_back(u.first);
				}
			}
		}
	}
}

//u.first - вес, u.second - вершина, приоритетная очередь с сортировкой от меньшего к большему по весам
void BFS_different(pair<int, int> s, vector<bool>& used, vector<vector<pair<int, int>>>& M) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push(s);
	used[s.second] = true;
	while (!q.empty()) {
		int v = q.top().second;
		q.pop();
		for (auto u : M[v]) {
			if (!used[u.second]) {
				used[u.second] = true;
				q.push(u);
			}
		}
	}
}


//u.first - вес, u.second - вершина, приоритетная очередь с сортировкой от меньшего к большему по весам
//weight инициализируем INT_MAX, если в итоге weight[i]=INT_MAX, то пути
//из s в i неть
void BFS_min_weight(int s, vector<bool>& used, vector<vector<pair<int, int>>>& M, vector<int>& weight) {
	priority_queue<int, vector<int>, greater<int>> q;
	q.push(s);
	used[s] = true;
	weight[s] = 0;
	while (!q.empty()) {
		int v = q.top();
		q.pop();
		for (auto u : M[v]) {
			if (!used[u.first]) {
				used[u.first] = true;
				weight[u.second] = min(weight[u.second], weight[v] + u.first);
				q.push(u.first);
			}
		}
	}
}