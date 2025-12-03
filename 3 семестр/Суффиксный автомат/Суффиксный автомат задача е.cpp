#include <string>
#include<vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;


struct SA {
    vector<map<char, int>> next;
    vector<int> link, len, p;
    vector<long long> dp;
    int sz;
    vector<long long> cnt ;
    vector<bool> seen;

    SA() : sz(0) { node(); }

    int node() {
        seen.emplace_back(false);
        cnt.emplace_back(0);
        next.emplace_back();
        link.emplace_back(-1);
        len.emplace_back(0);
        p.emplace_back(-1);
        return sz++;
    }

    int add(int A, char ch) {
        int B = node();
        link[B] = 0;
        len[B] = len[A] + 1;
        p[B] = A;
        cnt[B] = 1;
        for (; A != -1; A = link[A]) {
            if (next[A][ch] == 0) {
                next[A][ch] = B;
                continue;
            }
            int C = next[A][ch];
            if (p[C] == A) {
                link[B] = C;
                break;
            }
            int D = node();
            next[D] = next[C];
            link[D] = link[C];
            link[B] = D;
            link[C] = D;
            len[D] = len[A] + 1;
            p[D] = A;
            cnt[D] = 0;
            for (; A != -1 && next[A][ch] == C; A = link[A]) {
                next[A][ch] = D;
            }
            break;
        }
        return next[p[B]][ch];
    }
    
    void preprocess_counts() {
        vector<int> order(sz);
        for (int i = 0; i < sz; i++) {
            order[i] = i;
        }
        sort(order.begin(), order.end(), [&](int a, int b) {
            return len[a] > len[b];
        });

        for (int i = 0; i < sz; i++) {
            int v = order[i];
            if (link[v] != -1) {
                cnt[link[v]] += cnt[v];
            }
        }
    }

    void find(long long& ans, string& s, int n) {
        int v = 0;
        for (int i = 0; i < s.size(); ++i) {
            char c = s[i];
            //cout << c << endl;
            if (next[v].empty()) {
                v = 0;
            }
            if (next[v].find(c) == next[v].end()) {
                while (p[v] != -1 && next[v].find(c) == next[v].end()) {
                    //cout << c<<" "<<"link " <<link[v]<< endl;
                    v = link[v];
                }
            }
            if (next[v].find(c) != next[v].end()) {
                v = next[v][c];
                //cout << "len"<<len[v] << " " << p[v] << endl;
                if (len[v] >= n && i>=n-1) {
                    while (p[v] != -1 && n < len[link[v]] + 1) {
                        //cout << v<<" ! "<<n<<" "<<p[v] << endl;
                        v = link[v];
                    }
                    if (v != 0) {
                        ans += cnt[v];
                    }
                }
            }
            //cout << c<<" "<<ans << endl;
            
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    string s, x;
    cin >> s>>n;
    SA a{};
    int last = 0;
    for (int i = 0; i < s.size(); ++i) {
        last = a.add(last, s[i]);
    }
    a.preprocess_counts();
    for (int i = 0; i < n; ++i) {
        
        cin >> x;
        int p = x.size();
        x += x;
        x.pop_back();
        //cout << x << endl;
        long long ans = 0;
        a.find(ans, x, p);
        cout << ans << endl;
    }
}