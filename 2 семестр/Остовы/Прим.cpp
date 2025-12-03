#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include<fstream>
#include <cctype>
#include <iomanip>
using namespace std;

long long inf = 100000000000;

int leader(int v, vector<short>& p) {
	return (p[v] == v) ? v : p[v] = leader(p[v], p);
}

void unite(int a, int b, vector<short>& p, vector<short>& s) {
	a = leader(a, p);
	b = leader(b, p);
	if (a == b) {
		return;
	}
	if (s[a] > s[b])
		swap(a, b);
	s[b] += s[a];
	p[a] = b;
}

void init(int n, vector<short>& p, vector<short>& s) {
	for (int i = 0; i < n; i++)
		p[i] = i, s[i] = 1;
}

int main() {
	ifstream in("unionday.in");
	ofstream out("unionday.out");
	int n;
	in >> n;
	vector<pair<int, int>> node(n);
	for (int i = 0; i < n; ++i) {
		in >> node[i].first >> node[i].second;
	}
	vector<short> p(n);
	vector<short> s(n, 1);
	vector<vector<int>> g(n, vector<int>(n));
	init(n, p, s);
	for (short i = 0; i < node.size(); ++i) {
		for (short j = i+1; j < node.size(); ++j) {
				int a = node[i].first, b = node[i].second,
					c = node[j].first, d = node[j].second;
				g[i][j]=(a - c) * (a - c) + (b - d) * (b - d);
				g[j][i] = g[i][j];
			
		}
	}
	int inf = 1000000000;
	vector<bool> used(n);
	double ans = 0;
	vector<int> min_e(n, inf), sel_e(n, -1);
	min_e[0] = 0;
	for (int i = 0; i < n; ++i) {
		int v = -1;
		for (int j = 0; j < n; ++j)
			if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
				v = j;

		used[v] = true;
		if (sel_e[v] != -1)
			ans+=sqrt(g[v][sel_e[v]]);

		for (int to = 0; to < n; ++to)
			if (g[v][to] < min_e[to]) {
				min_e[to] = g[v][to];
				sel_e[to] = v;
			}
	}
	out << std::fixed << std::setprecision(3);
	out << ans;
	return 0;
}