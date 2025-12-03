#include <bits/stdc++.h>
using namespace std;
vector<int> z_function(string s) {
	vector<int> z(s.size());
    int l = 0, r = 0;
    for (int i = 1; i < s.size(); ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < s.size() && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
    }
    z[0] = s.size();
    return z;

}