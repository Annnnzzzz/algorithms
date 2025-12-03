#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
using namespace std;
 
//подсчёт путей заданной длины
int l = 179; // нужная нам длина
int ans = 0;
int ss;
 
int maxn = 100000;
vector<bool> used;
vector<int> s;
vector<vector<int>> g;
int LOG;
vector<int> h;
vector<int> parentCentroid;
vector<int> ms;
vector<bool> isWhite;
 
void preprocessLCA(int u, int p, int d, vector<vector<int>>& jmp) {
    h[u] = d;
    if (p == -1) {
        jmp[u][0] = u;
    }
    else {
        jmp[u][0] = p;
    }
    for (int i = 1; i < LOG; ++i) {
        jmp[u][i] = jmp[jmp[u][i - 1]][i - 1];
    }
    for (int v : g[u]) {
        if (v != p) preprocessLCA(v, u, d + 1, jmp);
    }
}
 
int lca(int a, int b, vector<vector<int>>& jmp) {
    if (h[a] < h[b]) {
        swap(a, b);
    }
    int d = h[a] - h[b];
    for (int k = LOG; k >= 0; k--) {
        if (d >= (1 << k)) {
            a = jmp[a][k];
            d -= (1 << k);
        }
    }
    if (a == b) {
        return a;
    }
    int a_, b_;
    for (int k = LOG; k >= 0; k--) {
        a_ = jmp[a][k];
        b_ = jmp[b][k];
        if (a_ != b_) {
            a = a_;
            b = b_;
        }
    }
    return jmp[a][0];
}
 
int dist(int u, int v, vector<vector<int>>& jmp) {
    return h[u] + h[v] - 2 * h[lca(u, v, jmp)];
}
void sizes(int v, int p) {
    s[v] = 1;
    for (int u : g[v]){
        if (u != p && !used[u]) {
            sizes(u, v);
            s[v] += s[u];
        }
    }
}
 
// второй параметр -- размер дерева
int centroid(int v, int p, int n) {
    for (int u : g[v]) {
        if (u != p && !used[u] && s[u] > n / 2) {
            //cout << u << endl;
            return centroid(u, v, n);
        }
    }
            
    return v;
}
 
// Построение центроидной декомпозиции
void build_centroid_decomposition(int u, int p, int d) {
    sizes(u, -1);
    int centr = centroid(u, -1, s[u]);
 
    parentCentroid[centr] = p;
    used[centr] = true;
    for (int v : g[centr]) {
        if (!used[v]) {
            build_centroid_decomposition(v, centr, d+1);
        }
    }
}
 
void color(int v, vector<vector<int>>& jmp) {
    isWhite[v] = !isWhite[v];
    int u = v;
    while (u != -1) {
        int d = dist(u, v, jmp);
        ms[u] = min(ms[u], d);
        u = parentCentroid[u];
    }
}
 
int find(int v, vector<vector<int>>& jmp) {
    int ans = 10000000;
    int u = v;
    while (u != -1) {
                int d = dist(u, v, jmp);
                ans = min(ans, d + ms[u]);
        u = parentCentroid[u];
    }
    return ans;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m; // количество вершин в дереве
    cin >> n>>m;
    n++;
    g.resize(n);
    h.resize(n);
    used.assign(n, false);
    s.resize(n);
    ms.resize(n, 1000000000);
    isWhite.resize(n, 0);
    parentCentroid.resize(n, -1);
    LOG = 0;
    //Считаем максимальную степень для двоичного подъема
    while ((1 << LOG) <= n) {
        ++LOG;
    }
    vector<vector<int>> jmp(n, vector<int>(LOG+1, 0));
    // Чтение дерева
    for (int i = 0; i < n - 2; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    preprocessLCA(1, -1, 0, jmp);
    // Построение центроидной декомпозиции
 
    build_centroid_decomposition(1, -1, 0);
 
    color(1, jmp);
    int t, v;
    // Вывод центроидного дерева (родителей)
    for (int i = 0; i < m; ++i) {
        cin >> t >> v;
        if (t == 1) {
            color(v, jmp);
        }
        else {
            cout << find(v, jmp) << endl;
        }
    }
 
    return 0;
}