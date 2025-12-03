#include <iostream>
#include <vector>
#include <unordered_map>
#include <stdio.h>
#include<array>
#include<fstream>
using namespace std;
 
int w = 129;
long long f[129][129][129];
long long a[129][129][129];
 
void inc(int x, int y, int z, int d) {
    for (int i = x; i < w; i = (i | (i + 1))) {
        for (int j = y; j < w; j = (j | (j + 1))) {
            for (int k = z; k < w; k = (k | (k + 1))) {
                //cout<<f[i][j][k]<<" "<<d << endl;
                f[i][j][k] += d;
                //cout << i << " " << j << " " << k << " " << f[i][j][k] << endl;
            }
        }
    }
}
 
long long sum_pref(int x, int y, int z) {
    long long rez = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
            for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
                rez += f[i][j][k];
                //cout<<"cur_rez "<<i << " " << j << " " << k << " " << f[i][j][k] << endl;
 
            }
        }
    }
    //cout << "rez" << rez << endl;
    return rez;
}
 
long long sum(int x1, int y1, int z1, int x2, int y2, int z2) {
    return sum_pref(x2, y2, z2) - sum_pref(x2, y2, z1 - 1) -
        sum_pref(x1 - 1, y2, z2) - sum_pref(x2, y1 - 1, z2) +
        sum_pref(x1 - 1, y2, z1 - 1) + sum_pref(x2, y1 - 1, z1 - 1) +
        sum_pref(x1 - 1, y1 - 1, z2) - sum_pref(x1 - 1, y1 - 1, z1 - 1);
}
 
int main() {
    /*ios::sync_with_stdio(false);
    cin.tie(NULL);*/
    ifstream in("stars.in");
    ofstream out("stars.out");
 
    int n, m = 1000000;
    in >> n;
    int ch, x, y, z, x1, y1, z1, x2, y2, z2, k;
    for (int i = 0; i < m; ++i) {
        in >> ch;
        if (ch == 3) {
            break;
        }
        if (ch == 1) {
            in >> x >> y >> z >> k;
            inc(x, y, z, k);
        }
        else {
            in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            out << sum(x1, y1 , z1, x2, y2, z2) << endl;
        }
    }
}