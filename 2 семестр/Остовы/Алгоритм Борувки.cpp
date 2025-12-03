#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Структура для представления ребра графа
struct Edge {
    int src, dest, weight;
};

// Структура для представления графа
struct Graph {
    int V, E;
    vector<Edge> edges;

    Graph(int v, int e) : V(v), E(e) {}
};

// Структура для системы непересекающихся множеств (DSU)
struct DSU {
    vector<int> parent, rank;

    DSU(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int u) {
        if (parent[u] != u)
            parent[u] = find(parent[u]);
        return parent[u];
    }

    void unite(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;

        if (rank[u] < rank[v])
            parent[u] = v;
        else if (rank[u] > rank[v])
            parent[v] = u;
        else {
            parent[v] = u;
            rank[u]++;
        }
    }
};

// Функция для поиска MST алгоритмом Борувки
vector<Edge> boruvkaMST(Graph& graph) {
    int V = graph.V;
    vector<Edge> mst;
    DSU dsu(V);

    while (mst.size() < V - 1) {
        vector<int> cheapest(V, -1); // Для хранения индекса самого дешевого ребра

        // Находим самое дешевое ребро для каждой компоненты
        for (int i = 0; i < graph.E; ++i) {
            Edge edge = graph.edges[i];
            int set1 = dsu.find(edge.src);
            int set2 = dsu.find(edge.dest);

            if (set1 != set2) {
                if (cheapest[set1] == -1 || graph.edges[cheapest[set1]].weight > edge.weight)
                    cheapest[set1] = i;

                if (cheapest[set2] == -1 || graph.edges[cheapest[set2]].weight > edge.weight)
                    cheapest[set2] = i;
            }
        }

        // Добавляем найденные ребра в MST
        bool added = false;
        for (int i = 0; i < V; ++i) {
            if (cheapest[i] != -1) {
                Edge edge = graph.edges[cheapest[i]];
                int set1 = dsu.find(edge.src);
                int set2 = dsu.find(edge.dest);

                if (set1 != set2) {
                    mst.push_back(edge);
                    dsu.unite(set1, set2);
                    added = true;
                }
            }
        }

        // Если на текущей итерации не добавили ни одного ребра, выходим
        if (!added) break;
    }

    return mst;
}

int main() {
    int V = 4, E = 5;
    Graph graph(V, E);

    // Добавляем ребра (src, dest, weight)
    graph.edges = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    vector<Edge> mst = boruvkaMST(graph);

    cout << "Ребра минимального остовного дерева:\n";
    for (Edge edge : mst) {
        cout << edge.src << " -- " << edge.dest << " (вес: " << edge.weight << ")\n";
    }

    return 0;
}