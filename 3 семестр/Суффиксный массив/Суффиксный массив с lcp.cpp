#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

using namespace std;

struct SuffixArray {
    int n;
    string s;
    vector<int> sa;
    vector<int> pos;
    vector<int> lcp;

    SuffixArray(string _s) {
        n = _s.size();
        s = _s;
        sa = suffix_array(s);
        pos.resize(n);
        lcp.resize(n - 1);
        for (int i = 0; i < n; ++i) {
            pos[sa[i]] = i;
        }
        find_lcp();
    }

    vector<int> sort_cyclic_shifts(string const& s) {
        int n = s.size();
        const int alphabet = 256;
        vector<int> p(n), c(n), cnt(max(alphabet, n));
        for (auto el : s) cnt[el]++;
        for (int i = 1; i < alphabet; ++i) cnt[i] += cnt[i - 1];
        for (int i = 0; i < n; ++i) p[--cnt[s[i]]] = i;
        c[p[0]] = 0;
        int classes = 1;
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i - 1]]) ++classes;
            c[p[i]] = classes - 1;
        }

        vector<int> pn(n), cn(n);
        for (int h = 0; (1 << h) < n; ++h) {
            for (int i = 0; i < n; i++) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            for (int i = 0; i < classes; ++i) cnt[i] = 0;
            for (auto el : pn) cnt[c[el]]++;
            for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
            cn[p[0]] = 0;
            classes = 1;
            for (int i = 1; i < n; i++) {
                pair<int, int> cur = { c[p[i]], c[(p[i] + (1 << h)) % n] };
                pair<int, int> prev = { c[p[i - 1]], c[(p[i - 1] + (1 << h)) % n] };
                if (cur != prev) ++classes;
                cn[p[i]] = classes - 1;
            }
            c.swap(cn);
        }
        return p;
    }

    vector<int> suffix_array(string s) {
        s += char(31);
        vector<int> sorted_shifts = sort_cyclic_shifts(s);
        sorted_shifts.erase(sorted_shifts.begin());
        return sorted_shifts;
    }

    void find_lcp() {
        int k = 0;
        for (int i = 0; i < n; ++i) {
            if (k > 0) {
                k--;
            }
            //pos[i] - позиция i в suf
            //pos[i] + 1 - позиция соседа i в suf
            // suf[pos[i]+1] - позиция в соседа i по suf в строке 
            if (pos[i] == n - 1) {
                k = 0;
                continue;
            }
            int j = sa[pos[i] + 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
                k++;
            }
            lcp[pos[i]] = k;
        }
    }
};


int main() {
    string s;
    cin >> s;
    SuffixArray suf(s);
    vector<int> count = suf.lcp;
    int n = s.size();
    long long ans = n;
    for (int i = 0; i < n - 1; ++i) {
        ans += n - i - 1;
        ans -= count[i];
    }
    cout << ans;
}