#include <iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;
 
 
int main() {
    ifstream in("stupid_rmq.in");
    ofstream out("stupid_rmq.out");
    int n, k, m, l, r, ans;
    in >> n;
    vector<int> a(n);
    k = 1<<11;
    vector<int> t(1<<12, INT_MAX);
    for (int i = 0; i < n; ++i) {
        in >> a[i];
    }
    for (int i = 0; i < n; i++) {
        t[k - 1 + i] = a[i];
    }
    for (int i = k - 2; i >= 0; i--) {
        t[i] = min(t[2 * i + 1], t[2 * i + 2]);
    }
    in >> m;
    for (int p = 0; p < m; ++p) {
            ans = INT_MAX;
            in >> l >> r;
            l--;
            r--;
            l += k - 1;
            r += k - 1;
            while (r >= l) {
                if (l % 2 == 0) {
                    ans = min(ans,t[l]);
                }
                l = l / 2;
                if (r % 2 == 1) {
                    ans = min(ans,t[r]);
                }
                r = (r / 2) - 1;
            }
            out << ans << endl;
    }
}