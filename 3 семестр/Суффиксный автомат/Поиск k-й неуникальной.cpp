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
    vector<int> size_of_endpos;
    vector<vector<int>> reverse_suf_links;
    vector<long long> num_of_diff_substr;
    vector<long long> dfs_to_count;

    SA() : sz(0) { node(); }

    int node() {
        next.emplace_back();
        link.emplace_back(-1);
        len.emplace_back(0);
        p.emplace_back(-1);
        first_pos.emplace_back(0);
        counting_patterns.emplace_back(1);
        size_of_endpos.emplace_back(0);
        reverse_suf_links.emplace_back();
        num_of_diff_substr.emplace_back(1);
        dfs_to_count.emplace_back(0);
        return sz++;
    }

    int add(int A, char ch, int pos) {
        //создаем новое состояние
        int B = node();
        size_of_endpos[B] = 1;
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
            size_of_endpos[v] += size_of_endpos[w];
        }
    }

    long long dfs_to_init_num_of_diff(int v, vector<bool>& used) {
       
        if (used[v]) {
            return dfs_to_count[v];
        } 
        dfs_to_count[v] = size_of_endpos[v];
        for (auto& w : next[v]) {
            dfs_to_count[v] += dfs_to_init_num_of_diff(w.second, used);
        }

        used[v] = true;
        return dfs_to_count[v];
    }
    
    vector<char> find_kth_smallest(long long k) {
        int cur_pos = 0;
        vector<char> ans;
        while (k > 0) {
            for (auto& w : next[cur_pos]) {
                if (dfs_to_count[w.second] < k) {
                    //cout << num_of_diff_substr[w.second]<<" "<<w.first;
                    k -= dfs_to_count[w.second];
                }
                else {
                    ans.push_back(w.first);
                    cur_pos = w.second;
                    k-= size_of_endpos[w.second];
                    break;
                }
            }
        }
        return ans; 
    }
};

int main() {
    SA a = SA();
    string s, pattern;
    long long k, res=0;
    cin >> s;
    for (int i = 0; i < s.size(); ++i) {
        res = a.add(res, s[i], i+1);
    }
    vector<bool> used(a.sz, false);
    //Отнимаем 1, чтобы не учитывать пустую строку
    a.init_reverse_suf_links();
    a.dfs_of_reverse_links(0);
    a.dfs_to_init_num_of_diff(0, used);
    cin >> k;
    vector<char> answer = a.find_kth_smallest(k);
    //cout << answer.size();
    for (int i = 0; i < answer.size(); ++i) {
        cout << answer[i];
    }
}