#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;
struct SA {
    //вектор переходов из состояния
    vector<map<char, int>> next;
    //суффиксные ссылки, максимальная длина, состояние с максимальной длинной, из которого пришли в текущее
    vector<int> link, len, p;
    int sz;
    vector<int> first_pos;
    vector<int> counting_patterns;
    vector<int> counting_diff_pos_of_patterns;
    vector<vector<int>> reverse_suf_links;
    vector<long long> num_of_diff_substr;

    SA() : sz(0) { node(); }

    int node() {
        next.emplace_back();
        link.emplace_back(-1);
        len.emplace_back(0);
        p.emplace_back(-1);
        first_pos.emplace_back(0);
        counting_patterns.emplace_back(1);
        counting_diff_pos_of_patterns.emplace_back(0);
        reverse_suf_links.emplace_back();
        num_of_diff_substr.emplace_back(1);
        return sz++;
    }

    int add(int A, char ch, int pos) {
        //создаем новое состояние
        int B = node();
        counting_diff_pos_of_patterns[B] = 1;
        first_pos[B] = pos;
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
            first_pos[D] = first_pos[C];
            //суффиксная ссылка из С копируется в D
            link[D] = link[C];
            //суффиксная ссылка из B и суффиксная ссылка из C ведут в D
            link[B] = link[C] = D;
            //длина состояния D это длина А, в которое пришли +1
            len[D] = len[A] + 1;
            //Минимально длинное состояние из которого пришли в D это А
            p[D] = A;
            //Продолжаем идти по суфф ссылкам А и перенаправляем все в D
            for (; A != -1 && next[A][ch] == C; A = link[A]) {
                next[A][ch] = D;
            }
            break;
        }
        return next[p[B]][ch];
    }

    long long dfs_to_init_num_of_diff(int v, vector<bool>& used) {
        if (used[v] == false) {
            for (auto& w : next[v]) {
                num_of_diff_substr[v] += dfs_to_init_num_of_diff(w.second, used);
            }
            used[v] = true;
        }
        return num_of_diff_substr[v];
    }

    void init_reverse_suf_links() {
        for (int i = 1; i < sz; ++i) {
            if (link[i] != -1) {
                reverse_suf_links[link[i]].push_back(i);
            }
        }
    }
    void dfs_of_reverse_links(int v) {
        for (const auto& w : reverse_suf_links[v]) {
            dfs_of_reverse_links(w);
            counting_diff_pos_of_patterns[v] += counting_diff_pos_of_patterns[w];
        }
    }

    int find_num_of_diff_pos(string& pattern) {
        int cur_pos = 0;
        for (int i = 0; i < pattern.size(); ++i) {
            if (next[cur_pos].find(pattern[i]) == next[cur_pos].end()) {
                return 0;
            }
            cur_pos = next[cur_pos][pattern[i]];
        }
        return counting_diff_pos_of_patterns[cur_pos];
    }

    //сколько существует подстрок с этим паттерном
    void dfs_to_count_patterns(int v, vector<bool>& used) {
        for (const auto& w : next[v]) {
            if (used[w.second] == false) {
                dfs_to_count_patterns(w.second, used);
                used[w.second] = true;
            }
            counting_patterns[v] += counting_patterns[w.second];
            cout << v <<" " << w.first << " " << w.second << " " << w.first << " " << counting_patterns[v] << " " << counting_patterns[w.second] << endl;
        }
    }
    
    //ищем позицию первого вхождения паттерна
    int find_pattern_with_it_pos(string& pattern) {
        int cur_pos = 0;
        for (int i = 0; i < pattern.size(); ++i) {
            if (next[cur_pos].find(pattern[i]) == next[cur_pos].end()) {
                return -1;
            }
            cur_pos = next[cur_pos][pattern[i]];
        }
        return first_pos[cur_pos]-pattern.size() + 1;
    }

    //ищем количество подстрок в которых встречается паттерн
    int find_pattern_with_it_count(string& pattern) {
        int cur_pos = 0;
        for (int i = 0; i < pattern.size(); ++i) {
            if (next[cur_pos].find(pattern[i]) == next[cur_pos].end()) {
                return 0;
            }
            cur_pos = next[cur_pos][pattern[i]];
        }
        return counting_patterns[cur_pos];
    }

    

};

int main() {
    SA a = SA();
    string s, pattern;
    int k, res=0;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        res = a.add(res, s[i], i+1);
    }
    vector<bool> used(a.sz, false);
    //Отнимаем 1, чтобы не учитывать пустую строку
    cout << a.dfs_to_init_num_of_diff(0, used)-1;
}