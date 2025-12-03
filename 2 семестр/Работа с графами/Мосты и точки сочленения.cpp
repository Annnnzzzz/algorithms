#include <iostream>
#include <vector>
#include<string>
#include<queue>
#include <deque>
#include<stack>
#include <algorithm>
using namespace std;

const int maxn = 1e5;

bool used[maxn];
int h[maxn], d[maxn];

//поиск мостов
void dfs(int v, int p = -1, vector<vector<int>>& g) {
    used[v] = true;
    d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
    for (int u : g[v]) {
        if (u != p) {
            if (used[u]) // если ребро обратное
                d[v] = min(d[v], h[u]);
            else { // если ребро прямое
                dfs(u, v, g);
                d[v] = min(d[v], d[u]);
                if (h[v] < d[u]) {
                    // ребро (v, u) -- мост
                }
            }
        }
    }
}

//Поиск точек сочленения
void dfs(int v, int p = -1, vector<vector<int>>& g) {
    used[v] = 1;
    d[v] = h[v] = (p == -1 ? 0 : h[p] + 1);
    int children = 0; // случай с корнем обработаем отдельно
    for (int u : g[v]) {
        if (u != p) {
            if (used[u])
                d[v] = min(d[v], h[u]);
            else {
                dfs(u, v, g);
                d[v] = min(d[v], d[u]);
                if (h[v]<=d[u] && p != -1) {
                    // v -- точка сочленения
                }
                children++;
            }
        }
    }
    if (p == -1 && children > 1) {
        // v -- корень и точка сочленения
    }
}