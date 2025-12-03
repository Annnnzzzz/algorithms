#include <iostream>
#include <vector>
#include <algorithm>
#include <bitset>
using namespace std;

//������������ ��� <W
int max_weight(int W, int n, vector<int>& w) {
    vector <vector<int>> d(n + 1, vector<int>(W + 1));
    d[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        d[i][0] = 1;
        for (int j = 1; j <= W; ++j) {
            if (j - w[i - 1] >= 0) {
                d[i][j] = max(d[i - 1][j], d[i - 1][j - w[i - 1]]);
            }
            else { d[i][j] = d[i - 1][j]; }
        }
    }
    for (int p = W; p >= 0; --p) {
        if (d[n][p] == 1) {
            return p;
        }
    }
}


//������������ ��������� ��� ���� <W + �������������� ������
void max_cost(int W, int n, vector<int>& w, vector<int>& c) {
    vector <vector<int>> d(n + 1, vector<int>(W + 1, INT_MIN));
    d[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        d[i][0] = 0;
        for (int j = 1; j <= W; ++j) {
            if (j - w[i - 1] >= 0) {
                d[i][j] = max(d[i - 1][j], d[i - 1][j - w[i - 1]] + c[i - 1]);
            }
            else { d[i][j] = d[i - 1][j]; }
        }
    }
    int m = 0;
    int j = 1, p = 0;
    while (j <= W) {
        if (m < d[n][j]) {
            m = d[n][j];
            p = j;
        }
        j++;
    }
    cout << m << endl;
    int i = n;
    while (i > 0 && p > 0) {
        if (d[i - 1][p] == d[i][p]) {
            i--;
        }
        else {
            cout << i << " "; //����� ��������
            i--;
            p -= w[i - 1];
        }
    }

}


//�������������� ������
int unlimited(int W, int n, vector<int>& w, vector<int>& c) {
    vector <vector<int>> d(n + 1, vector<int>(W + 1, INT_MIN));
    d[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        d[i][0] = 0;
        for (int j = 1; j <= W; ++j) {
            if (j - w[i - 1] >= 0) {
                d[i][j] = max(d[i - 1][j], d[i][j - w[i - 1]] + c[i - 1]);
            }
            else { d[i][j] = d[i - 1][j]; }
        }
    }
    int m = 0;
    for (int p = W; p >= 0; --p) {
        m = max(m, d[n][p]);
    }
    return m;
}


//������������
int unlimited(int W, int n, vector<int>& w, vector<int>& c) {
    vector <vector<int>> d(n + 1, vector<int>(W + 1, INT_MIN));
    d[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        d[i][0] = 0;
        for (int j = 1; j <= W; ++j) {
            if (j - w[i - 1] >= 0) {
                d[i][j] = max(d[i - 1][j], d[i][j - w[i - 1]] + c[i - 1]);
            }
            else { d[i][j] = d[i - 1][j];}
        }
    }   
    int m = 0;
    for (int p = W; p >= 0; --p) {
        m = max(m, d[n][p]);
    }
    return m;
}

//Ограниченный d[i][j] = max(d[i][j], d[i-1][j - l*w[i]] + l*c[i]), 0<=l<=[j/w[i]]
int main(){
    vector <int> a{ 3,2,4 };
    vector<int> c{ 5,8,10 };
    int s = 7;
    int n = 3;
    cout << max_weight(7, 3, a) << endl;
    max_cost(7, 3, a, c);
    cout << unlimited(7, 3, a, c);
    //Битсет
    bitset<1024> b;
    b[0] = 1;
    for (int i = 0; i < n; i++)
        b |= b << a[i];
}

