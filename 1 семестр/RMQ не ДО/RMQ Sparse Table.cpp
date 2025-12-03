#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<int>> build_sparse_table(vector<int>& a) {
	vector<vector<int>> table(a.size(), vector<int>(29, -1));
	for (int i = 0; i < a.size(); i++) {
		table[i][0] = a[i];
	}
	double r = round(log2(a.size()));
	for (int k = 1; k <= r; k++) {
		for (int i = 0; i <= a.size()-(1 << k); i++) {
			table[i][k] = max(table[i][k - 1], table[i + (1 << (k - 1))][k - 1]);
			cout<<i<<" "<<k<<" "<<table[i][k]<<endl;
		}
	}
	return table;
}

int RMQ_sparse_table(vector<vector<int>>& a, int l, int r) {
	int len = r - l + 1;
	int k;
	for (int i = 29; i >= 0; i--) {
		if ((1 << i) <= len) {
			k = i;
		}
	}
	return max(a[l][k], a[r - (1 << k)][k]);
}