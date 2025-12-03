#include <iostream>
#include <vector>
#include <map>
using namespace std;
 
int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<long long> a(n);
    vector<vector<long long>> c(n, vector<long long>(n));
    vector<vector<long long>> dp(n, vector<long long>((1 << n),0));
    map<int, int> ed;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int x, y, cost;
    for (int i = 0; i < k; ++i) {
        cin >> x >> y >> cost;
        c[x - 1][y - 1] = cost;
    }
    for (int u = 0; u < n; ++u) {
        dp[u][1 << u] = a[u];
    }
    int new_mask, p;
    for (int mask = 0; mask < (1 << n); ++mask) {
        p = 0;
        for (int v = 0; v < n; ++v) {
            if (!((mask >> v) & 1)) {
                continue;
            }
            for (int u = 0; u < n; ++u) {
                if (!((mask >> u) & 1)) {
                    new_mask = mask | (1 << u);
                    dp[u][new_mask] = max(dp[u][new_mask],
                        dp[v][mask] + a[u] + c[v][u]);
                }
            }
            p += 1;
        }
        ed[mask] = p;
    }
    long long ma = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (ed[mask] == m) {
            for (int v = 0; v < n; ++v) {
                ma = max(ma, dp[v][mask]);
            }
        }
    }
    cout << ma;
}