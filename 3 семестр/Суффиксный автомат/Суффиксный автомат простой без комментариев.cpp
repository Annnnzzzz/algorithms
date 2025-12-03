#include <vector>
#include <map>
using namespace std;
struct SA {
    vector<map<char, int>> next;
    vector<int> link, len, p;
    int sz;

    SA() : sz(0) { node(); }

    int node() {
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
            link[B] = link[C] = D;
            len[D] = len[A] + 1;
            p[D] = A;
            for (; A != -1 && next[A][ch] == C; A = link[A]) {
                next[A][ch] = D;
            }
            break;
        }
        return next[p[B]][ch];
    }
};
