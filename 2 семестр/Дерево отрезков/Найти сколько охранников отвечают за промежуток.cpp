#include <iostream>
#include <vector>
#include <stdio.h>
#include <array>
#include <unordered_map>
#include <set>
using namespace std;

long long mod = 1e9 + 7;


struct segtree {
    int lb, rb;
    int val = 0, index, lb_index, rb_index;
    segtree* left = 0, * right = 0;
    int x;

    void push() {
        left->val += x;
		right->val += x;
        left->x += x;
		right->x += x;
		x = 0;
    }

    void update_plus(int l, int r) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && r >= rb) {
            val++;
			x++;
            //cout<<"val "<<val << endl;
        }
        else {
            push();
            val++;
            left->update_plus(l, r);
            right->update_plus(l, r);
            //val = left->val + right->val;
        }
    }

    void update_minus(int l, int r) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && r >= rb) {
            val--;
            x--;
        }
        else {
            push();
            val--;
            left->update_plus(l, r);
            right->update_plus(l, r);
            //val = left->val + right->val;
        }
    }
    long long get(int l, int r) {
        if (r<lb || l>rb) {
            return 0;
        }
        if (l <= lb && r >= rb) {
            return val;
        }
        else {
            push();
            return (left->get(l, r) + right->get(l, r));
        }
    }

    void see() {
        cout<<"see "<<lb << " " << rb << " " << val << endl;
        if (left!=0){
			left->see();
			right->see();
		}
	}

};

vector<segtree> pool(800001);
int pool_ptr = 0;

segtree* create_node(int lb, int rb, const vector<int>& v) {
    segtree* node = &pool[pool_ptr++];
    node->lb_index = lb;
    node->rb_index = rb;
    node->lb = v[lb];
    node->rb = v[rb];
    if (lb != rb){
        int t = (rb + lb) / 2;
        cout<<lb<<" "<<rb<<" "<<t<<endl;
        node->left = create_node(lb, t, v);
        node->right = create_node(t+1, rb, v);
        
    }
    return node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q, lg, rg;
    cin >> n >> q;
    unordered_map< int, pair<int, int>> mp;
    set<int> uniq;
    pair <int, int> p;
    for (int i = 0; i < n; ++i) {
        cin >> lg>>rg;
		p.first = lg;
		p.second = rg;
        mp[i]=p;
        uniq.insert(lg);
		uniq.insert(rg);
    }
    int l, r, x;
    char ch;
    vector<vector<int>> requests(q, vector<int>(4));
    for (int i = 0; i < q; ++i) {
        cin >> ch;
        if (ch == '?') {
            requests[i][0] = 2;
            cin >> requests[i][1] >> requests[i][2];
		}
        else {
			requests[i][0] = 1;
			cin >> requests[i][3] >> requests[i][1]>>requests[i][2];
        }
        uniq.insert(requests[i][1]);
        uniq.insert(requests[i][2]);
    } 
    std::vector<int> a(make_move_iterator(uniq.begin()), 
        make_move_iterator(uniq.end()));

    segtree* tree = create_node(0, a.size() - 1, a);
    for (const auto& el : mp) {
        //cout << "num " << endl;
		tree->update_plus(el.second.first, el.second.second);
        //tree->see();
    }
    tree->see();
    for (const auto& el : requests) {
		if (el[0] == 1) {
            pair<int, int> MakeP = mp[el[3]];
			tree->update_minus(MakeP.first, MakeP.second);
			tree->update_plus(el[1], el[2]);
			mp[el[3]] = { el[1], el[2] };
		}
		else {
			cout << tree->get(el[1], el[2]) << endl;
		}
	}
	return 0;
}