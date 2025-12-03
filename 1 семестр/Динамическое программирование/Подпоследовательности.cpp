#include <iostream>
#include <vector>
#include <utility>
using namespace std;


//�������� ��� ���
int bin(int m, vector<int>& v)
{
    int n = v.size();
    int l = 0, r = n - 1;
    while (r >= l) {
        int mid = (r + l) / 2;
        if (v[mid] < m) {
            l = mid + 1;
        }
        else if (v[mid] >= m) {
            r = mid - 1;
        }
    }
    return l;
}


//���������� ������������ ���������������������
void nvp(vector<int>& a) {
    int n = a.size();
    vector <int> d(n + 1, INT_MAX);
    vector <int> pos(n + 1);
    vector<int>prev(n);
    int len = 0;
    pos[0] = -1;
    d[0] = INT_MIN;
    for (int i = 0; i < n; ++i) {
        int j = bin(a[i], d);
        if (d[j - 1] < a[i] && a[i] < d[j]) {
            d[j] = a[i];
            pos[j] = i;
            prev[i] = pos[j - 1];
            len = max(len, j);
        }
    }
    cout << len << endl;
    //�������������� ������
    int p;
    p = pos[len];
    while (p != -1) {
        cout << a[p] << " ";
        p = prev[p];
    }
    cout << endl;
}
//Или бинпоиском в массиве d найти первое число большее или равное a[i] и обновить его

//���������� ����� ���������������������
void lcs(vector<int>& a, vector<int>& b) {
    int m = a.size(), n = b.size();
    vector<vector<int>> l(m + 1, vector<int>(n + 1));
    vector<vector<int>> ans(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (a[i - 1] == b[j - 1]) {
                l[i][j] = l[i - 1][j - 1] + 1;
                ans[i][j] = 1;
            }
            else {
                if (l[i - 1][j] > l[i][j - 1]) {
                    l[i][j] = l[i - 1][j];
                    ans[i][j] = 2;
                }
                else {
                    l[i][j] = l[i][j - 1];
                    ans[i][j] = 3;
                }
            }
        }
    }
    cout << l[m][n] << endl;
    while (m > 0 && n > 0) {
        if (ans[m][n] == 1) {
            cout << a[m - 1] << " ";
            m--;
            n--;
        }
        else {
            if (ans[m][n] == 2) {
                m--;
            }
            else { n--; }
        }
    }
}

//���������� ����� ������������
int main()
{
    int n, m, l = 0, cur, k = 0;
    cin >> n;
    vector <int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    vector <int> b(m + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
    }
    vector <vector<int>> dp(n + 1, vector<int>(m + 1));
    vector <int> prev(m + 1);
    for (int i = 1; i <= n; ++i) {
        int ind = 0;
        int best = 0;
        for (int j = 1; j <= m; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (a[i] == b[j] && dp[i - 1][j] < best + 1) {
                dp[i][j] = best + 1;
                prev[j] = ind;
                k++;
            }
            if (a[i] > b[j] && dp[i - 1][j] > best) {
                best = dp[i - 1][j];
                ind = j;
            }
        }
    }
    if (k != 0) {
        int pos = 1;
        for (int j = 1; j <= m; ++j) {
            if (dp[n][pos] < dp[n][j]) {
                pos = j;
            }
        }
        vector<int> ans;
        while (pos != 0) {
            ans.push_back(b[pos]);
            pos = prev[pos];
        }
        cout << ans.size() << endl;
        for (int i = ans.size() - 1; i >= 0; --i) {
            cout << ans[i] << " ";
        }
    }
    else { cout << 0 << endl << "   " << endl; }
}

//������������
int main()
{
    int n, k, m, ans = 0;
    cin >> n >> k;
    vector <vector<int>> a(k + 1, vector<int>(n + 1));
    vector <vector<int>> pos(k + 1, vector<int>(n + 1));
    for (int i = 1; i < k + 1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            cin >> a[i][j];
            pos[i][a[i][j]] = j;
        }
    }
    vector <int> dp(n + 1);
    for (int j = 1; j < n + 1; ++j) {
        m = 0;
        for (int p = 1; p < j; ++p) {
            int i = 2;
            while (i < k + 1 && pos[i][a[1][p]] < pos[i][a[1][j]]) {
                ++i;
            }
            if (i == k + 1) {
                m = max(m, dp[p]);
            }
        }
        dp[j] = m + 1;
        ans = max(ans, dp[j]);
    }
    cout << ans << endl;
}

int main() {
    vector <int> a{ 1,3,2,5,4,2,4, 5 };
    vector<int> b{ 2,3,5,4 };
    vector<int> c{ 1,2,3,4 };
    int s = 7;
    int n = 3;
    nvp(a);
    lcs(b, c);
}