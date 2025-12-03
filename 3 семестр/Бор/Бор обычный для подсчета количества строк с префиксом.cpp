#include <bits/stdc++.h>
using namespace std;
struct Trie {
    struct Node {
        map<char, Node*> next;
        int sz; //количество строк с таким префиксом
 
        Node() {
            sz = 0;
        }
    };
 
    Node* root;
 
    Trie() {
        root = new Node();
    }
 
    void insert(const string& val) {
        Node* cur = root;
        cur->sz++;
        for (auto ch : val) {
            if (!cur->next[ch]) cur->next[ch] = new Node();
            cur = cur->next[ch];
            cur->sz++;
        }
    }
 
    int count(const string& s) {
        Node* cur = root;
        for (auto ch : s) {
            if (!cur->next[ch]) {
                return 0;
            }
            cur = cur->next[ch];
        }
        return cur->sz;
    }
 
};

int main() {
	int n;
	cin >> n;
    string s;
    Trie t = Trie();
    while (n-- > 0) {
        cin >> s;
        t.insert(s);
    }
    int m;
    cin >> m;
    while (m-- > 0) {
        cin >> n>>s;
        if (n == 1) {
            t.insert(s);
        }
        else {
            cout<<t.count(s)<<endl;
        }
    }
}
   