#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
#include<algorithm>
using namespace std;
 
 
 
struct segtree {
    long long lb, rb, lb_index, rb_index;
    long long val = 0, len;
    segtree* left = 0, * right = 0;
    int p = -5;
 
    void push() {
        if (p != -5) {
            if (left == 0) {
                return;
            }
            if (p == 0) {
                if (left->left != 0) {
                    left->p = 0;
                    right->p = 0;
                }
                left->val = 0;
                right->val = 0;
                p = -5;
            }
            else if (p == 1) {
                if (left->left != 0) {
                    left->p = 1;
                    right->p = 1;
                }
                left->val = left->len;
                right->val = right->len;
                p = -5;
            }
            else if (p == 3) {
                if (left->p != -5) {
                    left->push();
                }
                if (right->p != -5) {
                    right->push();
                }
                if (left->left != 0) {
                    left->p = 3;
                    right->p = 3;
                }
                left->val = left->len - left->val;
                right->val = right->len - right->val;
                p = -5;
            }
        }
        return;
    }
    void add(long long l, long long r) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && rb <= r) {
            val = len;
            p = 1;
        }
        else {
            push();
            left->add(l, r);
            right->add(l, r);
            if (left->val == left->len) {
                val = right->lb - left->lb + right->val;
            }
            else {
                val = 1;
            }
        }
    }
 
    void remove(long long l, long long r) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && rb <= r) {
            val = 0;
            p = 0;
        }
        else {
            push();
            left->remove(l, r);
            right->remove(l, r);
            if (left->val == left->len) {
                val = right->lb - left->lb + right->val;
            }
            else if ((left->val == 0) && (right->val == 0)) {
                val = 0;
            }
            else {
                val = 1;
            }
        }
    }
 
    void invert(long long  l, long long  r) {
        if (r<lb || l>rb) {
            return;
        }
        push();
        if (l <= lb && rb <= r) {
            val = len - val;
            p = 3;
            return;
        }
 
        else {
            left->invert(l, r);
            right->invert(l, r);
            if (left->val == left->len) {
                val = right->lb - left->lb + right->val;
            }
            else if ((left->val == 0) && (right->val == 0)) {
                val = 0;
            }
            else {
                val = 1;
            }
        }
    }
    long long get() {
        
        if (val == len) {
            return val;
        }
        else if (left == 0) {
            return 0;
        }
        push();
        if (left->val == left->len) {
            return (right->lb - left->lb) + right->get();
        }
        else {
            return left->get();
        }
 
    }
    /*void see() {
        cout << " see " << " " << lb << " " << rb << " " << val << " " << p << endl;
        if (left != 0) {
            left->see();
            right->see();
        }
    }*/
};
 
segtree pool[1100001];
int pool_ptr = 0;
 
segtree* create_node(int lb, int rb, const vector<long long>& v) {
    segtree* node = &pool[pool_ptr++];
    node->lb_index = lb;
    node->rb_index = rb;
    node->lb = v[lb];
    node->rb = v[rb];
    node->len = v[rb] - v[lb] + 1;
    
 
    if (lb != rb) {
        int t = (rb + lb) / 2;
        node->left = create_node(lb, t, v);
        node->right = create_node(t + 1, rb, v);
        //node->real_len=node->right->lb-node->left->lb;
    }
    return node;
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    int n, q;
 
    //cin >> n;
    int k = 0, c = 1;
    scanf("%d", &n); 
    vector<vector<long long>> a(n, vector<long long>(3));
    set<long long> uniq;
    uniq.insert(1);
    for (int i = 0; i < n; ++i) {
        //cin >> a[i][0] >> a[i][1] >> a[i][2];
        scanf("%lld %lld %lld", &a[i][0], &a[i][1], &a[i][2]);
        //cout << a[i][0] << endl;
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
        else if (a[i][0] == 2) {
            tree->remove(a[i][1], a[i][2]);
        }
        else {
            tree->invert(a[i][1], a[i][2]);
        }
        //cout << "change " << endl;
        //tree->see();
        //cout << tree->get() + 1 << endl;
        //tree->see();
        printf("%lld\n", tree->get()+1);
    }
}