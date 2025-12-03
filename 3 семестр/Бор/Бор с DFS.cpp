#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
 
struct Trie {
    struct Node {
        map<char, Node*> next;
        bool is_term=false;
 
        Node() {}
    };
 
    Node* root;
 
    Trie() {
        root = new Node();
    }
 
    void insert(const string& val, int i, int j) {
        Node* cur = root;
        for (int p = i; p <= j; ++p) {
            char ch = val[p];
            if (!cur->next[ch]) {
                cur->next[ch] = new Node();
            }
            cur = cur->next[ch];
        }
    }
 
    bool get(const string& val, int i, int j) {
        Node* cur = root;
        for (int p = i; p <= j; ++p) {
            char ch = val[p];
            if (!cur->next[ch]) {
                return false;
            }
            cur = cur->next[ch];
        }
        return true;
    }
 
    void DFS(Node* node, string& a, int k, int& count, int& ans) {
        Node* cur = node;
        int f=0;
        for (const auto& pair : cur->next) {
            if (a[pair.first - 'a'] == '0') {
                count++;
                if (count > k) {
                    count--;
                }
                else {
                    ans++;
                    DFS(pair.second, a, k, count, ans);
                    count--;
                }
            }
            else {
                ans++;
                DFS(pair.second, a, k, count, ans);
            }
        }
    }
};
 
 
int main() {
    string s, a;
    cin >> s >> a;
    int k;
    cin >> k;
    Trie t = Trie();
    int ans = 0;
    for (int i = 0; i < s.size(); i++) {
        t.insert(s, i, s.size() - 1);
    }
    int count = 0;
    t.DFS(t.root, a, k, count, ans);
    cout << ans;
 
}
