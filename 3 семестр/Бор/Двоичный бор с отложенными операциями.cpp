#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
struct Trie {
    const int B = 21;
    struct Node {
        Node* nxt[2];
        long long num_for_xor = 0;
 
        Node() {
            nxt[0] = nxt[1] = nullptr;
        }
    };
 
    Node* root;
 
    Trie() {
        root = new Node();
    }
 
    void insert(long long val) {
        Node* cur = root;
        for (int i = B - 1; i >= 0; --i) {
            long long b = (val >> i) & 1;
            if (cur->nxt[b] == nullptr) cur->nxt[b] = new Node();
            cur = cur->nxt[b];
        }
    }
 
    long long get_mex(long long y) {
        Node* cur = root;
        long long ans = 0;
        cur->num_for_xor^=y;
        for (int i = B - 1; i >= 0; --i) {
            long long x = cur->num_for_xor;
            long long k = (x >> i) & 1; 
            ans <<= 1;
            if (cur->nxt[0]) {
                cur->nxt[0]->num_for_xor =(cur->nxt[0]->num_for_xor)^x;
            }
            if (cur->nxt[1]) {
                cur->nxt[1]->num_for_xor =(cur->nxt[1]->num_for_xor)^x;
            } 
            cur->num_for_xor = 0;
            if (k == 1) {
                swap(cur->nxt[0], cur->nxt[1]);
            }
            if (cur->nxt[0]) {
                cur = cur->nxt[0];
            }
            else {
                cur = cur->nxt[1];
                ans++;
            }
        }
        return ans;
    }
};
 
 
 
int main() {
    int n, m, k, x;
    cin >> n >> m;
    vector<int> a(1<<19, 0);
    Trie t = Trie();
    for (int i = 0; i < n; ++i) {
        cin >> k;
        a[k]++;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == 0) {
            t.insert(i);
        }
    }
    while (m-- > 0) {
        cin >> x;
        cout << t.get_mex(x) << endl;
    }
}