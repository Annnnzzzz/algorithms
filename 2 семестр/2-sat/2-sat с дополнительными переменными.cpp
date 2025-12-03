#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

class TwoSat {
    int n;
    vector<vector<int>> graph;
    vector<vector<int>> reverse_graph;
    vector<bool> visited;
    vector<int> order;
    vector<int> component;
    int current_component;

public:
    TwoSat(int n) : n(n), graph(2 * n), reverse_graph(2 * n) {}

    void add_implication(int a, int b) {
        graph[a].push_back(b);
        reverse_graph[b].push_back(a);
    }

    void add_clause(int a, int b) {
        add_implication(a ^ 1, b);
        add_implication(b ^ 1, a);
    }

    void dfs1(int u) {
        visited[u] = true;
        for (int v : graph[u]) {
            if (!visited[v]) {
                dfs1(v);
            }
        }
        order.push_back(u);
    }

    void dfs2(int u) {
        visited[u] = true;
        component[u] = current_component;
        for (int v : reverse_graph[u]) {
            if (!visited[v]) {
                dfs2(v);
            }
        }
    }

    vector<bool> solve() {
        visited.assign(2 * n, false);
        order.clear();
        for (int i = 0; i < 2 * n; ++i) {
            if (!visited[i]) {
                dfs1(i);
            }
        }

        visited.assign(2 * n, false);
        component.assign(2 * n, -1);
        current_component = 0;
        for (int i = 2 * n - 1; i >= 0; --i) {
            int u = order[i];
            if (!visited[u]) {
                dfs2(u);
                current_component++;
            }
        }

        vector<bool> assignment(n);
        for (int i = 0; i < n; ++i) {
            if (component[2 * i] == component[2 * i + 1]) {
                return {};
            }
            assignment[i] = component[2 * i] > component[2 * i + 1];
        }
        return assignment;
    }
};

vector<bool> sieve(int max_num) {
    vector<bool> is_prime(max_num + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i * i <= max_num; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max_num; j += i) {
                is_prime[j] = false;
            }
        }
    }
    return is_prime;
}

void factorize(int num, const vector<bool>& is_prime, unordered_map<int, vector<int>>& prime_to_literals, int literal) {
    if (num == 1) return;
    
    if (is_prime[num]) {
        prime_to_literals[num].push_back(literal);
        return;
    }

    int temp = num;
    for (int p = 2; p * p <= temp; ++p) {
        if (is_prime[p] && temp % p == 0) {
            prime_to_literals[p].push_back(literal);
            while (temp % p == 0) {
                temp /= p;
            }
        }
    }
    if (temp > 1 && is_prime[temp]) {
        prime_to_literals[temp].push_back(literal);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, int>> cards(N);
    int max_num = 0;
    for (int i = 0; i < N; ++i) {
        cin >> cards[i].first >> cards[i].second;
        max_num = max(max_num, cards[i].first);
        max_num = max(max_num, cards[i].second);
    }

    vector<bool> is_prime = sieve(max_num);

    unordered_map<int, vector<int>> prime_to_literals;
    for (int i = 0; i < N; ++i) {
        int a = cards[i].first;
        int b = cards[i].second;
        
        // Литералы: 2*i - W_i (лицевая сторона), 2*i+1 - ¬W_i (обратная сторона)
        factorize(a, is_prime, prime_to_literals, 2 * i);
        factorize(b, is_prime, prime_to_literals, 2 * i + 1);
    }

    // Основные переменные: 0..2N-1 (W_i и ¬W_i)
    // Дополнительные переменные начнем с 2N
    int current_var = 2 * N;
    // Оценим максимальное количество дополнительных переменных
    int max_additional = 0;
    for (const auto& entry : prime_to_literals) {
        max_additional += 2 * entry.second.size();
    }
    TwoSat ts(2 * N + max_additional);

    for (const auto& entry : prime_to_literals) {
        const auto& literals = entry.second;
        int k = literals.size();
        if (k == 0) continue;

        // Создаем дополнительные переменные pref и suf
        vector<int> pref_vars(k);
        vector<int> suf_vars(k);
        for (int i = 0; i < k; ++i) {
            pref_vars[i] = current_var++;
            suf_vars[i] = current_var++;
        }

        // Добавляем ограничения
        for (int i = 0; i < k; ++i) {
            int x = literals[i];

            // x_i → pref_i
            ts.add_implication(x, 2 * pref_vars[i]);
            // x_i → suf_i
            ts.add_implication(x, 2 * suf_vars[i]);

            if (i > 0) {
                // x_i → ¬pref_{i-1}
                ts.add_implication(x, 2 * pref_vars[i-1] + 1);
                // pref_i → pref_{i-1}
                ts.add_implication(2 * pref_vars[i], 2 * pref_vars[i-1]);
            }

            if (i < k - 1) {
                // x_i → ¬suf_{i+1}
                ts.add_implication(x, 2 * suf_vars[i+1] + 1);
                // suf_i → suf_{i+1}
                ts.add_implication(2 * suf_vars[i], 2 * suf_vars[i+1]);
            }
        }
    }

    // Добавляем ограничение, что каждая карта должна быть либо лицом вверх, либо вниз
    for (int i = 0; i < N; ++i) {
        ts.add_clause(2 * i, 2 * i + 1);
    }

    vector<bool> assignment = ts.solve();
    if (!assignment.empty()) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

    return 0;
}