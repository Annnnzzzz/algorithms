#include <bits/stdc++.h>
using namespace std;

const int N = 100009;
const int BLOCK = 2137; // Размер блока для алгоритма Мо

struct Update {
    int pos;    // Позиция в массиве
    int val;    // Новое значение
    int prev;   // Предыдущее значение
};

struct Query {
    int l, r;   // Границы запроса
    int t;      // Временная метка (кол-во обновлений до запроса)
    int idx;    // Номер запроса
    
    // Сравнение для сортировки
    bool operator<(const Query& q) const {
        if (l/BLOCK != q.l/BLOCK) return l < q.l;
        if ((l/BLOCK) % 2) return r < q.r;
        return r > q.r;
    }
};

int a[N];           // Исходный массив
Update upd[N];      // Массив обновлений
Query qry[N];       // Массив запросов
int ans[N];         // Массив ответов

// Для подсчета уникальных элементов
unordered_map<int, int> cnt;  // Количество вхождений каждого значения
int unique_cnt;               // Количество уникальных элементов

void add(int val) {
    if (cnt[val] == 0) unique_cnt++;
    cnt[val]++;
}

void remove(int val) {
    cnt[val]--;
    if (cnt[val] == 0) unique_cnt--;
}

void apply_update(int pos, int val, int l, int r) {
    if (l <= pos && pos <= r) {
        remove(a[pos]);
        a[pos] = val;
        add(a[pos]);
    } else {
        a[pos] = val;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int n, m;
    cin >> n >> m;
    
    // Чтение массива
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    int upd_cnt = 0, qry_cnt = 0;
    
    // Обработка операций
    while (m--) {
        int type, x, y;
        cin >> type >> x >> y;
        
        if (type == 1) {
            // Запрос количества уникальных
            qry[++qry_cnt] = {x, y, upd_cnt, qry_cnt};
        } else {
            // Обновление элемента
            upd[++upd_cnt] = {x, y, a[x]};
            a[x] = y;
        }
    }
    
    // Восстановление исходного массива
    for (int i = upd_cnt; i >= 1; i--) 
        a[upd[i].pos] = upd[i].prev;
    
    // Сортировка запросов
    sort(qry + 1, qry + qry_cnt + 1);
    
    // Инициализация
    int cur_l = 1, cur_r = 0, cur_t = 0;
    unique_cnt = 0;
    
    // Обработка запросов
    for (int i = 1; i <= qry_cnt; i++) {
        int l = qry[i].l;
        int r = qry[i].r;
        int t = qry[i].t;
        
        // Синхронизация времени (обновлений)
        while (cur_t < t) {
            cur_t++;
            apply_update(upd[cur_t].pos, upd[cur_t].val, cur_l, cur_r);
        }
        while (cur_t > t) {
            apply_update(upd[cur_t].pos, upd[cur_t].prev, cur_l, cur_r);
            cur_t--;
        }
        
        // Синхронизация границ
        while (cur_r < r) add(a[++cur_r]);
        while (cur_l > l) add(a[--cur_l]);
        while (cur_r > r) remove(a[cur_r--]);
        while (cur_l < l) remove(a[cur_l++]);
        
        // Запоминаем ответ - количество уникальных
        ans[qry[i].idx] = unique_cnt;
    }
    
    // Вывод результатов
    for (int i = 1; i <= qry_cnt; i++)
        cout << ans[i] << '\n';
    
    return 0;
}