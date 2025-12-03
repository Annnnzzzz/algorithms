#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
#include <unordered_map>
#include <stack>
#include <unordered_set>
#include <algorithm>
using namespace std;

unordered_map<long long, int> start;
vector<int> p, s;
vector<pair<char, pair<int, int>>> query;
stack<pair<int, int>> st;

int leader(int v) {
    return (p[v] == v) ? v : leader(p[v]);
}

void cancel() {
    auto [a, b] = st.top();
    p[a] = b;
    st.pop();
}
void unite(int a, int b) {
    st.push({ a, p[a] });
    a = leader(a);
    b = leader(b);
    if (a == b) {
        return;
    }
    if (s[a] > s[b])
        swap(a, b);
    s[b] += s[a];
    p[a] = b;
}

void init(int n) {
    for (int i = 0; i <= n; i++)
        p[i] = i, s[i] = 1;
}

struct segtree {
    int lb, rb;
    vector<pair<int, int>> val;
    segtree* left = 0, * right = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb < rb) {
            int t = (lb + rb) / 2;
            left = new segtree(lb, t);
            right = new segtree(t + 1, rb);
        }
    }

    void update(int l, int r, pair<int, int> p) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && r >= rb) {
            val.push_back(p);
        }
        else {
            left->update(l, r, p);
            right->update(l, r, p);
        }
    }

    int get(int l, int r) {
        if (r<lb || l>rb) {
            return 0;
        }
        if (l <= lb && r >= rb) {
            return 0;
        }
        else {
            return left->get(l, r) + right->get(l, r);
        }
    }
    void see() {
        for (auto [u, v] : val) {
            unite(u, v);
        }
        if (lb == rb){
            if (query[lb].first == '?') {
                if (leader(query[lb].second.first) ==
                    leader(query[lb].second.second)) {
                    cout << "Y" << endl;
                }
                else {
                    cout << "N" << endl;
                }
            }
        }
        else {
            left-> see();
            right->see();
        }
        //cout << val.size() << endl;
        for (int i = 0; i < val.size(); ++i) {
            cancel();
        }
    }
};


int main() {
    int n, m, v, u;
    cin >> n >> m;
    segtree tree{ 1, m };
    p.resize(n + 1);
    s.resize(n + 1);
    query.resize(m + 1);
    init(n);
    for (int i = 1; i <= m; ++i) {
        cin >> query[i].first >> u >> v;
        query[i].second.first = u;
        query[i].second.second = v;
        if (u > v) {
            swap(u, v);
        }
        if (query[i].first == '+') {
            start[v * 10000 + u] = i;
           // cout << "start " << i;
        }
        else if (query[i].first == '-') {
            //cout << "start " << start[v * 10000 + u] << "end " << i << endl;
            tree.update(start[v * 10000 + u], i, {u, v});
        }
    }
    tree.see();
    return 0;
}