#include <iostream>
#include <vector>
#include <queue>
using namespace std;
 
struct Trie {
    const int B = 31;
    struct Node {
        Node* nxt[2];
        int sz;
        bool is_terminal = false;
 
        Node() {
            nxt[0] = nxt[1] = nullptr;
            sz = 0;
        }
    };
 
    Node* root;
 
    Trie() {
        root = new Node();
    }
 
    void insert(long long val) {
        Node* cur = root;
        cur->sz++;
        for (int i = B - 1; i >= 0; --i) {
            long long b = (val >> i) & 1;
            if (cur->nxt[b] == nullptr) cur->nxt[b] = new Node();
            cur = cur->nxt[b];
            cur->sz++;
        }
        cur->is_terminal = true;
    }
 
    void del(long long val) {
        Node* cur = root;
        cur->sz--;
        for (int i = B - 1; i >= 0; --i) {
            long long b = (val >> i) & 1;
            cur = cur->nxt[b];
            cur->sz--;
        }
        if (cur->sz == 0) {
            cur->is_terminal = false;
        }
    }
 
 
    int get_max(long long x) {
        Node* cur = root;
        long long ans = 0;
        for (int i = B - 1; i >= 0; --i) {
            long long k = (x >> i) & 1;
            ans <<= 1;
            if (cur->nxt[k ^ 1] && cur->nxt[k ^ 1]->sz != 0) {
                cur = cur->nxt[k ^ 1];
                ++ans;
            }
            else{
                cur = cur->nxt[k];
            }
        }
        return ans;
    }
};
 
 
 
int main() {
    int n;
    long long x;
    cin >> n;
    char ch;
    Trie t = Trie();
    t.insert(0);
    while (n-- > 0) {
        cin >> ch >> x;
        if (ch == '+') {
            t.insert(x);
        }
        else if (ch == '-') {
            t.del(x);
        }
        else {
            cout << t.get_max(x) << endl;
        }
    }
}