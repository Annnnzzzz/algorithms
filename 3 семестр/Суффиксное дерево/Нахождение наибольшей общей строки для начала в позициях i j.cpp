#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <unordered_set>

using namespace std;

int b = 73;
int p = 10000007;
vector<long long> powers;

int l;

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
    int sz, m=0;
    // Строка по которой строим дерево.
    string s;
    vector<int> counter;
    vector<unordered_set<int>> achievable;
    vector<int> len_of_all;
    vector<int> pos_and_vert;
    vector <int> h;
    vector < vector<int> > jmp;

    void prepr() {
        while ((1 << m) <= sz) {
                    ++m;
        }
        for (int i = 0; i < sz; ++i) {
            jmp[i].resize(m + 1, 0);
        }
        /*jmp[1][0] = 1;
        for (int i = 1; i <= m; ++i) {
            jmp[1][i] = 1;
        }*/
        dfs_lca(0, 0);
        /*cout << "done" << endl;
        for (int i = 0; i < jmp.size(); ++i) {
            for (int j = 0; j < jmp[i].size(); ++j) {
                cout << i << " " << j << " " << jmp[i][j] << endl;
            }
        }*/
    }

    void dfs_lca(int v, int p) {
        h[v] = (v == 0 ? 0 : h[p] + 1);
        jmp[v][0] = p;
        for (int i = 1; i <= m; ++i) {
            jmp[v][i] = jmp[jmp[v][i - 1]][i - 1];
            //cout << jmp[v][i] << endl;
        }
        for (auto w : next[v]) {
            if (w.second != p)
                dfs_lca(w.second, v);
        }
    }


    int lca(int a, int b) {
        if (h[a] < h[b]) {
            swap(a, b);
        }
        int d = h[a] - h[b];
        cout << d << endl;
        for (int k = m; k >= 0; k--) {
            if (d >= (1 << k)) {
                a = jmp[a][k];
                //cout << " a " << a << endl;
                d -= (1 << k);
            }
        }
        cout << a << " " << b;
        if (a == b) {
            cout << "YES";
            return a;
        }
        int a_, b_;
        for (int k = m; k >= 0; k--) {
            cout << "lca "<<a << " " << b << endl;
            a_ = jmp[a][k];
            b_ = jmp[b][k];
            if (a_ != b_) {
                a = a_;
                b = b_;
            }
        }
        return jmp[a][0];
    }


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
        achievable.emplace_back();
        len_of_all.emplace_back();
        pos_and_vert.emplace_back();
        h.emplace_back();
        jmp.emplace_back();
        return sz++;
    }

    ST(string s) : ptr(0, 0), sz(0), s(s) {
        node();
        for (int i = 0; i < s.size(); ++i) add(i);
        hash = prefix_hash(s);
        counter.resize(sz, 0);
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
        int current = par[v];
        vector<int> path = { v };

        while (current != -1 && link[current] == -1) {
            path.push_back(current);
            current = par[current];
        }

        // current теперь либо корень, либо вершина с известной ссылкой
        int to;
        if (current == -1) {
            to = 0;  // корень
        }
        else {
            to = link[current];
        }

        // Вычисляем ссылки для всех вершин на пути
        for (int i = path.size() - 1; i >= 0; --i) {
            int vertex = path[i];
            if (vertex == v) continue;  // исходную вершину обработаем отдельно

            link[vertex] = split(go(State(to, len(to)),
                l[vertex] + (par[vertex] == 0),
                r[vertex]));
            to = link[vertex];
        }

        // И наконец для исходной вершины v
        return link[v] = split(go(State(to, len(to)),
            l[v] + (par[v] == 0),
            r[v]));
        //return link[v] = split(go(State(to, len(to)), l[v] + (par[v] == 0), r[v]));
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
                cout << 0<<endl;
                return;
            }
            else {
                int find_len = min(len(cur), size - pos);
                if (hash_section(l[cur], find_len, hash) == hash_section(pos, find_len, p_hash)) {
                    pos+=find_len;
                }
                else {
                    cout << 0 << endl;
                    return;
                }
            }
        }
        cout << counter[cur] << endl;
    }

    void dfs(int v, pair<int, int>& ans, int n) {
        if (v != 0) {
            if (par[v] == 0) {
                //cout << "l " << l[v] << endl;
                len_of_all[v] = len(v);
            }
            else {
                //cout << "par " << par[v] << endl;
                len_of_all[v] = len_of_all[par[v]]+len(v);
            }
        }

        for (auto& w : next[v]) {
            cout << v << " " << w.second << " " << w.first << " " << 
                l[w.second] << " " << r[w.second]<<" "<<len_of_all[v]<<" "<<n
                <<" "<<2*n+1<<" " << endl;
            if (l[w.second]<=n && n<r[w.second]) {
                pos_and_vert[l[w.second] - len_of_all[v]] = v;
            }
            if (l[w.second] <= (2*n+1) && (2*n+1)<r[w.second]){
                pos_and_vert[l[w.second] - len_of_all[v]] = v;
            }
            dfs(w.second, ans, n);
        }
    }

    pair<int, int> answer(int i, int j, int n) {
        j += n + 1;
        cout << pos_and_vert[i]<<" "<<pos_and_vert[j] << endl;
        int v = lca(pos_and_vert[i], pos_and_vert[j]);
        return {r[v] - len_of_all[v], len_of_all[v]};
    }
};


int main() {
    string s,r,  pattern;
    int n;
    cin >> s;
    n = s.size();
    count_powers(1000001);
    s += '&';
    cin >> r;
    for (int i = 0; i < r.size(); ++i) {
        s += r[i];
    }
    s += '#';
    cout << s << endl;
    ST tree(s);
    tree.prepr();
    //cout <<endl<< "build" << endl;
    //cout << s;
    //cout << "print" << endl;
    pair<int, int> ans{ 0, 0 };
    tree.dfs(0, ans, n);
    for (int i = 0; i < 5; ++i) {
        int p, j;
        cin >> p >> j;
        pair<int, int> ans = tree.answer(p, j, n);
        cout << ans.first << " " << ans.second << endl;
        for (int i = ans.first; i < ans.first + ans.second; ++i) {
               cout << s[i];
        }
    }
}
