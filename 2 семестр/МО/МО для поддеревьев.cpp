#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> g[N];  // Граф дерева
int val[N];        // Значения в вершинах
int in[N], out[N]; // Время входа/выхода в DFS
int flat[2*N];    
int timer = 0;
int BLOCK;

// DFS для преобразования дерева в массив
void dfs(int u, int p) {
    in[u] = ++timer;
    flat[timer] = val[u];
    for (int v : g[u]) {
        if (v != p) dfs(v, u);
    }
    out[u] = ++timer;
    flat[timer] = val[u]; // Для обработки поддеревьев
}

// Запрос к поддереву вершины u
struct Query {
    int l, r, idx; // l=in[u], r=out[u]
    bool operator < (const Query& q) const {
        return (l/BLOCK == q.l/BLOCK) ? (r < q.r) : (l < q.l);
    }
};

unordered_map<int, int> cnt;
int unique_count = 0;

void add(int pos) {
    if (++cnt[flat[pos]] == 1) unique_count++;
}

void remove(int pos) {
    if (--cnt[flat[pos]] == 0) unique_count--;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, -1); 

    BLOCK = sqrt(n);

    vector<Query> queries(q);
    for (int i = 0; i < q; i++) {
        int u;
        cin >> u;
        queries[i] = {in[u], out[u], i};
    }

    sort(queries.begin(), queries.end());

    vector<int> ans(q);
    int cur_l = 1, cur_r = 0;

    for (auto q : queries) {
        while (cur_l > q.l) add(--cur_l);
        while (cur_r < q.r) add(++cur_r);
        while (cur_l < q.l) remove(cur_l++);
        while (cur_r > q.r) remove(cur_r--);
        
        ans[q.idx] = unique_count;
    }

    for (int x : ans) cout << x << "\n";

    return 0;
}