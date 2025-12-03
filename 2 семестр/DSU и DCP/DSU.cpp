#include <bits/stdc++.h>
using namespace std;
int leader(int v, vector<int>& p) {
    return (p[v] == v) ? v : p[v] = leader(p[v], p);
}
 
void unite(int a, int b, vector<int>& p, vector<int>& s) {
    a = leader(a, p);
    b = leader(b, p);
    if (a == b) {
        return;
    }
    if (s[a] > s[b])
        swap(a, b);
    s[b] += s[a];
    p[a] = b;
}
 
void init(int n, vector<int>& p, vector<int>& s) {
    for (int i = 0; i < n; i++)
        p[i] = i, s[i] = 1;
}