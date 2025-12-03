#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <set>
#include<fstream>
#include <cctype>
using namespace std;

int n, inf;
vector<vector<int>> d(501, vector<int> (501, 0));
vector<long long> weight(200002, inf);
vector<int> p(200002, inf);
vector<int> use(501);
vector<int> x;
vector<int> sum(501, 0);

void FW(){
	for (int k = 1; k <= n; ++k) {
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
}
//main к другой задаче похожей но не такой
int main() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cin >> d[i][j];
		}
	}
	int ch;
	for (int i = 0; i < n; ++i) {
		cin >> ch;
		x.push_back(ch);
	}
	reverse(x.begin(), x.end());
	FW();
	for (int i = n - 1; i >= 0; --i) {
		cout << sum[i] << " ";
	}
}