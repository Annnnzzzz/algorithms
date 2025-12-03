#include <iostream>
#include <vector>
#include<fstream>
 
using namespace std;
 
int main()
{	
	int n, m;
	ofstream out;          
	out.open("m3.out");
	ifstream in("m3.in");
	in >> n >> m;
	//cin>>n>>m;
	if (n < m) {
		swap(n, m);
	}
	vector<vector<long long>> prev(m+1, vector<long long>((1 << (m+1)), 0));
	vector<vector<long long>> curr(m+1, vector<long long>((1 << (m+1)), 0));
	for (long long p = 0; p < (1 << (m+1)); ++p) {
		curr[1][p] = 1;
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 1; j < m; j++) {
			for (int p = 0; p < (1 << (m+1)); p++) {
				for (int b = 0; b <= 1; ++b) {
					if ((((p >> (j - 1)) & 7) != b * 7)) {
						int q = ((p & (~(1 << j))) | (b << j));
						curr[j + 1][q] =(curr[j + 1][q]+ curr[j][p])%((1 << 30) + 1);
						//cout<<"i "<<	i << " j " << j+1 << " p " << p << " b " << b << " q " << q << " curr[j+1][q]" << curr[j + 1][q] << endl;
					}
				}
			}
		}
		prev = curr;
		curr.clear();
		curr.resize(m+1, vector<long long>((1 << (m+1)), 0));
		for (int p = 0; p < (1 << (m+1)); ++p) {
			int q1 = (((p & (~(1 << m)))<<1)|(1));
			int q2 = ((p & (~(1 << m)))<<1);
			curr[1][q1] = (curr[1][q1]+prev[m][p])%((1 << 30) + 1);
			curr[1][q2] = (curr[1][q2]+prev[m][p])%((1 << 30) + 1);
		}
	}
	long long ans = 0;
	for (int p = 0; p < (1 << (m)); ++p) {
		ans = (ans + prev[1][p])%((1<<30)+1);
	}
	out << (ans % ((1 << 30) + 1));
}