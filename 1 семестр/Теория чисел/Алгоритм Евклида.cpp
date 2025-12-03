#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int GCD(int a, int b)
{
	if (a > b) {
		return GCD(a - b, b);
	}
	else if (a < b) {
		return GCD(a, b-a);
	}
	else {
		return a;
	}
}

int gcd(int a, int b)
{
	if (b == 0) {
		return a;
	}
	return gcd(b, a % b);
}

int main(){
	cout<<gcd(3456, 45);
}