#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct segtree {
    int lb, rb;
    int val = 0;
    int p = 0;
    segtree* left = 0, * right = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb  < rb) {
            int t = (lb + rb) / 2;
            left = new segtree(lb, t);
            right = new segtree(t+1, rb);
        }
    }
    void push() {
        left->p += p;
        right->p +=p;
        left->val += p * (left->rb - left->lb + 1);
        right->val += p * (right->rb - right->lb + 1);
        p = 0;
    }

    void add(long long i, long long x) {
        if (i<lb || i>rb) {
            return;
        }
        if (i == lb && i == rb) {
            val = x;
        }
        else {
            left->add(i, x);
            right->add(i, x);
            val = left->val, right->val;
        }
    }
    void update(int l, int r, int x) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && r >= rb) {
            p+= x;
            val += x * (rb - lb + 1);
        }
        else {
            push();
            int m = (lb + rb) / 2;
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
            int m = (lb + rb) / 2;
            return left->get(l, r)+right->get(l, r);
        }
    }
};

int main() {
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    segtree tree{ 1, 16 };
    for (int i = 0; i < 10; ++i) {
        tree.update(i + 1, i+1, v[i]);
    }
    tree.update(3, 7, 2);
    cout << tree.get(3, 5);
}