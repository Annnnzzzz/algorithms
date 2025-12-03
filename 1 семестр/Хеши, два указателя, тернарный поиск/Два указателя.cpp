#include <iostream>
#include <string>
#include <vector>
using namespace std;

string generateKthRhyme(int n, long long k) {
    string rhyme(n, 'a');
    vector<int> lastPos(26, -1);
    int nextChar = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 25; j >= 0; --j) {
            if (lastPos[j] == -1) {
                long long combinations = 1LL << (n - i - 1);
                if (k <= combinations) {
                    rhyme[i] = 'a' + j;
                    lastPos[j] = i;
                    nextChar = max(nextChar, j + 1);
                    break;
                }
                k -= combinations;
            }
        }
        if (rhyme[i] == 'a') {
            for (int j = 0; j < nextChar; ++j) {
                if (lastPos[j] != -1) {
                    rhyme[i] = 'a' + j;
                    break;
                }
            }
        }
    }
    return rhyme;
}

int main() {
    int n;
    long long k;
    cin >> n >> k;
    cout << generateKthRhyme(n, k) << endl;
    return 0;
}