#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include<array>
#include<fstream>
using namespace std;

long long f[100002];
long long a[100002];

void inc(int i, int x) {
    int j = i;
    while (j <= 100000) {
        f[j] += x;
        j = j | (j + 1);
    }
}

long long sum_pref(int r) {
    long long i = r, rez = 0;
    while (i >= 0) {
        rez += f[i];
        i = (i & (i + 1)) - 1;
    }
    return rez;
}

long long sum(int l, int r) {
    return sum_pref(r) - sum_pref(l - 1);
}

void init() {
    for (int i = 1; i <= 100002; i++) {
        inc(i, a[i]);
    }
}
int main() {

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    init();
    int ch, x, y;
    for (int i = 0; i < m; ++i) {
        cin >> ch >> x >> y;
        if (ch == 0) {
            cout << sum(x, y) << endl;
        }
        else {
            inc(x, -a[x] + y);
            a[x] = y;
        }
    }
}