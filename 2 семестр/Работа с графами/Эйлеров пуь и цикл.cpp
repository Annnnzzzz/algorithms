#include <iostream>
#include <vector>
#include<string>
#include<queue>
#include <deque>
#include<stack>
#include <algorithm>
using namespace std;

void DFS(vector<vector<int>>& M, vector<bool>& used, int v) {
    used[v] = true;
    for (auto u : M[v]) {
        if (!used[u]) {
            DFS(M, used, u);
        }
    }
}

//Проверка Графа на эйлеров путь/цикл 
bool checkForEulerPath(vector<vector<int>>& M) {
    int OddVertex = 0;
    for (int v = 0; v < M.size(); ++v) {
        if (M[v].size() % 2 == 1) {
            OddVertex++;
        }
    }
    //Для эйлерово пути, для эйлерового графа >0 
    // (все вершны имеют четную степень)
    if (OddVertex > 2 || OddVertex == 1) {
        return false;
    }
    //Проверка, что существует не более одного КС связности с ребрами
    vector<bool> used(M.size());
    for (int v = 0; v < M.size(); ++v) {
        if (M[v].size() > 0) {
            DFS(M, used, v);
            break;
        }
    }
    for (int v = 0; v < M.size(); ++v) {
        if (M[v].size() > 0 && !used[v]) {
            return false;
        }
    }
    return true;
}

//Построение Эйлерового пути
//Если граф полуэйлеров запускаем из нечетной вершины,
//если нет v в аргументах не нужно
void EulerPath(int v, vector<vector<int>> M) {
    for (int u = 0; u < M.size(); ++u) {
        if (M[u].size() % 2 == 1) {
            v = u; 
            break;
        }
    }
    stack<int> s;
    s.push(v);
    while (!s.empty()) {
        int w = s.top();
        bool found_edge = false;
        for (int u = 0; u < M.size(); ++u) {
            if (M[w][u]) {
                s.push(u);
                M[w][u] = 0;
                found_edge = true;
                break;
            }
        }
        if (!found_edge) {
            s.pop();
            cout << w<<" ";
        }
    }
}

//можем хранить для каждой вершины unordered set со смежными ею, 
//тогда занимаем меньше памяти