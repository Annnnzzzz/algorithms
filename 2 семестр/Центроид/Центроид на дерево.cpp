#include <iostream>
#include <vector>
using namespace std;
 
//подсчёт путей заданной длины
int l = 179; // нужная нам длина
int ans = 0;
 
int maxn = 100000;
vector<bool> used(maxn);
vector<int> s(maxn); //размеры поддеревьев
vector<vector<int>> g;
vector<int> parent;
vector<int> rang;
 
void sizes(int v, int p) {
    s[v] = 1;
    for (int u : g[v]){
        if (u != p && !used[u]) {
            sizes(u, v);
            s[v] += s[u];
        }
    }
    //cout << v << " " << s[v] << endl;
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
void build_centroid_decomposition(int u, int p, int r) {
    sizes(u, -1);
    int centr = centroid(u, -1, s[u]);
 
    //parent[centroid] = p;
    used[centr] = true;
    rang[centr] = r;
 
    for (int v : g[centr]) {
        if (!used[v]) {
            build_centroid_decomposition(v, centr, r+1);
        }
    }
}
 
 
int main() {
    int n; // количество вершин в дереве
    cin >> n;
    n++;
    g.resize(n);
    rang.resize(n);
    used.resize(n, false);
    s.resize(n);
    parent.resize(n, -1);
        
    // Чтение дерева
    for (int i = 0; i < n-2; ++i) {
        //cout << i;
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    build_centroid_decomposition(1, -1, 0);
    for (int i = 1; i < n; ++i) {
        if (rang[i] >= 26) {
            cout << "Impossible!" << endl;
        }
    }
    for (int i = 1; i < n; ++i) {
        cout << char('A' + rang[i]) << " ";
    }
        return 0;
}