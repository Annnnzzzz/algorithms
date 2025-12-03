#include <iostream>
#include <vector>
#include <stdio.h>
#include <set>
#include<algorithm>
#include<fstream>
using namespace std;
 
struct treap {
    int key, prior;
	treap *left=nullptr, *right=nullptr;
	treap(int k) {key=k; prior=rand();}
};
 
//int size(treap *v) {return v ? v->size:0;}
int get_min(treap* v) {
	if (!v) return -1;
	if (!(v->left)) return v->key;
	else return get_min(v->left);
}
 
//void upd(treap *v) {
//	//v->size = size(v->left) + size(v->right) + 1;
//	v->val = min(min(v->val, Min(v->left)), Min(v->right));
//}
 
treap *merge(treap *l, treap *r) {
	if (!l) {
		return r;
	}
	if (!r){
		return l;
	}
	if (l->prior > r->prior) {
		l->right = merge(l->right, r);
		return l;
	}
	else {
		r->left = merge(l, r->left);
		return r;
	}
}
 
typedef pair<treap *, treap *> NodePair;
 
NodePair split(treap *t, int key) {
	if (!t) {
		return NodePair(nullptr, nullptr);
	}
	if (t->key<= key) {
		NodePair p = split(t->right, key);
		t->right = p.first;
		return NodePair(t, p.second);
	}
	else {
		NodePair p = split(t->left, key);
		t->left = p.second;
		return NodePair(p.first, t);
	}
}
 
void insert(treap *&t, int key) {
	NodePair p = split(t, key);
	if (p.first && p.first->key == key) {
		//cout << "key" <<key<< endl;
		t=merge(p.first, p.second);
		return;
	}
	//cout<<p.first->key<<" "<<endl;
	t = merge(merge(p.first, new treap(key)), p.second);
}
 
void inorder(treap *& x){
	if (x != NULL) {
		inorder(x->left);
		cout<<x->key<<" ";
		inorder(x->right);
	}
}
//декарт работает так, что, когда мы режем по ключу, ключ уход влево
int main() {
	int n;
	ifstream in("next.in");
	ofstream out("next.out");
	in >> n;
	char c1='+', c2;
	int x, y=0;
	treap *t=new treap(1);
	//inorder(t);
	for (int i = 0; i < n; ++i) {
		
		in >> c2 >> x;
		if (c2 == '+') {
			
			if (c1 == '+') {
				insert(t, x);
			}
			else {
				
				long long ans =(x + y) % 1000000000;
				//cout<<"ans "<<ans << endl;
				insert(t, ans);
			}
			//inorder(t);
			//cout  << endl;
		}
		else{
			NodePair p1 = split(t, x-1);
			y=get_min(p1.second);
			out << y << endl;
			t = merge(p1.first, p1.second);
			
		}
		c1 = c2;
	}
}