#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
#include<algorithm>
using namespace std;
 
int k=31, p=1000000007;
 
vector <long long> power(int b) {
	vector <long long> power_of_b(b);
	power_of_b[0] = 1;
	for (size_t i = 1; i < b; i++) {
		power_of_b[i] = (power_of_b[i - 1] * k) % p;
	}
	return power_of_b;
}
 
struct treap {
	int key, prior, size = 1;
	int val;
	long long prefix_hash = 0, postfix_hash = 0;
	treap* left = nullptr, * right = nullptr;
	treap(int k, char c) {
		key = k;
		val = c-'a'+1;
		prior = rand();
		prefix_hash = c - 'a' + 1;
		postfix_hash = c - 'a' + 1;
	}
};
 
int size(treap* v) { return v ? v->size : 0; }
long long pref(treap* v) { return v ? v->prefix_hash : 0; }
long long post(treap* v) { return v ? v->postfix_hash : 0; }
 
void upd(treap* v, vector<long long>& pow) {
	v->size = size(v->left) + size(v->right) + 1; 
	v->prefix_hash = ((pref(v->left) + v->val*pow[size(v->left)])%p+pow[size(v->left)+1]*pref(v->right))%p;
	v->postfix_hash =( (post(v->right) + v->val*pow[size(v->right)])%p+pow[size(v->right)+1]*post(v->left))%p;
}
 
treap* merge(treap* l, treap* r, vector<long long>& pow) {
	if (!l) {
		return r;
	}
	if (!r) {
		return l;
	}
	if (l->prior > r->prior) {
		l->right = merge(l->right, r, pow);
		upd(l, pow);
		return l;
	}
	else {
		r->left = merge(l, r->left, pow);
		upd(r, pow);
		return r;
	}
}
 
typedef pair<treap*, treap*> NodePair;
 
NodePair split(treap* t, int key, vector<long long>& pow) {
	if (!t) {
		return NodePair(nullptr, nullptr);
	}
	if (size(t->left) + 1 <= key) {
		NodePair p = split(t->right, key - size(t->left) - 1, pow);
		t->right = p.first;
		upd(t, pow);
		return NodePair(t, p.second);
	}
	else {
		NodePair p = split(t->left, key, pow);
		t->left = p.second;
		upd(t, pow);
		return NodePair(p.first, t);
	}
}
 
void insert(treap*& t, int key, vector<long long>& pow, char c) {
	NodePair p = split(t, size(t), pow);
	t = merge(merge(p.first, new treap(key, c), pow), p.second, pow);
}
 
void inorder(treap*& x) {
	if (x != NULL) {
		inorder(x->left);
		cout << x->val << " ";
		inorder(x->right);
	}
}
int main() {
	int n, q;
	char c;
	vector<long long> pow = power(300001);
	cin >> n>>q;
	vector<char> v(n+1);
	for (int i = 1; i <= n; i++) {
		cin >> v[i];
	}
	treap* t = new treap(1, v[1]);
	for (int i = 2; i <= n; ++i) {
		insert(t, i, pow, v[i]);
	}
	//inorder(t);
	for (int i = 0; i < n; ++i) {
		int l, r, x, pos;
		char cc;
		cin >>x;
		//cout << "x" << x << endl;
		if (x==1) {
			//cout<<"enter l and r"<<endl;
			cin >> l >> r;
			NodePair p1_24 = split(t, l - 1, pow);
			NodePair p2_34 = split(p1_24.second, r - l+1, pow);
			t = merge(p1_24.first, p2_34.second, pow);
		}
		else if (x==2) {
			cin >> cc >> pos;
			NodePair p1_24 = split(t, pos - 1, pow);
			t = merge(merge(p1_24.first, new treap(pos, cc), pow), p1_24.second, pow);
		}
		else {
			//cout << "check" << endl;
			cin >> l >> r;
			NodePair p1_24 = split(t, l - 1, pow);
			NodePair p2_34 = split(p1_24.second, r - l+1, pow);
			//inorder(t);
			if (p2_34.first->postfix_hash == p2_34.first->prefix_hash) {
				cout << "yes" << endl;
			}
			else{
				cout << "no" << endl;
			}
			t=merge(p1_24.first, merge(p2_34.first, p2_34.second, pow), pow);
			//inorder(t);
			//cout << endl;
		}
			
	}
	return 0;
}