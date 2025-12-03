#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <unordered_set>

using namespace std;

int b = 73;
int p = 10000007;
vector<long long> powers;

vector<long long> prefix_hash(const string& s) {
    vector<long long> v(s.length());
    v[0] = (s[0] - 'a' + 1);
    for (int j = 1; j < s.length(); j++) {
        v[j] = ((v[j - 1] * b) % p + (s[j] - 'a' + 1)) % p;
    }
    return v;
}

void count_powers(int k) {
    powers.resize(k);
    powers[0] = 1;
    for (size_t i = 1; i < k; i++) {
        powers[i] = (powers[i - 1] * b) % p;
    }
    return;
}

int hash_section(int start, int length, vector<long long>& vectors) {
    if (start == 0) {
        return vectors[length - 1];
    }
    return (vectors[start + length - 1] - (vectors[start - 1] * powers[length]) % p + p) % p;
}

struct State {
    // Вершина, на ребре в которую мы находимся.
    int v;
    // Отступ от начала ребра. Т.е. мы находимся в позиции l[v] + pos.
    int pos;
    State(int v, int pos) : v(v), pos(pos) {}
};

struct ST {
    // Переходов из вершины.
    vector<long long> hash;
    vector<map<char, int>> next;
    // Cуфф ссылка, родитель.
    vector<int> link, par;
    // Полуинтервал строки для ребра ведущего в вершину v. Т.е. вершине v соответствует ребро со строкой s[l..r).
    vector<int> l, r;
    // Самый длинный суффикс строки, который не является листом в дереве будет лежать в ptr.
    State ptr;
    // Размер дерева.
    int sz;
    // Строка по которой строим дерево.
    string s;

    int& get(int v, char c) {
        if (!next[v].count(c)) next[v][c] = -1;
        return next[v][c];
    }

    int node() {
        next.emplace_back();
        link.emplace_back(-1);
        par.emplace_back(-1);
        l.emplace_back(0);
        r.emplace_back(0);
        return sz++;
    }

    ST(string s) : ptr(0, 0), sz(0), s(s) {
        node();
        for (int i = 0; i < s.size(); ++i) add(i);
        hash = prefix_hash(s);
    }

    int len(int v) {
        return r[v] - l[v];
    }

    // Делает переход из состояния st по строке s[from, to)
    State go(State st, int from, int to) {
        while (from < to) {
            if (st.pos == len(st.v)) {
                // Мы оказались в вершине v и надо идти по следующему ребру.
                st = State(get(st.v, s[from]), 0);
                // Если такого перехода не существует вернём фиктивное состояние.
                if (st.v == -1) return st; //
            }
            else {
                // Мы находимся где-то на ребре в вершину v.
                // Если следующий символ не совпадает с символом s[from], значит мы не можем идти дальше по этому ребру.
                // Q: Почему мы сравниваем только первый символ, а не все s[from, to)?
                // A: Потому что мы используем go в двух случаях:
                //   1) Когда добавляем один новый символ в дерево. Тогда мы его честно проверим.
                //   2) Когда хотим пройти по уже существующему суффиксу (для поиска суфф. ссылки в suf_link(v)),
                //      но так как это продолжение было в вершине par[v], то оно также будет и в link[par[v]].
                if (s[l[st.v] + st.pos] != s[from]) return { -1, -1 };
                // Если после прохода по s[from, to) мы останемся на этом же ребре, то вернём новое состояние.
                if (to - from < len(st.v) - st.pos) return { st.v, st.pos + to - from };
                // Иначе переместимся в вершину v, изменив from. На следующей итерации цикла получим новое ребро в if.
                from += len(st.v) - st.pos;
                st.pos = len(st.v);
            }
        }
        return st;
    }

    int split(State st) {
        // Если мы прошли всё ребро в v (стоим в v), то просто вернём v.
        if (st.pos == len(st.v)) return st.v;
        // Если мы не прошли ни одного шага на ребре в v, то мы стоим в par[v].
        if (st.pos == 0) return par[st.v];

        int cur = st.v;
        // Создаём новую вершину.
        int mid = node();
        // Меняем переходы. from par[cur] -> cur to par[cur] -> mid -> cur;
        get(par[cur], s[l[cur]]) = mid;
        get(mid, s[l[cur] + st.pos]) = cur;
        // Выставляем нужные границы полуинтервалов.
        l[mid] = l[cur];
        r[mid] = l[cur] + st.pos;
        l[cur] += st.pos;
        // Выставляем нужных родителей.
        par[mid] = par[cur];
        par[cur] = mid;
        return mid;
    }

    int get_link(int v) {
        // Если ссылка уже посчитана, то вернём её.
        if (link[v] != -1) return link[v];
        // Если мы в корне, то ссылка ведёт в корень.
        if (par[v] == -1) return 0;
        // Переходим по суфф ссылке нашего родителя (по ребру из которого мы прошли r[v] - l[v] символов).
        int to = get_link(par[v]);
        // Переходим от полученной вершины по такому же пути и делаем split в этом состоянии.
        // Note: Если мы в ребёнке корня, то нужно оторвать первый символ от строки s[l..r).
        return link[v] = split(go(State(to, len(to)), l[v] + (par[v] == 0), r[v]));
    }

    void add(int pos) {
        while (true) {
            // Проверяем, есть ли переход по новому символу из ptr.
            State nptr = go(ptr, pos, pos + 1);
            // Если есть, то ничего делать не надо, во всех суффиксах st тоже есть переход по этому символу.
            if (nptr.v != -1) {
                ptr = nptr;
                return;
            }
            // Если перехода не оказалось, то нам надо расщепить ребро в текущей позиции, подвесить лист и перейти по суфф ссылке.
            int mid = split(ptr);
            // Создаём лист.
            int leaf = node();
            // Лист всегда будет оставаться листом, при построении. Поэтому можем сразу продлить суффикс из него до s.size().
            l[leaf] = pos;
            r[leaf] = s.size();
            // Подвешиваем лист к текущей вершине
            par[leaf] = mid;
            get(mid, s[pos]) = leaf;

            // Переходим по суфф ссылке
            ptr.v = get_link(mid);
            ptr.pos = len(ptr.v);
            // Если оказались в корне, то заканчиваем.
            if (!mid) break;
        }
    }

    void check(string& pattern) {
        int pos = 0, cur = 0, size=pattern.size();
        vector<long long> p_hash = prefix_hash(pattern);
        while (pos < pattern.size()) {
            cur = get(cur, pattern[pos]);
            if (cur == -1) {
                cout << "NO"<<endl;
                return;
            }
            else {
                int find_len = min(len(cur), size - pos);
                if (hash_section(l[cur], find_len, hash) == hash_section(pos, find_len, p_hash)) {
                    pos+=find_len;
                }
                else {
                    cout << "NO" << endl;
                    return;
                }
            }
        }
        cout << "YES" << endl;
    }
};


int main() {
    string s, pattern;
    cin >> s;
    count_powers(100001);
    ST tree(s);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        cin >> pattern;
        tree.check(pattern);
    }
}