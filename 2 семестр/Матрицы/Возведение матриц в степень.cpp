#include <iostream>
#include <vector>
#include<string>
#include<sstream>
#include <unordered_map>
#include <algorithm>
using namespace std;

vector<vector<int>> mulMat(vector<vector<int>>& m1, vector<vector<int>>& m2, int size_i, int size_j, int mid)
{
    vector<vector<int>> rez (size_i, vector<int>(size_j));
    for (int i = 0; i < size_i; i++) {
        for (int j = 0; j < size_j; j++) {
            rez[i][j] = 0;
            for (int k = 0; k <mid; k++) {
                rez[i][j] += m1[i][k] * m2[k][j];
            }

            cout << rez[i][j] << " ";
        }

        cout << endl;
    }
    return rez;
}

vector<vector<int>> binpow(vector<vector<int>>& m, int n) {
    
    if (n == 1) {
        return m;
    }
    vector<vector<int>> rez;
    if (n % 2 == 1) {
        rez = binpow(m, n - 1);
        rez = mulMat(m, rez, m.size(), m.size(), m.size());
    }
    else {
        rez = binpow(m, n / 2);
        rez = mulMat(rez, rez, m.size(), m.size(), m.size());
    }
    return rez;
}

int main() {
    int n, m, k;
    cin >> n>>m>>k;
    vector<vector<int>> a(n, vector<int>(m));
    vector<vector<int>> b(m, vector<int>(k));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
        
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> b[i][j];
        }

    }
    vector<vector<int>> rez = mulMat(a, b, n, k, m);
    vector<vector<int>> rez2 = binpow(a, 2);

}