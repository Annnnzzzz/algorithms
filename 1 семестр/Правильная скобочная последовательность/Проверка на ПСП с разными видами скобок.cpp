#include <iostream>
#include <stack>
using namespace std;

bool check(string s) {
    stack <char> stack;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            stack.push(s[i]);
        }
        else {
            if (stack.empty() || (s[i] - 1 != stack.top() && s[i] - 2 != stack.top())) {
                return false;
            }
            else { stack.pop(); }
        }
    }
    return (stack.empty());
}

int main() {
    string s;
    cin >> s;
    cout << check(s);
}