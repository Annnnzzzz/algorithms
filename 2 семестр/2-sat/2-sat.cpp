#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include<fstream>
using namespace std;
const int N = 210;
int n, m, q;
vector<int> cs(N, 0);
vector<vector<int>> to(N, vector<int>(18, 0));
vector<vector<vector<int>>> f(N, vector<vector<int>>(18, vector<int>(0)));
vector<vector<int>> con(N);
 
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
 
void DFS2(vector<vector<int>>& M, vector<bool>& used, int v, int num) {
    cs[v] = num;
    used[v] = true;
    for (auto u : M[v]) {
        if (!used[u]) {
            DFS2(M, used, u, num);
        }
    }
}
 
int main() {
    int n, m, a, b, c;
    cin >> n>>m;
    vector<vector<int>> g(2*n+2);
    vector<vector<int>> r(2*n+2);
    for (int i = 0; i < m; i++) {
        cin >> a>>b>>c;
        if (c == 1) {
            g[a+n].push_back(b+n);
            r[b+n].push_back(a+n);
 
            g[b].push_back(a);
            r[a].push_back(b);
 
            g[b+n].push_back(a+n);
            r[a+n].push_back(b+n);
 
            g[a].push_back(b);
            r[b].push_back(a);
        }
        else {
            g[a + n].push_back(b);
            r[b].push_back(a + n);
 
            g[b].push_back(a+n);
            r[a+n].push_back(b);
 
            g[b + n].push_back(a);
            r[a].push_back(b + n);
 
            g[a].push_back(b+n);
            r[b+n].push_back(a);
        }
       
    }
    vector<int> tin;
    vector<int> tout;
    vector<bool> used(2*n + 2, 0);
    for (int i = 0; i <= n; ++i) {
        if (!used[i]) {
            DFS(g, used, i, tin, tout);
        }
    }
    vector<bool> used2(2*n + 2, 0);
    //каждый запуск dfs2 новая КС
    int num = 0;
    for (int i = tout.size() - 1; i >= 0; --i) {
        if (!used2[tout[i]]) {
            DFS2(r, used2, tout[i], num);
            num++;
        }
    }
    int res = 0;
    vector<int> ans;
    for (int i = 1; i <= n; ++i) {
        if (cs[i] < cs[i + n]) {
            res++;
            ans.push_back(i);
        }
    }
    if (res == 0) {
        cout << "Impossible";
        return 0;
    }
    cout << res << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << " ";
    }
}