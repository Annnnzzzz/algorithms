#include <string>
#include<vector>
#include <iostream>
using namespace std;

void pref(string& s, vector<int>& pr) {
	pr.resize(s.size(), 0);
	for (int i = 1; i < s.size(); ++i) {
		int k = pr[i - 1];
		while (s[i] != s[k] && k > 0) {
			k = pr[k - 1];
		}
		if (s[i] == s[k]) {
			pr[i] = k + 1;
		}
	}
}