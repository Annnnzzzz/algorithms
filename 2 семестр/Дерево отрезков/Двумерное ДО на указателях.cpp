#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> a;
int m;

struct segtree_x;

struct segtree_y {
    segtree_x* parent;
    long long xlb, xrb, ylb, yrb;
    long long val = 0;
    segtree_y* left = 0, * right = 0;

    segtree_y(int xlb_, int xrb_, int ylb_, int yrb_, segtree_x* p) :
        xlb(xlb_), xrb(xrb_), ylb(ylb_), yrb(yrb_), parent(p) {
        if (ylb_ == yrb_) {
            if (xlb_ == xrb_) {
                val = a[xlb_][ylb_];
            }
            else {
                val = parent->left->child->get(ylb, ylb) + parent->right->child->get(ylb, ylb);
            }
        }
        if (ylb != yrb) {
            int t = (yrb + ylb) / 2;
            left = new segtree_y(xlb, xrb, ylb, t, p);
            right = new segtree_y(xlb, xrb, t + 1, yrb, p);
            val = left->val + right->val;
        }
    }


    void update(int x, int i) {
        if (ylb == yrb && ylb==x) {
            if (xlb == xrb)
                val = i;
            else
                val = parent->left->child->get(ylb, ylb) + parent->right->child->get(ylb, ylb);
        }
        else {
            if (left->yrb<x)
                right->update(x, i);
            else
                left->update(x, i);
            val = left->val + right->val;
        }
    }

    long long get(int lb, int rb) {
        if (rb<ylb || lb>yrb) {
            return 0;
        }
        if (lb <= ylb && yrb <= rb) {
            return val;
        }
        else {
            return left->get(lb, rb)+right->get(lb, rb);
        }

    }
};

struct segtree_x {
    long long lb, rb;
    segtree_x* left = 0, * right = 0;
    segtree_y* child = 0;

    segtree_x(long long l, long long r) : lb(l), rb(r) {
        if (lb != rb) {
            int m = (lb + rb) / 2;
            left = new segtree_x(lb, m);
            right = new segtree_x(m + 1, rb);
        }
        child = new segtree_y(lb, rb, 1, m, this);
    }

    void update(int x, int y, int i) {
        if (x<lb || x>rb) {
            return;
        }
        if (x == lb && x == rb) {
            child->update(y, i);
        }
        else {
            left->update(x, y, i);
            right->update(x, y, i);
        }
    }

    long long get(int xlb_, int xrb_, int ylb_, int yrb_) {

        if (xrb_<lb || xlb_>rb) {
            return 0;
        }
        if (xlb_ <= lb && xrb_ >= rb) {
            return child->get(ylb_, yrb_);
        }
        else {
            return left->get(xlb_, xrb_, ylb_, yrb_) +
                right->get(xlb_, xrb_, ylb_, yrb_);
        }

    }
};