#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Kadanes_alg(vector<int> a)
{   
    int s = 0, m = 0;
    for (int i = 0; i < a.size(); ++i) {
        s += a[i];
        if (s < 0) {s = 0;}
        m = max(m, s);
    }
    return m;
}

int main() {
    cout<<Kadanes_alg({ -2, 1, -3, 4, -1, 2, 1, -5, 4 });
}