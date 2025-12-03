#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Power(int a, int b, int p) {
    int result = 1;
    a = a % p;
    while (b > 0) {
        if (b % 2 == 1) { // Если b нечетное
            result = (result * a) % p;
        }
        a = (a * a) % p;  // Удваиваем степень
        b =b/ 2;  // Делим b на 2
    }
    return result;
}

int main() {
    vector<int> a = {9,8, 7, 6, 5, 4, 3, 1, 2, 3, 5, 6, 7, 8, 9 };
    cout << Power(2, 10, 10) << endl;
}

//Малая т Ферма: a^p=a  => a^(p-1)=1 => a^(p-2)=a^(-1) - обратное по модулю p