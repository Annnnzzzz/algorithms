#include <vector>
using namespace std;
vector<int> divisor(int a)
{
	vector<int> v;
	for (int i = 1; i*i <= a; i++)
	{
		if (a % i == 0) {
			v.push_back(i);
			if (i * i != a) {
				v.push_back(a / i);
			}
		}
	}
	return v;
}