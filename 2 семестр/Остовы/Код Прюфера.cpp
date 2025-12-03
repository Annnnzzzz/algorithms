#include <bits/stdc++.h>
using namespace std;
//Построение за nlogn
const int MAXN = 1e8;
int n;
vector<int> g[MAXN];
int degree[MAXN];
bool killed[MAXN];
 
vector<int> prufer_code() {
	set<int> leaves;
	for (int i=0; i<n; ++i) {
		degree[i] = (int) g[i].size();
		if (degree[i] == 1)
			leaves.insert (i);
		killed[i] = false;
	}
 
	vector<int> result (n-2);
	for (int iter=0; iter<n-2; ++iter) {
		int leaf = *leaves.begin();
		leaves.erase (leaves.begin());
		killed[leaf] = true;
 
		int v;
		for (size_t i=0; i<g[leaf].size(); ++i)
			if (!killed[g[leaf][i]])
				v = g[leaf][i];
 
		result[iter] = v;
		if (--degree[v] == 1)
			leaves.insert (v);
	}
	return result;
}

//Построение за линию 
const int MAXN = 1e8;
int n;
vector<int> g[MAXN];
int parent[MAXN], degree[MAXN];
 
void dfs (int v) {
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to != parent[v]) {
			parent[to] = v;
			dfs (to);
		}
	}
}
 
vector<int> prufer_code() {
	parent[n-1] = -1;
	dfs (n-1);
 
	int ptr = -1;
	for (int i=0; i<n; ++i) {
		degree[i] = (int) g[i].size();
		if (degree[i] == 1 && ptr == -1)
			ptr = i;
	}
 
	vector<int> result;
	int leaf = ptr;
	for (int iter=0; iter<n-2; ++iter) {
		int next = parent[leaf];
		result.push_back (next);
		--degree[next];
		if (degree[next] == 1 && next < ptr)
			leaf = next;
		else {
			++ptr;
			while (ptr<n && degree[ptr] != 1)
				++ptr;
			leaf = ptr;
		}
	}
	return result;
}


//Восстановление за логарифм
vector < pair<int,int> > prufer_decode (const vector<int> & prufer_code) {
	int n = (int) prufer_code.size() + 2;
	vector<int> degree (n, 1);
	for (int i=0; i<n-2; ++i)
		++degree[prufer_code[i]];
 
	set<int> leaves;
	for (int i=0; i<n; ++i)
		if (degree[i] == 1)
			leaves.insert (i);
 
	vector < pair<int,int> > result;
	for (int i=0; i<n-2; ++i) {
		int leaf = *leaves.begin();
		leaves.erase (leaves.begin());
 
		int v = prufer_code[i];
		result.push_back (make_pair (leaf, v));
		if (--degree[v] == 1)
			leaves.insert (v);
	}
	result.push_back (make_pair (*leaves.begin(), *--leaves.end()));
	return result;
}


//Восстановление за линию 
vector < pair<int,int> > prufer_decode_linear (const vector<int> & prufer_code) {
	int n = (int) prufer_code.size() + 2;
	vector<int> degree (n, 1);
	for (int i=0; i<n-2; ++i)
		++degree[prufer_code[i]];
 
	int ptr = 0;
	while (ptr < n && degree[ptr] != 1)
		++ptr;
	int leaf = ptr;
 
	vector < pair<int,int> > result;
	for (int i=0; i<n-2; ++i) {
		int v = prufer_code[i];
		result.push_back (make_pair (leaf, v));
 
		--degree[leaf];
		if (--degree[v] == 1 && v < ptr)
			leaf = v;
		else {
			++ptr;
			while (ptr < n && degree[ptr] != 1)
				++ptr;
			leaf = ptr;
		}
	}
	for (int v=0; v<n-1; ++v)
		if (degree[v] == 1)
			result.push_back (make_pair (v, n-1));
	return result;
}