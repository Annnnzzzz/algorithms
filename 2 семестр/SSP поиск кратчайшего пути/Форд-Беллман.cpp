#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <set>
#include<fstream>
#include <cctype>
using namespace std;

struct edge {
	int a, b, cost;
};

int n, m, v;
vector<edge> e;
const int INF = 1000000000;

//Точно знаем что отриц цикла нет
void solve(int t, vector<int> &p) {
	vector<int> d(n, INF);
	d[v] = 0;
	for (;;) {
		bool any = false;
		for (int j = 0; j < m; ++j)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = d[e[j].a] + e[j].cost;
					any = true;
				}
		if (!any)  break;
	}
	if (d[t] == INF)
		cout << "No path from " << v << " to " << t << ".";
	else {
		vector<int> path;
		for (int cur = t; cur != -1; cur = p[cur])
			path.push_back(cur);
		reverse(path.begin(), path.end());

		cout << "Path from " << v << " to " << t << ": ";
		for (size_t i = 0; i < path.size(); ++i)
			cout << path[i] << ' ';
	}
}

//Проверка на отриц цикл
void find_cycle() {
	vector<int> d(n, INF);
	vector<int> p (n, -1);
	d[v] = 0;
	int x=-1;
	for (int i=0;i<n; ++i) {
		x=-1;
		for (int j = 0; j < m; ++j)
			if (d[e[j].a] < INF)
				if (d[e[j].b] > d[e[j].a] + e[j].cost) {
					d[e[j].b] = d[e[j].a] + e[j].cost;
					p[e[j].b] = e[j].a;
					x=e[j].b;
				}
		if (x==-1)  break;
	}
	if (x==-1)
		cout << "No negative cycle from"<<v;
	else {
		int y = x;
		for (int i=0; i<n; ++i)
			y = p[y];
 
		vector<int> path;
		for (int cur=y; ; cur=p[cur]) {
			path.push_back (cur);
			if (cur == y && path.size() > 1)  break;
		}
		reverse (path.begin(), path.end());
 
		cout << "Negative cycle: ";
		for (size_t i=0; i<path.size(); ++i)
			cout << path[i] << ' ';
	}
}
//если несколько КС запусакть для проверки циклов во всех КС
