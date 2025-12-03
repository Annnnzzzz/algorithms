#include <iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;
 
 
int main() {
    ifstream in("rmq.in");
    ofstream out("rmq.out");
    int n, k, m, l, r, q, f = 0;
    long long ans;
    in >> n >> m;
    vector<long long> a(n);
    vector<vector<int>> test(m, vector<int>(3));
    k = 1 << 17;
    vector<long long> t(1 << 18, 1000000000000);
    for (int p = 0; p < m; ++p) {
        //ans = INT_MAX;
        in >> l >> r >> q;
        l--;
        r--;
        l += k - 1;
        r += k - 1;
        test[p] = { l, r, q };
        while (r >= l) {
            if (l % 2 == 0) {
                if (t[l] == 1000000000000 || t[l] < q) {
                    t[l] = q;
                }
            }
            l = l / 2;
            if (r % 2 == 1) {
                if (t[r] == 1000000000000 || t[r] < q) {
                    t[r] = q;
                }
            }
            r = (r / 2) - 1;
        }
    }
    for (int i = k - 1; i < k + n - 1; ++i) {
        //cout << t[i] << endl;
        //if (t[i] == 1000000000000) {
            int x = i;
            while (x >= 0) {
                if (t[x] != 1000000000000 && t[i]!=1000000000000 && t[x] > t[i]) {
                    t[i] = t[x];
                }
                else if (t[x] != 1000000000000 && t[i] == 1000000000000) {
                    t[i] = t[x];
                }
                if (x % 2 == 1) {
                    x = x / 2;
                }
                else {
                    x = (x / 2) - 1;
                }
            }
            if (t[i] == 1000000000000) {
                t[i] = INT_MAX;
            }
    }
    for (int i = k - 2; i >= 0; i--) {
        t[i] = min(t[2 * i + 1], t[2 * i + 2]);
    }
    for (int i = 0; i < m; i++) {
        l = test[i][0];
        r = test[i][1];
        ans = 1000000000000;
        while (r >= l) {
            if (l % 2 == 0) {
                ans = min(ans, t[l]);
            }
            l = l / 2;
            if (r % 2 == 1) {
                ans = min(ans, t[r]);
            }
            r = (r / 2) - 1;
        }
        //cout << "ans" << ans;
        if (ans != test[i][2]) {
            f = 1;
            break;
        }
    }
    if (f == 0) {
        out << "consistent" << endl;
        for (int i = k - 1; i < k + n - 1; ++i) {
            out << t[i] << " ";
        }
    }
    else { out << "inconsistent"; }
    return 0;
}