#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N], r[N];
priority_queue<int> q;
int ans[N], in[N], k, n, m;
void topSort() {
    int u, v;
    for (int i = 0; i < m; i++) {
        cin >> v >> u;
        g[v].push_back(u);
        r[u].push_back(v);
        in[v]++;
    }
    for (int i = 1; i <= n; ++i) {
        if (in[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int p = q.top();
        q.pop();
        ans[p] = k;
        k--;
        for (auto w : r[p]) {
            in[w]--;
            if (in[w] == 0) {
                q.push(w);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        cout << ans[i]<<" ";
    }
}