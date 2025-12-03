#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include<fstream>
using namespace std;
 
struct segtree {
    int lb, rb;
    int val = 0;
    int p = -1;
    segtree* left = 0, * right = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb < rb) {
            int t = (lb + rb) / 2;
            left = new segtree(lb, t);
            right = new segtree(t + 1, rb);
        }
    }
 
    void push() {
        if (p != -1) {
            left->p = p;
            right->p = p;
            left->val = p * (left->rb - left->lb + 1);
            right->val = p * (right->rb - right->lb + 1);
            p = -1;
        }
    }
 
    void update(int l, int r, int x) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && r >= rb) {
            p = x;
            val = x * (rb - lb + 1);
            if (l == r) { p = -1; }
            //cout << lb << " " << rb << " " << val<<endl;
        }
        else {
            push();
            left->update(l, r, x);
            right->update(l, r, x);
            val = left->val + right->val;
        }
    }
    
    int get(int l, int r) {
        if (r<lb || l>rb) {
            return 0;
        }
        if (l <= lb && r >= rb) {
            return val;
        }
        
        else {
            push();
            return left->get(l, r) + right->get(l, r);
        }
    }
};
 
 
struct HLD {
    int N, timer = 0;
    vector<vector<int>> g;
    vector<int> par;//массив родителей вершин
    vector<int> sz; // размер поддеревьев
    vector <int> depth; //глубина
    vector <int> top; // вершина тяжелого пути
    vector <int> pos; //позиция вершины в ДО

    segtree* tree;
 
 

    HLD(vector<vector<int>> g_)
        : N(g_.size()), g(g_), par(N, -1), sz(N, 1), depth(N), top(N, 1), pos(N),
        tree(new segtree(0, N)) {
        //все значения top изначально 1, поэтому не возникает проблем 
        //при поиске top[1]
        dfsSz(1);
        dfsHld(1);
    }
 
    void dfsSz(int v) {
        //Удаляем обратные ребра к родителям, считаем размер поддеревьев
        //и находим тяжелые пути
        if (par[v] != -1)
            g[v].erase(find(g[v].begin(), g[v].end(), par[v]));
 
        for (int& u : g[v]) {
            par[u] = v, depth[u] = depth[v] + 1;
            dfsSz(u);
            sz[v] += sz[u];
            if (sz[u] > sz[g[v][0]])
                swap(u, g[v][0]);
        }
    }
 
    void dfsHld(int v) {
        //Второй обход для определения позиций вершин в ДО
        //и определения начала тяжелых путей
        //По предыдущему обходу, если путь тяжелый, он первый
        //то есть если вершина продолжает тяжелый путь, то u == g[v][0]
        //иначе u -- первая вершина нового тяжелого пути
        pos[v] = timer++;
        for (int u : g[v]) {
                top[u] = (u == g[v][0] ? top[v] : u);
                dfsHld(u);
        }
    }
 
    // B операция для выполнения на отрезке, задается в виде лямбды
    //Поднимается от нижней вершины к верхней разбивая путь на сегменты
    template <class B>
    void process(int a, int b, B op) {
        for (; top[a] != top[b]; b = par[top[b]]) {
            // Вершина а выше вершины b
            if (depth[top[a]] > depth[top[b]])
                swap(a, b);
            //применяем операцию к сегменту
            op(pos[top[b]], pos[b]);
        }
        // последняя операция из lca a и b к a или b
        if (depth[a] > depth[b])
            swap(a, b);
        op(pos[a], pos[b]);
    }
 
    // Just examples, modify depending on your problem
    void modifyPath(int u, int v, int val) {
        process(u, v, [&](int l, int r) { tree->update(l, r, val); });
    }
 
    int sumPath(int u, int v) {
        int res=0;
        process(u, v, [&](int l, int r) { res += tree->get(l, r); });
        return res;
    }
};
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, q, u, v, a, b, c, d;
    cin >> n >> q;
    vector<vector<int>> g(n+1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    HLD h(g);
    for (int i = 0; i < q; ++i) {
        cin >> a >> b >> c >> d;
        h.modifyPath(a, b, 1);
        cout << h.sumPath(c, d) << endl;
        h.modifyPath(a, b, 0);
    }
}
