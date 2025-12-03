#include <iostream>
#include <vector>
#include<fstream>
#include<algorithm>
using namespace std;

vector<int> factorize(int N) {
    vector<int> result(N);
    for (int i = 2; i * i <= N; i++) {
        while (N % i == 0) {
            result[i]++;
            N /= i;
        }
    }
    if (N != 1) {
        result[N]++;
    }
    return result;
}