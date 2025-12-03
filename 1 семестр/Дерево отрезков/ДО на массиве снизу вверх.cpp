#include <iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;

int chose_k(int n) {
    int k;
    for (int i = 0; i < 31; i++) {
        if (1 << i >= n * 2) {
            k = i;
            break;
        }
    }
    return k;
}

vector<int> build_sum_tree_of_segments(vector<int>& a, int k)
{
    vector<int> t(1 << k, -1);
    for (int i = 0; i < a.size(); i++)
    {
        t[(1 << (k - 1)) + i - 1] = a[i];
        //cout << (1 << (k - 1)) + i - 1 << " " << a[i] << endl;
    }
    for (int i = (1 << (k - 1)) - 2; i >= 0; i--) {
        t[i] = t[2 * i + 1] + t[2 * i + 2];
        //cout << i << " " << t[i] << endl;
    }
    return t;
}

int sum(vector<int>& t, int l, int r, int k) {
    int ans = 0;
    l--;
    r--;
    l += (1<<(k-1))-1;
    r += (1<<(k-1))-1;
    while (r >= l) {
        if (l % 2 == 0) {
            ans = ans+t[l];
        }
        l = l / 2;
        if (r % 2 == 1) {
            ans = ans+t[r];
        }
        r = (r / 2) - 1;
    }
    return ans;
}

void set(vector<int>& t, int i, int v, int k) {
	i += (1 << (k - 1)) - 1;
	t[i] = v;
	while (i > 0) {
		i = (i - 1) / 2;
		t[i] = t[2 * i + 1] + t[2 * i + 2];
	}
}

int main()
{
    int a, b, n, low, high;
    vector<int> v = { 5, 2, 6, 7, 8, 4, 2, 6 };
    int k=chose_k(v.size());
    vector<int> t = build_sum_tree_of_segments(v, k);
    set(t, 1, 1, k); //нумерация с 1
    for (int i = 0; i < t.size(); i++)
    {
        cout << i << " " << t[i] << endl;

    }
    cout << sum(t, 1, 5, k);
}
