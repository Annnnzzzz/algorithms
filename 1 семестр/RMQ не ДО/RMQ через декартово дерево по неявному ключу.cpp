#include <iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;
 
struct Item{
    int count, x, Min, priority;
    Item* left_tree, * right_tree;
    Item(): count(0), left_tree(nullptr), right_tree(nullptr), priority(0), x(0),Min((1<<31)-1) { }
    Item(int x) : priority((rand() << 16) + rand()),
        x(x), Min(x), left_tree(nullptr), right_tree(nullptr), count(1) { }
};
 
int cnt(Item* t)
{
    return t ? t->count : 0;
}
 
int GetMin(Item* t)
{
    return t ? t->Min : (1<<31)-1;
}
void upd(Item* t)
{
    if (t)
    {
        t->count = 1 +cnt(t->left_tree) + cnt(t->right_tree);
        t->Min = min(t->x, min(GetMin(t->left_tree), GetMin(t->right_tree)));
    }
}
 
void Merge(Item* l, Item* r, Item*& t)
{
    if (!l || !r) {
        t = l ? l : r;
    }
    else if (l->priority > r->priority) {
        Merge(l->right_tree, r, l->right_tree), t = l;
    }
    else {
        Merge(l, r->left_tree, r->left_tree), t = r;
    }
    upd(t);
}
 
void Split(Item* t, Item*& l, Item*& r, int pos)
{
    if (!t) { return void(l = r = 0); }
    if (pos <= cnt(t->left_tree)) {
        Split(t->left_tree, l, t->left_tree, pos), r=t;
    }
    else {
        Split(t->right_tree, t->right_tree, r, pos - 1 - cnt(t->left_tree)), l=t;
    }
    upd(t);
}
 
int main() {
    int n, i, j;
    char c;
    ifstream in("rmq.in");
    ofstream out("rmq.out");
    in >> n;
    Item* t = nullptr, * t1 = nullptr, * t2 = nullptr;
    for (int p = 0; p < n; p++)
    {
        in >> c >> i >> j;
        if (c == '+')
        {
            Split(t, t1, t2, i);
            Merge(t1, new Item(j), t1);
            Merge(t1, t2, t);
        }
        else
        {
            Split(t, t, t1, i - 1);
            Split(t1, t1, t2, j - i + 1);
            out << (t1->Min)<<endl;
            Merge(t, t1, t);
            Merge(t, t2, t);
        }
    }
}