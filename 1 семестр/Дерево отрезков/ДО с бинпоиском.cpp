#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;



vector<int> build_sum_tree_of_segments(vector<int>& a)
{	
	int k;
	for (int i = 0; i < 31; i++) {
		if (1 << i >= a.size() * 2) {
			k = i;
			break;
		}
	}
	cout<<k<<endl;
	vector<int> t(1<<k, -1);
	for (int i = 0; i<a.size(); i++)
	{
		t[(1<<(k-1)) + i] = a[i];
		cout<<(1<<(k-1))+i<<" "<<a[i]<<endl;
	}
	for (int i = (1 << (k-1)) - 2; i >= 0; i--) {
		t[i]=t[2*i+1]+t[2*i+2];
		cout<<i<<" "<<t[i]<<endl;
	}
	return t;
}

int MAX_segments_tree(vector<int>& a, int l, int r, int x, int lx, int rx) {
	//cout << 1 << " " << l << " " << r << " " << x << " " << lx << " " << rx << endl;
	if (l > rx || lx > r) {
		//cout << "JBN";
		return -1;
	}
	if (lx >= l && rx <= r) {
		//cout << "    a[x]"<<a[x]<<endl;
		return a[x];
	}
	int m = (lx + rx+((lx+rx)%2)) / 2;
	return max(MAX_segments_tree(a, l, r, 2 * x + 1, lx, m-1), 
MAX_segments_tree(a, l, r, 2 * x + 2, m, rx));
}


bool binary_search(const vector <long long>& vector, long long x) {
	int l = 0;
	int r = vector.size() - 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (vector[mid] == x) {
			return true;
		}
		else if (vector[mid] < x) {
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	return false;
}
int main()
{	
	int a, b, n, low, high;
	vector<int> v={5, 2, 6, 7, 8, 4, 2, 6};
	cin >> a >> b>>n;
	for (int i = 0; i < n; i++)
	{
		cin >> low >> high;
		
	}
}
    
