#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
#include<algorithm>
#include<fstream>
using namespace std;
 
struct treap {
    int key, prior, size=1, val=0;
	treap *left=nullptr, *right=nullptr;
	treap(int k) {key=k, val=k; prior=rand();}
};
 
int size(treap *v) {return v ? v->size:0;}
 
void upd(treap *v) {v->size = size(v->left) + size(v->right) + 1;}
 
treap *merge(treap *l, treap *r) {
	if (!l) {
		return r;
	}
	if (!r){
		return l;
	}
	if (l->prior > r->prior) {
		l->right = merge(l->right, r);
		upd(l);
		return l;
	}
	else {
		r->left = merge(l, r->left);
		upd(r);
		return r;
	}
}
 
typedef pair<treap *, treap *> NodePair;
 
NodePair split(treap *t, int key) {
	if (!t) {
		return NodePair(nullptr, nullptr);
	}
	if (size(t->left) +1 <= key) {
		NodePair p = split(t->right, key-size(t->left)-1);
		t->right = p.first;
		upd(t);
		return NodePair(t, p.second);
	}
	else {
		NodePair p = split(t->left, key);
		t->left = p.second;
		upd(t);
		return NodePair(p.first, t);
	}
}
 
void insert(treap *&t, int key) {
	NodePair p = split(t, size(t));
	t = merge(merge(p.first, new treap(key)), p.second);
}
 
void inorder(treap *& x, vector<int>& v){
	if (x != NULL) {
		inorder(x->left, v);
		v.push_back(x->val);
		inorder(x->right, v);
	}
}
int main() {
	int n, m;
	ifstream in("movetofront.in");
	ofstream out("movetofront.out");
	in >> n >> m;
	treap *t=new treap(1);
	for (int i = 2; i <= n; ++i) {
		insert(t, i);
	}
	for (int i = 0; i < m; ++i) {
		int l, r;
		in >> l >> r;
		NodePair p1 = split(t, l-1);
		NodePair p2 = split(p1.second, r-l+1);
		t = merge(merge(p2.first, p1.first), p2.second);
	}
	vector<int> v;
	inorder(t, v);
	for (int i=0; i<v.size(); ++i) {
		out << v[i] << " ";
	}
	return 0;
}
