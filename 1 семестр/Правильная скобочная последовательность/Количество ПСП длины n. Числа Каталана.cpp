#include <iostream>
#include <vector>
using namespace std;

int count(int n) {
    vector <int> d(n + 1);
    d[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 0; j < i; ++j) {
            d[i] += d[j] * d[i - 1 - j];
        }
    }
    return (d[n]);
}

int main() {
    int s;
    cin >> s;
    cout << count(s);
}