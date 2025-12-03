#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <set>
using namespace std;

const int INF = INT_MAX;
const int MAX_LOG = 20;

vector<vector<int>> tree;
vector<int> weight;
vector<vector<int>> ancestors;
vector<int> depth;
vector<bool> used;
vector<int> subtree_size;
vector<int> parent_centroid;

struct CentroidData {
    vector<pair<int, int>> sorted_nodes; // {distance, weight}
    vector<pair<int, int>> min_prefix;   // {distance, min_weight}
    multiset<int> weights;               // Все веса в поддереве (для обновлений)
};
vector<CentroidData> centroid_data;

int D;

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

int getDistance(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    int dist = 0;
    
    for (int i = MAX_LOG-1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = ancestors[u][i];
            dist += (1 << i);
        }
    }
    
    if (u == v) return dist;
    
    for (int i = MAX_LOG-1; i >= 0; i--) {
        if (ancestors[u][i] != ancestors[v][i]) {
            u = ancestors[u][i];
            v = ancestors[v][i];
            dist += 2 * (1 << i);
        }
    }
    return dist + 2;
}

void computeSubtreeSizes(int v, int p) {
    subtree_size[v] = 1;
    for (int u : tree[v]) {
        if (u != p && !used[u]) {
            computeSubtreeSizes(u, v);
            subtree_size[v] += subtree_size[u];
        }
    }
}

int findCentroid(int v, int p, int total_size) {
    for (int u : tree[v]) {
        if (u != p && !used[u] && subtree_size[u] > total_size/2) {
            return findCentroid(u, v, total_size);
        }
    }
    return v;
}

void collectNodes(int v, int p, int d, vector<pair<int, int>>& nodes, multiset<int>& weights) {
    nodes.emplace_back(d, weight[v]);
    weights.insert(weight[v]);
    for (int u : tree[v]) {
        if (u != p && !used[u]) {
            collectNodes(u, v, d+1, nodes, weights);
        }
    }
}

void buildCentroidDecomposition(int v, int p) {
    computeSubtreeSizes(v, -1);
    int centroid = findCentroid(v, -1, subtree_size[v]);
    parent_centroid[centroid] = p;
    used[centroid] = true;

    CentroidData data;
    collectNodes(centroid, -1, 0, data.sorted_nodes, data.weights);
    sort(data.sorted_nodes.begin(), data.sorted_nodes.end());

    // Предподсчет минимумов
    if (!data.sorted_nodes.empty()) {
        data.min_prefix.emplace_back(data.sorted_nodes[0].first, data.sorted_nodes[0].second);
        for (size_t i = 1; i < data.sorted_nodes.size(); i++) {
            int current_min = min(data.sorted_nodes[i].second, data.min_prefix.back().second);
            data.min_prefix.emplace_back(data.sorted_nodes[i].first, current_min);
        }
    }

    centroid_data[centroid] = move(data);

    for (int u : tree[centroid]) {
        if (!used[u]) {
            buildCentroidDecomposition(u, centroid);
        }
    }
}

void updateWeight(int v, int new_weight) {
    int old_weight = weight[v];
    weight[v] = new_weight;
    
    // Обновляем во всех центроидах, содержащих эту вершину
    int u = v;
    while (u != -1) {
        auto& data = centroid_data[u];
        
        // Удаляем старый вес и добавляем новый
        data.weights.erase(data.weights.find(old_weight));
        data.weights.insert(new_weight);
        
        // Пересчитываем минимумы (можно оптимизировать)
        if (!data.sorted_nodes.empty()) {
            data.min_prefix[0].second = data.sorted_nodes[0].second;
            for (size_t i = 1; i < data.sorted_nodes.size(); i++) {
                data.min_prefix[i].second = min(data.sorted_nodes[i].second, data.min_prefix[i-1].second);
            }
        }
        
        u = parent_centroid[u];
    }
}

int findMinWeight(int v) {
    int res = INF;
    int u = v;
    
    while (u != -1) {
        int dist = getDistance(v, u);
        if (dist <= D) {
            int remaining = D - dist;
            auto& data = centroid_data[u];
            
            auto it = upper_bound(data.min_prefix.begin(), data.min_prefix.end(), 
                                make_pair(remaining, INF));
            if (it != data.min_prefix.begin()) {
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

    tree.resize(n+1);
    weight.resize(n+1);
    ancestors.assign(n+1, vector<int>(MAX_LOG));
    depth.resize(n+1);
    used.assign(n+1, false);
    subtree_size.resize(n+1);
    parent_centroid.assign(n+1, -1);
    centroid_data.resize(n+1);

    for (int i = 1; i <= n; i++) cin >> weight[i];

    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    preprocessLCA(1, -1, 0);
    buildCentroidDecomposition(1, -1);

    while (m--) {
        int type, v;
        cin >> type >> v;
        if (type == 1) {
            int new_weight;
            cin >> new_weight;
            updateWeight(v, new_weight);
        } else {
            cout << findMinWeight(v) << '\n';
        }
    }

    return 0;
}