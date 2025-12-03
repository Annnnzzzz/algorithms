#include <iostream>
#include <algorithm>

struct segtree {
    int lb, rb;
    int sum = 0;
    segtree* l = nullptr;
    segtree* r = nullptr;

    segtree(int _lb, int _rb) : lb(_lb), rb(_rb) {}

    ~segtree() {
        delete l;
        delete r;
    }

    void extend() {
        if (!l && lb + 1 < rb) {
            int t = (lb + rb) / 2;
            l = new segtree(lb, t);
            r = new segtree(t, rb);
        }
    }

    void add(int k, int x) {
        extend();
        sum += x;
        if (l) {
            if (k < l->rb)
                l->add(k, x);
            else
                r->add(k, x);
        }
    }

    void update(int k, int newValue) {
        extend();
        if (lb + 1 == rb) {
            sum = newValue; // Обновляем значение
        } else {
            if (k < l->rb)
                l->update(k, newValue);
            else
                r->update(k, newValue);
            sum = (l ? l->sum : 0) + (r ? r->sum : 0); // Обновляем сумму
        }
    }

    int get_sum(int lq, int rq) {
        if (lb >= lq && rb <= rq)
            return sum;
        if (std::max(lb, lq) >= std::min(rb, rq))
            return 0;

        extend();
        return (l ? l->get_sum(lq, rq) : 0) + (r ? r->get_sum(lq, rq) : 0);
    }
};

// // считываем все позиции из запросов в вектор
// vector<ll> positions;
// ...
// // сортируем все позиции и оставляем только уникальные
// sort(positions.begin(), positions.end());
// positions.erase(unique(positions.begin(), positions.end()), positions.end());

// // стром дерево отрезков только на массиве размером positions.size().
// SegTree tr(positions.size());

// // снова проходим по запросам
// for (auto [query] : Queries) {
//     // конвертируем позицию из запроса в индекс массива positions
//     auto pos = distance(positions.begin(), lower_bound(positions.begin(), positions.end(), query.pos));
//     // делаем запрос в дерево отрезков по полученному индексу
//     tr.upd(pos, query.val);
// }

int main() {
    int n = 10; // Размер массива
    segtree tree(0, n); // Создаем дерево для диапазона [0, n)

    // Инициализация массива
    for (int i = 0; i < n; ++i) {
        tree.add(i, i + 1); // Добавляем значения 1, 2, ..., n
    }

    // Получаем сумму отрезка
    std::cout << "Sum from 1 to 4: " << tree.get_sum(1, 4) << std::endl; // Ожидаем 10 (2 + 3 + 4)

    // Обновляем значение на индексе 2
    tree.update(2, 10); // Теперь элемент с индексом 2 будет равен 10

    // Получаем сумму отрезка после обновления
    std::cout << "Sum from 1 to 4 after update: " << tree.get_sum(1, 4) << std::endl; // Ожидаем 15 (2 + 10 + 4)

    return 0;
}