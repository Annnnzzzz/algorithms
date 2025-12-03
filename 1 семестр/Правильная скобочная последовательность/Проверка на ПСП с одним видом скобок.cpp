#include <iostream>
#include <vector>
using namespace std;


int main() {
    int q, t;
    cout << "wdn";
    cin >> q;
    cout << "jndjkned" << endl;
    char c;
    int counter = 0;
    int f = -1;
    vector<char> v;
    cout << q << endl;
    while (q-- > 0) {
        cin >> t;
        if (t == 1) {
            cout << t << endl;
            cin >> c;
            if (c == '(') {
                v.push_back('(');
                counter++;
            }
            else {
                v.push_back(')');
                counter--;
            }
            if (counter < 0) {
                f = v.size();
            }
            cout << "1" << endl;
        }
        else {
            char d = v[v.size() - 1];
            if (d == '(') {
                counter--;
            }
            if (d == ')') {
                counter++;
            }
            v.pop_back();
            if (f != -1 && v.size() < f) {
                f = -1;
            }
        }
        if (f == -1 && counter == 0) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
}