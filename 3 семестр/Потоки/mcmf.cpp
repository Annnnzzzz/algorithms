#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long ll;

struct Edge {
    int to;
    ll capacity;
    ll cost;
    ll flow;
    int rev;
};
ll INF = 10e10;

class MinCostMaxFlowDijkstra {
private:
    int n;
    vector<vector<Edge>> graph;
    vector<ll> dist;
    vector<ll> potential;
    vector<int> parent;
    vector<int> parent_edge;
    vector<bool> visited;

    void dijkstra(int source) {
        fill(dist.begin(), dist.end(), LLONG_MAX);
        fill(visited.begin(), visited.end(), false);

        dist[source] = 0;
        using pll = pair<ll, int>;
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        pq.push({ 0, source });

        while (!pq.empty()) {
            auto pp  = pq.top();
            auto d = pp.first;
            auto u = pp.second;
            pq.pop();

            if (visited[u]) continue;
            visited[u] = true;

            for (int i = 0; i < graph[u].size(); i++) {
                Edge& e = graph[u][i];
                if (e.capacity > e.flow) {
                    ll new_dist = dist[u] + e.cost + potential[u] - potential[e.to];
                    if (new_dist < dist[e.to]) {
                        dist[e.to] = new_dist;
                        parent[e.to] = u;
                        parent_edge[e.to] = i;
                        pq.push({ dist[e.to], e.to });
                    }
                }
            }
        }
    }

public:
    MinCostMaxFlowDijkstra(int n) : n(n), graph(n), dist(n), potential(n),
        parent(n), parent_edge(n), visited(n) {}

    void add_edge(int from, int to, ll capacity, ll cost, bool f) {
        if (f) {
            Edge e1 = { to, capacity, cost, 0, (int)graph[to].size() };
            Edge e2 = { from, capacity, cost, 0, (int)graph[from].size() };
            graph[from].push_back(e1);
            graph[to].push_back(e2);
        }
        else {
            Edge e1 = { to, capacity, cost, 0, (int)graph[to].size() };
            Edge e2 = { from, 0, -cost, 0, (int)graph[from].size() };
            graph[from].push_back(e1);
            graph[to].push_back(e2);
        }
    }

    pair<ll, ll> min_cost_flow(int source, int sink, ll required_flow = LLONG_MAX) {
        ll total_flow = 0;
        ll total_cost = 0;

        fill(potential.begin(), potential.end(), 0);

        while (total_flow < required_flow) {
            dijkstra(source);

            if (dist[sink] == LLONG_MAX) break;

            // Обновляем потенциалы
            for (int i = 0; i < n; i++) {
                if (dist[i] != LLONG_MAX) {
                    potential[i] += dist[i];
                }
            }

            ll path_flow = required_flow - total_flow;
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                int i = parent_edge[v];
                path_flow = min(path_flow, graph[u][i].capacity - graph[u][i].flow);
            }

            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                int i = parent_edge[v];

                graph[u][i].flow += path_flow;
                graph[v][graph[u][i].rev].flow -= path_flow;

                total_cost += path_flow * graph[u][i].cost;
            }

            total_flow += path_flow;
        }

        return { total_flow, total_cost };
    }
};

// Пример транспортной задачи
int main() {
    int v, e, n, k, a, b, t;
    cin >> v >> e >> n >> k;
    MinCostMaxFlowDijkstra mcmf(v+2+1);
    vector<int> start(v + 1, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a;
        start[a]++;
    }
    for (int i = 1; i <= n; ++i) {
        if (start[i] != 0) {
            mcmf.add_edge(0, i, start[i], 0, false);
        }
        mcmf.add_edge(i, v + 1, 1, 0, false);
    }
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> t;
        mcmf.add_edge(a, b, INF, t, true);
    }
    mcmf.add_edge(v + 1, v + 2, k, 0, false);
    int s = 0;
    int T = v+2;

    auto flow_cost = mcmf.min_cost_flow(s, T);

    if (flow_cost.first == k) {
        cout << flow_cost.second;
    }
    else {
        cout << -1;
    }

    return 0;
}