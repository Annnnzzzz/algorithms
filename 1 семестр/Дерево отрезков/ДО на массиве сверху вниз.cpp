#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void build_sum_tree_of_segments(vector<int>& a, vector<int>& t, int i, int tl, int tr)
{
	if (tr - tl == 1) {
		t[i] = a[tl];
	}
	else {
		int tm = (tl + tr) / 2;
		build_sum_tree_of_segments(a, t, 2 * i + 1, tl, tm);
		build_sum_tree_of_segments(a, t, 2 * i + 2, tm, tr);
		t[i] = t[2 * i + 1] + t[2 * i + 2];
	}
}

void set(vector<int>& t, int i, int v, int x, int lx, int rx)
{
	if (rx - lx == 1) {
		t[x] = v;
	}
	else {
		int m = (lx + rx) / 2;
		if (i < m) {
			set(t, i, v, 2 * x + 1, lx, m);
		}
		else {
			set(t, i, v, 2 * x + 2, m, rx);
		}
		t[x] = t[2 * x + 1] + t[2 * x + 2];
	}
}

//Правая граница не входит в сумму, нумерация с 0
int sum(vector<int>& t, int l, int r, int x, int lx, int rx)
{
	if (l>=rx || lx>=r) { //заданный и текущий отрезки не пересекаются
		return 0;
	}
	if (lx >= l && rx <= r) {//полностью лежит в заданном отрезке
		return t[x];
	}
	int m = (lx + rx) / 2;
	int sl=sum(t, l, r, 2 * x + 1, lx, m);
	int sr=sum(t, l, r, 2 * x + 2, m, rx);
	return sl+sr;
}

int main()
{
	int a, b, n, low, high;
	vector<int> v = { 5, 2, 6, 7, 8, 4, 2, 6 };
	int k;
	for (int i = 0; i < 31; i++) {
		if (1 << i >= v.size() * 2) {
			k = i;
			break;
		}
	}
	cout << k << endl;
	vector<int> t(1 << k, -1);
	build_sum_tree_of_segments(v, t, 0, 0, v.size());
    set(t, 1, 1, 0, 0, v.size());
	for (int i = 0; i < t.size(); i++)
	{
		cout << i <<" "<<t[i]<<endl;

	}
    cout << sum(t, 1, 5, 0, 0, v.size());
}