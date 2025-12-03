#include <iostream>
#include <string>
#include <vector>
using namespace std;

int z_function(string s) {
	vector<int> z(s.size());
    int n=s.size();
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(z[i - l], r - i + 1);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            r = i + z[i] - 1;
            l = i;
        }
        if (z[i]+i==n){
            return i;
        }
    }
    z[0] = s.size();
    return n;

}

int main(){
	int n;
	string s;
	cin >> s;
	cout<<z_function(s);
}