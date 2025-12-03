#include <iostream>
#include <string>
#include <vector>
using namespace std;

int pointers(vector<int>& a, int n) {
    int l=0, ans=0, s=0;
    for (int i=0; i<a.size(); i++) {
        s+=a[i];
        while (s>n){
            s-=a[l];
            l++;
        }
        if (s==n){
            ans++;
        }
    }
    return ans;
}

//Дано множество чисел. Найти максимальное подмножество S,
//для которого max(S) <= 2 * min(S)
int max_min_subset(vector<int>& a) {
    int l = 0, r = 0, ans = 0;
    int min_el = a[0], max_el = a[0];
    cout << "a: ";
    for (int i = 0; i < a.size(); i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    while (r < a.size()) {
        min_el = min(min_el, a[r]);
        max_el = max(max_el, a[r]);
        cout << "r: " << r << " min_el: " << min_el << " max_el: " << max_el << endl;
        while (max_el > 2 * min_el) {
            min_el = min(min_el, a[l]);
            max_el = max(max_el, a[r]);
            cout << "l: " << l << " r: " << r << " min_el: " << min_el << " max_el: " << max_el << endl;
            l++;
        }
        ans = max(ans, r - l + 1);
        cout << "ans: " << ans << endl;
        r++;
    }
    return ans;
}

int main(){
    vector<int> number {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    cout<<pointers(number, 5);
}