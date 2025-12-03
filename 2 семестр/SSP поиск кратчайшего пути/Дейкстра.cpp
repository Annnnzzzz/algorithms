#include <vector>
#include <set>
using namespace std;

int n, root;
long long inf = 1e18;
vector< vector< pair<int, int> > > g;
vector<int> dijkstra(int s) {
    vector<int> d(n, inf);
    d[root] = 0;
    set< pair<int, int> > q;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [u, w] : g[v]) {
            if (d[u] > d[v] + w) {
                q.erase({d[u], u});
                d[u] = d[v] + w;
                q.insert({d[u], u});
            }
        }
    }
    return d;
}