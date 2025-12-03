#include <iostream>
#include<vector>
#include<queue>
#include<fstream>
#include<string>
#include<algorithm>
using namespace std;

//Дан ориентированный взвешенный граф без кратных рёбер. 
//Необходимо определить, есть ли в нём циклы, и если есть,
//то вывести любой из них.

int k = 0, f = 0, f1 = 0, f2 = 0;
//v красим в 1 если вошли, но не вышли и в 2 если вышли 
void DFS(vector<vector<int>>& M, vector<int>& used, int v, vector<int>& depth, vector<int>& ans) {
	used[v]++;
	//cout << "v " << v << endl;
	for (auto u : M[v]) {
		if (used[u]==0) {
			depth[u] = depth[v] + 1;
			DFS(M, used, u, depth, ans);
			if (f != 0 || f1 == 1) {
				f2 = 1;
				break;
			}
		}
		//считаем длину цикла
		else if (used[u]==1){
			f = depth[v] - depth[u] + 1;
			break;
		}
		//если уже нашли цикл прекращаем обход
		if (f2 == 1) {
			break;
		}
	}
	used[v]++;
	//если нашли вершину и оказались в цикле, эта вершина его часть
	if (f != 0) {
		ans.push_back(v);
		f--;
		if (f == 0) {
			f1 = 1;
		}
	}
}

int main() {
	ifstream in("cycle2.in");
	ofstream out("cycle2.out");
	int n, v, u, m;
	long long d;
	in >> n >> m;
	vector<vector<int>> g(n + 1);
	for (int i = 0; i < m; i++) {
		in >> v >> u;
		g[v].push_back(u);
	}

	vector<int> used(n + 1);
	vector<int> depth(n + 1);
	vector<int> ans;
	for (int i = 1; i <= n; ++i) {
		if (!used[i]) {
			//cout << i;
			DFS(g, used, i, depth, ans);
		}
		if (ans.size() != 0) {
			break;
		}
	}
	if (ans.size() == 0) {
		out << "NO";
	}
	else {
		out << "YES" << endl;
	}
	for (int i = ans.size()-1; i >=0; --i) {
		out << ans[i] << " ";
	}
}