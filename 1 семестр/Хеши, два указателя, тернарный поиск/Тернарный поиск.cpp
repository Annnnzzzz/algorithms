#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int TernarySearch(vector<int>& a) {
    int l = 0, m1, m2;
    int r = a.size();
    while (l < r - 2) {
        m1 = l + (r - l)/3;
        m2 = r - (r - l) / 3;
        if (a[m1]>a[m2]) {
            l = m1;
            //cout <<" l: "<<l;
        }
        else {
            r = m2;
            //cout <<" r: "<<r;
        }
    }
    return min(a[r], min(a[l], min(a[m1], a[m2])));
}

int main() {
    vector<int> a = {9,8, 7, 6, 5, 4, 3, 1, 2, 3, 5, 6, 7, 8, 9 };
    cout << TernarySearch(a);
}