#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include<fstream>
using namespace std;
 
int n, l;
vector < vector<int> > g;
vector<int> tin, tout;
vector <int> h(500001, 0);
vector < vector<int> > jmp(500001);
 
void dfs(int v, int p) {
	h[v] = (p == 0 ? 0 : h[p] + 1);
	jmp[v][0] = p;
	for (int i = 1; i <= l; ++i)
		jmp[v][i] = jmp[jmp[v][i - 1]][i - 1];
	for (auto w :g[v]) {
		if (w != p)
			dfs(w, v);
	}
}
 
 
int lca(int a, int b) {
	if (h[a] < h[b]) {
		swap(a, b);
	}
	int d = h[a] - h[b];
	for (int k = l; k >= 0; k--) {
		if (d >= (1 << k)) {
			a = jmp[a][k];
			//cout << " a " << a << endl;
			d -= (1 << k);
		}
	}
	//cout << a << " " << b;
	if (a == b) {
		//cout << "YES";
		return a;
	}
	int a_, b_;
	for (int k = l; k >= 0; k--) {
		a_ = jmp[a][k];
		b_ = jmp[b][k];
		if (a_!= b_) {
			a = a_;
			b = b_;
		}
	}
	return jmp[a][0];
}
 
//Подвесить b за a
void add(int a, int b) {
	h[b] = h[a] + 1;
	jmp[b][0] = a;
	for (int i = 1; i <= l; ++i) {
		jmp[b][i] = jmp[jmp[b][i - 1]][i - 1];
		//cout << i << " " << jmp[b][i] << endl;
	}
}
 
int main() {
	ifstream in("lca.in");
	ofstream out("lca.out");
	int n, u, v, m, k;
	in >> k;
	n = k + 1;
	l = 1;
    //Считаем максимальную степень для двоичного подъема
	while ((1 << l) <= n) {
		++l;
	}
 
	for (int i = 0; i < n; ++i) {
		jmp[i].resize(l + 1);
	}
	for (int i = 0; i < l + 1; ++i) {
		jmp[0][i] = 1;
	}
	jmp[1][0] = 1;
	for (int i = 1; i <= l; ++i) {
		jmp[1][i] = 1;
	}
	string s;
	int a, b;
	for (int t=0;t<k;++t) {
		in >> s>>a>>b;
		if (s == "ADD") {
			add(a, b);
		}
		else {
			out<<lca(a, b)<<endl;
		}
	}
}