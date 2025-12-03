#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;

template <typename T>
struct PQ {
  long long sum = 0;
  priority_queue<T, vector<T>, greater<T>> Q;
  void push(T x) {
    x.cost -= sum;
    Q.push(x);
  }
  T pop() {
    auto ans = Q.top();
    Q.pop();
    ans.cost += sum;
    return ans;
  }
  int size() { return Q.size(); }
  void add(long long x) { sum += x; }
  void merge(PQ&& x) {
    if (size() < x.size())
      swap(sum, x.sum), swap(Q, x.Q);
    while (x.size()) {
      auto tmp = x.pop();
      tmp.cost -= sum;
      Q.push(tmp);
    }
  }
};
struct edge {
  int from, to;
  long long cost;
  bool operator>(const edge& rhs) const { return cost > rhs.cost; }
};
struct DSU {
  vector<int> par;
  DSU(int n) : par(n, -1) {}
  int root(int i) { return par[i] < 0 ? i : par[i] = root(par[i]); }
  void set_par(int c, int p) { par[c] = p; }
};
vector<int> DMST(int n, int root, const vector<edge>& edges) {
  vector<int> prev(2 * n - 1, -1);
  vector<int> super_par(2 * n - 1, -1);
  vector<edge> par_edge(2 * n - 1);
  vector<vector<int>> children(2 * n - 1);

  vector<PQ<edge>> pq(2 * n - 1);
  for (auto e : edges)
    pq[e.to].push(e);
  for (int i = 0; i < n; i++)
    pq[(i + 1) % n].push({i, (i + 1) % n, INF});

  int super = n;
  DSU dsu(2 * n - 1);
  int cur = 0;
  while (pq[cur].size()) {
    auto edge = pq[cur].pop();
    int from = dsu.root(edge.from);
    if (from == cur)
      continue;
    prev[cur] = from;
    par_edge[cur] = edge;
    if (prev[from] == -1) {
      cur = from;
      continue;
    }
    int cycle_v = from;
    do {
      pq[cycle_v].add(-par_edge[cycle_v].cost);
      pq[super].merge(std::move(pq[cycle_v]));
      assert(prev[cycle_v] != -1);
      children[super].push_back(cycle_v);
      cycle_v = dsu.root(prev[cycle_v]);
    } while (cycle_v != from);
    for (auto u : children[super]) {
      super_par[u] = super;
      dsu.set_par(u, super);
    }
    cur = super++;
  }
  vector<int> ans(2 * n - 1, -1);
  queue<int> q;
  q.push(root);
  while (q.size()) {
    int cur = q.front();
    q.pop();
    for (; super_par[cur] != -1; cur = super_par[cur]) {
      for (auto ch : children[super_par[cur]]) {
        if (ch != cur) {
          ans[par_edge[ch].to] = par_edge[ch].from;
          q.push(par_edge[ch].to);
          super_par[ch] = -1;
        }
      }
    }
  }
  ans[root] = root;
  ans.resize(n);
  return ans;
}
