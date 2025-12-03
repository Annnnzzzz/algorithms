#include <iostream>
#include <vector>
#include<string>
#include<sstream>
#include <unordered_map>
#include <algorithm>
using namespace std;
 
struct segtree {
    int lb, rb;
    long long val = 10000000000000;
    long long p = 0;
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
        left->p += p;
        right->p += p;
        left->val += p;
        right->val += p;
        p = 0;
    }
 
    void add(int i, int x) {
        if (i<lb || i>rb) {
            return;
        }
        if (i == lb && i == rb) {
            val = x;
        }
        else {
            left->add(i, x);
            right->add(i, x);
            val = min(left->val, right->val);
        }
    }
 
    void update(int l, int r, long long x) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && r >= rb) {
            p += x;
            val += x;
        }
        else {
            push();
            left->update(l, r, x);
            right->update(l, r, x);
            val = min(left->val,right->val);
        }
    }
    long long get(int l, int r) {
        if (r<lb || l>rb) {
            return 10000000000000;
        }
        if (l <= lb && r >= rb) {
            return val;
        }
        else {
            push();
            return min(left->get(l, r), right->get(l, r));
        }
    }
};
 
int main() {
    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int k;
    for (int i = 0; i < 31; i++) {
        if ((1 << i) >= n) {
            k = i;
            break;
        }
    }
 
    cin >> m;
    cin.ignore();
    segtree tree{ 0, (1<<k)-1 };
    for (int i = 0; i < n; ++i) {
        tree.add(i, a[i]);
    }
    for (int i = 0; i < m; ++i) {
        std::string line;
        getline(std::cin, line);
        std::istringstream iss(line);
        vector<int> v;
        int value;
        while (iss >> value)
            v.push_back(value);
        if (v.size() == 2) {
            if (v[0] <= v[1]) {
                cout << tree.get(v[0], v[1])<<endl;
            }
            else {
                cout << min(tree.get(v[0], n - 1), tree.get(0, v[1]))<<endl;
            }
        }
        else {
            if (v[0] <= v[1]) {
                tree.update(v[0], v[1], v[2]);
            }
            else {
                tree.update(v[0], n - 1, v[2]);
                tree.update(0, v[1], v[2]);
            }
        }
    }
}