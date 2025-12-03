#include <iostream>
#include <string>
using namespace std;

void gen(int n, int c_o, int c_c, string ans) {
    if (c_o + c_c == 2 * n) {
        cout << ans << endl;
    }
    if (c_o < n) {
        gen(n, c_o + 1, c_c, ans + '(');
    }
    if (c_o > c_c) {
        gen(n, c_o, c_c + 1, ans + ')');
    }
}

int main() {
    int n;
    cin >> n;
    gen(n, 0, 0, "");
}
//Подсчет количества скобочных последовательностей заданной длины длины 
//и заданного баланса. dp[n][bal] = dp[n - 1][bal + 1] + dp[n - 1][bal - 1]