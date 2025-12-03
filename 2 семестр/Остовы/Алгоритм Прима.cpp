#include <iostream>
#include <vector>
#include <queue>
#include <climits>


using namespace std;

const int maxn = 1e5, inf = 1e9;
bool used[maxn];
vector< pair<int, int> > g[maxn];
int min_edge[maxn] = {inf}, best_edge[maxn];

// за квадрат

void PRIM(int n) {
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int u = 0; u < n; u++)
            if (!used[u] && (v == -1 || min_edge[u] < min_edge[v]))
                v = u;

        used[v] = 1;
        if (v != -1)
            cout << v << " " << best_edge[v] << endl;

        for (auto e : g[v]) {
            int u = e.first, w = e.second;
            if (w < min_edge[u]) {
                min_edge[u] = w;
                best_edge[u] = v;
            }
        }
    }
}

//за логарифм

vector<int> prim(const vector<vector<pair<int, int>>>& graph) {
    int n = graph.size();
    vector<int> parent(n, -1);     // Родители вершин в MST
    vector<int> key(n, INT_MAX);   // Минимальные веса рёбер
    vector<bool> included(n, false); // Отметки о включении в MST
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Начинаем с вершины 0
    key[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Пропускаем вершину, если она уже в MST
        if (included[u]) continue;
        included[u] = true;

        // Обновляем ключи для всех соседей u
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (!included[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    // Проверка на связность графа
    for (bool inc : included) {
        if (!inc) return {}; // Граф несвязный
    }

    return parent;
}

// Пример использования
int main() {
    // Граф в виде списка смежности (вершина, вес)
    vector<vector<pair<int, int>>> graph = {
        {{1, 1}, {2, 3}},          // Соседи вершины 0
        {{0, 1}, {2, 3}},          // Соседи вершины 1
        {{0, 3}, {1, 3}, {3, 2}},  // Соседи вершины 2
        {{2, 2}}                   // Соседи вершины 3
    };

    vector<int> mst = prim(graph);

    if (mst.empty()) {
        cout << "Граф несвязный!" << endl;
        return 0;
    }

    cout << "Рёбра минимального остовного дерева:\n";
    for (int v = 1; v < graph.size(); ++v) {
        cout << mst[v] << " - " << v << endl;
    }

    return 0;
}