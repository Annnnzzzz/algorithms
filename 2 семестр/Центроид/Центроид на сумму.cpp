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
void build_centroid_decomposition(int u, int p) {
    sizes(u, -1);
    int centr = centroid(u, -1, s[u]);
 
    //parent[centroid] = p;
    used[centr] = true;
 
    for (int v : g[centr]) {
        if (!used[v]) {
            build_centroid_decomposition(v, centr);
        }
    }
}
 
// записывает в t[] глубины вершин
void dfs(int v, int p, int d, vector<int>& t) {
    t.push_back(d);
    for (int u : g[v])
        if (u != p && !used[u])
            dfs(u, v, d + 1, t);
}
 
void solve(int v) {
    /* <единственный зависящий от конкретной задачи код> */
    //cout <<"v "<< v<<endl;
    sizes(v, -1);
    vector<int> d(s[v], 0);
    d[0] = 1;
    for (int u : g[v]) {
        //cout << "u " << u << endl;
        if (!used[u]) {
            
            vector<int> t;
            dfs(u, v, 1, t);
            //cout << "yes";
            for (int x : t)
                if (x <= l) {
                   // cout << "+ ans " <<x<< endl;
                    if (d.size() > l - x) {
                        ans += d[l - x];
                    }
                    //cout << "good ans" << endl;
                }
                    
            for (int x : t) {
                //cout << "try" << endl;
                d[x]++;
                //cout << "+" << endl;
            }
                
        }
    }
    /* </единственный зависящий от конкретной задачи код> */
    
    used[v] = 1;
    
    for (int u : g[v]) {
        //cout << "used?" << endl;
        if (!used[u]) {
            //cout << "not" << endl;
            //cout << s[u];
            solve(centroid(u, v, s[u]));
           // cout << "(" << endl;
        }
    }
}
 
int main() {
        int n; // количество вершин в дереве
        cin >> n>>l;
        n++;
        g.resize(n);
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
 
        solve(1);
        cout << ans;
    
        return 0;
}