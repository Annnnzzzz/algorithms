#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

vector<int> a, cnt;

int ans = 0;
int k;

inline void add(int i) {
    ++cnt[a[i]];
    if (cnt[a[i]] == 1) { //  cnt[a[i]] == 1 <=> не встречалось ни одного a[i]
        ++ans;
    }
}

inline void del(int i) {
    --cnt[a[i]];
    if (cnt[a[i]] == 0) { //  cnt[a[i]] == 0 <=> нет элементов a[i] левее
        --ans;
    }
}

struct query {
    int l, r, i;

    query() {}

    query(int l, int r, int i) : l(l), r(r), i(i) {}
};

inline bool cmp(query& a, query& b) {
    if (a.l / k == b.l / k) {
        return a.r < b.r;
    }
    return a.l < b.l; //  <=> a.l / k < b.l / k
}

int main() {
    int n, q;
    cin >> n >> q;
    k = n / (sqrt(q));
    cout << k;
    a.resize(n);
    cnt.assign(1000000, 0);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<query> qq;
    int i = 0;
    while (q--) {
        int l, r;
        cin >> l >> r;
        qq.push_back(query(l - 1, r - 1, i++));
    }
    sort(qq.begin(), qq.end(), cmp);
    int L = 0, R = -1;
    vector<int> answer(qq.size(), 0);
    for (query x : qq) {
        int l = x.l, r = x.r, i = x.i;
        while (R < r) {
            add(++R);
        }
        while (L > l) {
            add(--L);
        }
        while (R > r) {
            del(R--);
        }
        while (L < l) {
            del(L++);
        }
        answer[i] = ans;
    }
    for (int i : answer) {
        cout << i << '\n';
    }
}