#include <vector>
#include <string>
using namespace std;

int b=73;
int p=10000007;
vector<long long> prefix_hash(const string& s) {
	vector<long long> v(s.length());
	v[0] = (s[0] - 'a' + 1);
	for (int j = 1; j < s.length(); j++) {
		v[j] = ((v[j - 1] * b) % p + (s[j] - 'a' + 1)) % p;
	}
	return v;
}
 
vector<long long> postfix_hash(const string& s) {
	vector<long long> v(s.length());
	v[s.length() - 1] = (s[s.length() - 1] - 'a' + 1);
	long long b1 = b;
	for (int j = s.length() - 2; j >= 0; j--) {
		v[j] = (v[j + 1] + ((s[j] - 'a' + 1)*b1)%p) % p;
		b1=(b1*b)%p;
	}
	return v;
}
 
vector <long long> powers(int k) {
	vector <long long> power_of_b(k);
	power_of_b[0] = 1;
	for (size_t i = 1; i < k; i++) {
		power_of_b[i] = (power_of_b[i - 1] * b) % p;
	}
	return power_of_b;
}
 
bool binary_search(int l, int r, int ans, int k, vector<int>& vectors, vector <int>& powers) {
	while (l <= r) {
		int m = (l + r) / 2;
		//функция проверяющая наличие k кусков с префиксом длинны m и она их нашла) {
		if (check(l, m, ans, k, vectors, powers)) {
			ans=m;
			l=m+1;
		}
		else {
			r = m-1;
		}
	}
}

int hash_section(int start, int length, vector<int>& vectors, vector <int>& powers) {
    return (vectors[start+length-1] - (vectors[start-1]*powers[length])%p + p) % p;
}
		
bool check(int l, int m, int ans, int k, vector<int>& pr_hash, vector <int>& pow) {
	if (hash_section(m, k, pr_hash, pow) == hash_section(l, k, pr_hash, pow)) {
		return true; 
	}
}
