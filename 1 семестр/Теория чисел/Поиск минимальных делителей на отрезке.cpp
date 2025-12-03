#include <vector>
using namespace std;
vector<int> primes_2(int n) {
    vector<int> p(n + 1, 0);
    vector<int> primes; // вектор найденных простых чисел
    for (int i = 2; i <= n; ++i) {
        if (p[i] == 0) { // i - простое
            p[i] = i;
            primes.push_back(i);
        }
        for (int x : primes) {
            if (x > p[i] || 1ll * x * i > n)
                break;
            p[x * i] = x;
        }
    }
    return p;
}
//Простые - все числа для которых p[i]==i
//p[i] содержит наименьший делитель i => 
// можно использовать для факторизации числа 