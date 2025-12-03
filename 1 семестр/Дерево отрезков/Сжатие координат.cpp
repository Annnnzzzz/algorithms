#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

vector<int> pool;
int pool_ptr = 0;
struct segtree {
    int lb, rb;
    int sum = 0, len=0;
    segtree* l = nullptr;
    segtree* r = nullptr;

    segtree(int _lb, int _rb) : lb(_lb), rb(_rb) {}

    ~segtree() {
        delete l;
        delete r;
    }

    void extend() {
        if (!l && lb + 1 < rb) {
            int t = (lb + rb) / 2;
            l = new segtree(lb, t);
            r = new segtree(t, rb);
        }
    }

    void add(int k, int x) {
        extend();
        sum += x;
        if (l) {
            if (k < l->rb)
                l->add(k, x);
            else
                r->add(k, x);
        }
    }

    void update(int k, int newValue) {
        extend();
        if (lb + 1 == rb) {
            sum = newValue; 
        } else {
            if (k < l->rb)
                l->update(k, newValue);
            else
                r->update(k, newValue);
            sum = (l ? l->sum : 0) + (r ? r->sum : 0); 
        }
    }

    int get_sum(int lq, int rq) {
        if (lb >= lq && rb <= rq)
            return sum;
        if (std::max(lb, lq) >= std::min(rb, rq))
            return 0;

        extend();
        return (l ? l->get_sum(lq, rq) : 0) + (r ? r->get_sum(lq, rq) : 0);
    }
};


segtree* create_node(int lb, int rb, const vector<long long>& v) {
    segtree* node = new segtree(lb, rb);
    node->lb = lb;
    node->rb= rb;
    node->lb = v[lb];
    node->rb = v[rb];
    node->len = v[rb] - v[lb] + 1;
                 
    if (lb != rb) {
        int t = (rb + lb) / 2;
        node->l = create_node(lb, t, v);
        node->r = create_node(t + 1, rb, v);
    }
    return node;
}
         
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);   
    int n, q;
    int k = 0, c = 1;
    cin>>n; 
    vector<vector<long long>> a(n, vector<long long>(3));
    set<long long> uniq;
    uniq.insert(1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        cout << a[i][0] << endl;
        uniq.insert(a[i][1]);
        uniq.insert(a[i][2]);
        uniq.insert(a[i][2] + 1);
    }
    vector<long long> s(make_move_iterator(uniq.begin()),
        make_move_iterator(uniq.end()));
    for (int i = 0; i < 20; ++i) {
        if (c >= s.size()) {
            break;
        }
        else {
            k++;
            c *= 2;
        }
    }
    while (s.size() < c) {
        s.push_back(s[s.size() - 1] + 1);
    }
    segtree* tree = create_node(0, s.size() - 1, s);
    for (int i = 0; i < n; i++) {
        if (a[i][0] == 1) {
            tree->add(a[i][1], a[i][2]);
        }
    }
}