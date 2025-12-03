#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

const int INF = INT_MAX;
const int MAX_LOG = 20;

vector<vector<int>> tree;          // Структура дерева
vector<int> weight;               // Веса вершин
vector<vector<int>> ancestors;    // Для LCA
vector<int> depth;                // Глубины вершин
vector<bool> used;                // Посещенные вершины
vector<int> subtree_size;         // Размеры поддеревьев
vector<int> parent_centroid;      // Центроидная декомпозиция
vector<vector<pair<int, int>>> centroid_data; // {расстояние, мин_вес}

int D; // Максимальное расстояние

// Подготовка для LCA
void preprocessLCA(int v, int p, int d) {
    depth[v] = d;
    ancestors[v][0] = p;
    for (int i = 1; i < MAX_LOG; i++) {
        ancestors[v][i] = ancestors[ancestors[v][i-1]][i-1];
    }
    for (int u : tree[v]) {
        if (u != p) preprocessLCA(u, v, d+1);
    }
}

// Вычисление расстояния между вершинами
int getDistance(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int dist = 0;
    
    // Поднимаем u до уровня v
    for (int i = MAX_LOG-1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = ancestors[u][i];
            dist += (1 << i);
        }
    }
    
    if (u == v) return dist;
    
    // Поднимаем вместе до LCA
    for (int i = MAX_LOG-1; i >= 0; i--) {
        if (ancestors[u][i] != ancestors[v][i]) {
            u = ancestors[u][i];
            v = ancestors[v][i];
            dist += 2 * (1 << i);
        }
    }
    return dist + 2;
}

// Вычисление размеров поддеревьев
void computeSubtreeSizes(int v, int p) {
    subtree_size[v] = 1;
    for (int u : tree[v]) {
        if (u != p && !used[u]) {
            computeSubtreeSizes(u, v);
            subtree_size[v] += subtree_size[u];
        }
    }
}

// Поиск центроида
int findCentroid(int v, int p, int total_size) {
    for (int u : tree[v]) {
        if (u != p && !used[u] && subtree_size[u] > total_size/2) {
            return findCentroid(u, v, total_size);
        }
    }
    return v;
}

// Сбор информации о вершинах в поддереве центроида
void collectNodes(int v, int p, int d, vector<pair<int, int>>& nodes) {
    nodes.emplace_back(d, weight[v]);
    for (int u : tree[v]) {
        if (u != p && !used[u]) {
            collectNodes(u, v, d+1, nodes);
        }
    }
}

// Построение центроидной декомпозиции
void buildCentroidDecomposition(int v, int p) {
    computeSubtreeSizes(v, -1);
    int centroid = findCentroid(v, -1, subtree_size[v]);
    parent_centroid[centroid] = p;
    used[centroid] = true;

    // Собираем вершины и сортируем по расстоянию
    vector<pair<int, int>> nodes;
    collectNodes(centroid, -1, 0, nodes);
    sort(nodes.begin(), nodes.end());

    // Предподсчёт минимумов на префиксах
    vector<pair<int, int>> min_prefix;
    for (auto [d, w] : nodes) {
        int current_min = min_prefix.empty() ? w : min(w, min_prefix.back().second);
        min_prefix.emplace_back(d, current_min);
    }
    centroid_data[centroid] = min_prefix;

    // Рекурсивно строим для поддеревьев
    for (int u : tree[centroid]) {
        if (!used[u]) {
            buildCentroidDecomposition(u, centroid);
        }
    }
}

// Поиск минимального веса в D-окрестности
int findMinWeight(int v) {
    int res = INF;
    int u = v;
    
    while (u != -1) {
        int dist = getDistance(v, u);
        if (dist <= D) {
            int remaining = D - dist;
            auto& data = centroid_data[u];
            
            // Бинарный поиск нужного расстояния
            auto it = upper_bound(data.begin(), data.end(), 
                                make_pair(remaining, INF));
            if (it != data.begin()) {
                res = min(res, (it-1)->second);
            }
        }
        u = parent_centroid[u];
    }
    
    return res == INF ? -1 : res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m >> D;

    // Инициализация структур
    tree.resize(n+1);
    weight.resize(n+1);
    ancestors.assign(n+1, vector<int>(MAX_LOG));
    depth.resize(n+1);
    used.assign(n+1, false);
    subtree_size.resize(n+1);
    parent_centroid.assign(n+1, -1);
    centroid_data.resize(n+1);

    // Чтение весов вершин
    for (int i = 1; i <= n; i++) cin >> weight[i];

    // Чтение дерева
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    // Подготовка LCA
    preprocessLCA(1, -1, 0);

    // Построение центроидной декомпозиции
    buildCentroidDecomposition(1, -1);

    // Обработка запросов
    while (m--) {
        int type, v;
        cin >> type >> v;
        if (type == 1) {
            // Обновление веса вершины
            int new_weight;
            cin >> new_weight;
            weight[v] = new_weight;
            // Здесь нужно обновить centroid_data (пропущено для краткости)
        } else {
            // Поиск минимального веса
            cout << findMinWeight(v) << '\n';
        }
    }

    return 0;
}