#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;


struct segtree {
    int lb, rb;
    int val = 0;
    int p = 0;
    segtree* left = 0, * right = 0;
    segtree(int _lb, int _rb) {
        lb = _lb, rb = _rb;
        if (lb < rb) {
            int t = (lb + rb) / 2;
            left = new segtree(lb, t);
            right = new segtree(t + 1, rb);
        }
    }
    void push() {
        left->p += p;
        right->p += p;
        left->val += p * (left->rb - left->lb + 1);
        right->val += p * (right->rb - right->lb + 1);
        p = 0;
    }

    void update(int l, int r, int x) {
        if (r<lb || l>rb) {
            return;
        }
        if (l <= lb && r >= rb) {
            p += x;
            val += x * (rb - lb + 1);
        }
        else {
            push();
            int m = (lb + rb) / 2;
            left->update(l, r, x);
            right->update(l, r, x);
            val = left->val + right->val;
        }
    }

    void get(int n) {
        if (lb == rb) {
		 if (lb <= n) {
     			cout << val << " ";
 		}
        }
        else {
            push();
            left->get(n);
            right->get(n);
        }
    }
};

struct SA {
    //вектор переходов из состояния
    vector<map<char, int>> next;
    vector<map<int, char>> reverse_next;
    //суффиксные ссылки, максимальная длина, состояние с максимальной длинной, из которого пришли в текущее
    vector<long long> link, len, p;
    int sz;
    vector<long long> size_of_endpos;
    vector<vector<int>> reverse_suf_links;
    vector<long long> refren;

    SA() : sz(0) { node(); }

    int node() {
        next.emplace_back();
        reverse_next.emplace_back();
        link.emplace_back(-1);
        len.emplace_back(0);
        p.emplace_back(-1);
        size_of_endpos.emplace_back(0);
        reverse_suf_links.emplace_back();
        refren.emplace_back(0);
        return sz++;
    }

    int add(int A, char ch) {
        //создаем новое состояние
        int B = node();
        size_of_endpos[B] = 1;
        //суффиксная ссылка изначально в корень
        link[B] = 0;
        //длина нового состояния - длина предыдущего + 1
        len[B] = len[A] + 1;
        //родитель
        p[B] = A;
        //Пройдемся по суффиксам уже добавленной строки (родителя) и добавим переход по новой букве, если необходимо
        for (; A != -1; A = link[A]) {
            //если такого перехода нет просто направляем переход в текущее состояние
            if (next[A][ch] == 0) {
                next[A][ch] = B;
                continue;
            }
            //если такой переход есть, идем по нему
            int C = next[A][ch];
            //Если состояние с максимальной длинной из которого могли прийти в С то же состояние, в которое до этого пришли мы,
            //Направляем суффиксную ссылку в С и прерываем, так каак все остальные строки ведущие в С будут суффиксами того,
            //что вело из А и ничего не нарушится, для того состояния уже суфф ссылки посчитаны
            if (p[C] == A) {
                link[B] = C;
                break;
            }
            //Иначе существует более длинная строка ведущее в это же состояние, но она не является суффиксом текущей набранной,
            // от которой шли по ссылкам, предположим, что она является, но суфф ссылка ведет в более короткую, значит, где то уже было состояние, 
            //принимающее эту строку, но автомат детерминирован, поэтому не может принимать 2 разными путями отду строку. Поэтому 
            //делим ноду на 2, одна отвечает одному endpos, другая - другому. Причем более длинная строка меньшему endpos и она будет включаться
            //в endpos более кот=роткой, которую будем ассоциировать с новой вершиной, то есть из нее суфф ссылка теперь будет идти в новую ноду, 
            // как в ноду без какого-то первого символа
            //создаем новую ноду
            int D = node();
            //Копируем C в D, все переходы из состояния C в состояние D
            next[D] = next[C];
            //суффиксная ссылка из С копируется в D
            link[D] = link[C];
            //суффиксная ссылка из B и суффиксная ссылка из C ведут в D
            link[B] = link[C] = D;
            //длина состояния D это длина А, в которое пришли +1
            len[D] = len[A] + 1;
            //Мaксимально длинное состояние из которого пришли в D это А
            p[D] = A;
            //Продолжаем идти по суфф ссылкам А и перенаправляем все в D
            for (; A != -1 && next[A][ch] == C; A = link[A]) {
                next[A][ch] = D;
            }
            break;
        }
        return next[p[B]][ch];
    }

    void number_of_lenth(int n) {
        int k = 1;
        while (k < n) {
            k *= 2;
        }
        segtree tree{ 1,  k};
        for (int i = 1; i < sz; ++i) {
            tree.update(len[link[i]] + 1, len[i], 1);
        }
        tree.get(n);
   }

    
};

int main() {
    SA a = SA();
    int n, m, res=0;
    string s;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        res = a.add(res, s[i]);
    }
    a.number_of_lenth(s.size());
}