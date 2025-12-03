#include<iostream>
#include<vector>
using namespace std;
void DFS(vector<vector<int>>& M, vector<bool>& used, int v, vector<int>& tin, vector<int>& tout, int& t) {
	t++;
	tin[v] = t;
	used[v] = true;
	for (auto u : M[v]) {
		if (!used[u]) {
			DFS(M, used, u, tin, tout, t);
		}
	}
	//cout << "DFS out v" <<v<<" t "<< t<<endl;
	tout[v] = t;
	t++;
}