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
 
long long inf = 100000000000;
 
struct edges {
	int v, u, w;
	bool operator<(const edges& other) const {
		return w < other.w;
	}
};
int leader(int v, vector<int>& p) {
	return (p[v] == v) ? v : p[v] = leader(p[v], p);
}
 
void unite(int a, int b, vector<int>& p, vector<int>& s) {
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
 
void init(int n, vector<int>& p, vector<int>& s) {
	for (int i = 0; i < n; i++)
		p[i] = i, s[i] = 1;
}
 
int main() {
	ifstream in("maxincycle.in");
	ofstream out("maxincycle.out");
	int n, m, p1, p2;
	in >> n >> m ;
	vector<int> p(n+1);
	vector<edges> edge;
	for (int i = 0; i < m; i++) {
		in >> p1 >> p2;
		edge.push_back({ p1, p2, i });
	}
	vector<int> s(n+1);
	init(n+1, p, s);
	std::sort(edge.begin(), edge.end());
	long long ans = 0;
	vector<int> answer;
	
	for (auto& e : edge) {
		if (leader(e.v, p) != leader(e.u, p)) {
			unite(e.v, e.u, p, s);
			answer.push_back(e.w + 1);
		}
		else {
			ans += 1;
		}
	}
	//cout << "doo";
	out << answer.size() << endl;
	for (int i=0; i < answer.size(); i++) {
		out << answer[i] << " ";
	}
	return 0;
}