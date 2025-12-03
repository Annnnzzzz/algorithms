#include <bits/stdc++.h>
using namespace std;

void DFS(vector<vector<int>>& M, vector<bool>& used, int v, vector<int>& tin, vector<int>& tout) {
    tin.push_back(v);
	used[v] = true;
	for (auto u : M[v]) {
		if (!used[u]) {
			DFS(M, used, u, tin, tout);
		}
	}
    tout.push_back(v);
}
 
void DFS2(vector<vector<int>>& M, vector<bool>& used, int v, pair<long long, long long>& mi, vector<long long>& n) {
    if (n[v] < mi.first) {
        mi.first = n[v];
        mi.second = 1;
    }
    else if (n[v] == mi.first) {
        mi.second++;
    }
    used[v] = true;
    for (auto u : M[v]) {
        if (!used[u]) {
            DFS2(M, used, u, mi, n);
        }
    }
}

int main() {
    int n, u, v, m;
    cin >> n;
    vector<long long> cost(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> cost[i];
    }
    cin >> m;
    vector<vector<int>> g(n + 1);
    vector<vector<int>> r(n + 1);
    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        g[v].push_back(u);
        r[u].push_back(v);
    }
    vector<int> tin;
    vector<int> tout;
    vector<bool> used(n + 1, 0);
    for (int i = 0; i <= n; ++i) {
        if (!used[i]) {
            DFS(g, used, i, tin, tout);
        }
    }
    vector<bool> used2(n + 1, 0);
    //каждый запуск dfs2 новая КС
    long long rez_count=1;
    long long rez_sum=0;
    //вектор tout - топологическая сортировка, если a раньше b, 
    //а недостижима из b, 
    //но b может быть как достижима, так и недостижима из a
    for (int i = tout.size()-1; i>=0; --i) {
        if (!used2[tout[i]]) {
            pair<long long, long long> mi = { 1000000000000000000, 1 };
            DFS2(r, used2, tout[i], mi, cost);
 
           
            mi.second = mi.second % 1000000007;
            rez_count = (rez_count*mi.second)%1000000007;
            rez_sum += mi.first;
        }
    }
    cout << rez_sum << " " << rez_count % 1000000007;
}
