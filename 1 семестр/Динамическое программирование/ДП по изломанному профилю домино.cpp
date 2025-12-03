#include <iostream>
using namespace std;

#include <vector>
using namespace std;

int profile(int n, int m) {
    if (n < m) { swap(n, m); }
    vector <vector<vector<int>>> d(n+2,
        vector<vector<int>>(m+1, vector<int>((1 << m)+1)));
    d[0][0][0] = 1;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j < m ; ++j) {
            for (int p = 0; p < (1 << m); ++p) {
                cout << p<<endl;
                if (p & (1 << j)) {
                    d[i][j + 1][p - (1 << j)] += d[i][j][p];
                }
                else {
                    d[i][j + 1][p + (1 << j)] += d[i][j][p];
                    if (j < m-1 && (!(p & (1 << (j + 1))))) {
                        d[i][j + 1][p + (1 << (j + 1))] += d[i][j][p];
                    }
                }
            }
        }
        for (int p = 0; p < (1 << m); p++) {
            d[i + 1][0][p] = d[i][m][p];
        }
    }
    return d[n][0][0];
}

int main()
{
    cout<<profile(8, 3);
}
    