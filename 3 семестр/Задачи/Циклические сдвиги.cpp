#include <iostream>
#include <string>
#include <vector>
using namespace std;

int z_function(string s, int sz) {
	int n = s.size();
	vector<int> z(n);
	for (int i = 1; i < n; ++i) {
		int l = 0, r = 0;
		if (i <= r)
			z[i] = min(r - i + 1, z[i - l]);
		while (i + z[i] < n && s[z[i]] == s[i + z[i]])
			++z[i];
		if (i + z[i] - 1 > r)
			l = i;
		r = i + z[i] - 1;
		if (z[i] == sz) {
			return i-sz-1;
		}
	}
	return -1;
}

int main(){
	int n;
	string s1, s2;
	cin >> s1 >> s2;
	n = s1.size();
	string t = s1 + '#' + s2 + s2;
	cout<<z_function(t, n);
}