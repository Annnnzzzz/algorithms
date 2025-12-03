#include <vector>
#include <string>
#include <map>
#include <iostream>

using namespace std;
struct SA {
    //вектор переходов из состояния
    vector<map<char, long long>> next;
    vector<map<long long, char>> reverse_next;
    //суффиксные ссылки, максимальная длина, состояние с максимальной длинной, из которого пришли в текущее
    vector<long long> link, len, p;
    long long sz;
    vector<long long> size_of_endpos;
    vector<vector<long long>> reverse_suf_links;
    vector<long long> refren;

    SA() : sz(0) { node(); }

    long long node() {
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

    long long add(long long A, char ch) {
        //создаем новое состояние
        long long B = node();
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
                reverse_next[A][B] = ch;
                continue;
            }
            //если такой переход есть, идем по нему
            long long C = next[A][ch];
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
            long long D = node();
            //Копируем C в D, все переходы из состояния C в состояние D
            next[D] = next[C];
            reverse_next[D] = reverse_next[C];
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
                reverse_next[A][D] = ch;
            }
            break;
        }
        return next[p[B]][ch];
    }

    void init_reverse_suf_links() {
        for (long long i = 1; i < sz; ++i) {
            if (link[i] != -1) {
                reverse_suf_links[link[i]].push_back(i);
            }
        }
    }
    void dfs_of_reverse_links(long long v) {
        for (const auto& w : reverse_suf_links[v]) {
            dfs_of_reverse_links(w);
            size_of_endpos[v] += size_of_endpos[w];
        }
    }

    vector<char> find_max_refren() {
        long long ans = 0;
        long long lenth = 0;
        for (long long i = 1; i < sz; ++i) {
            refren[i] = size_of_endpos[i] * len[i];
            ans = max(ans, refren[i]);
        }
        cout << ans << endl;
        vector<char> a;
        for (long long i = 1; i < sz; ++i) {
            if (refren[i] == ans) {
                while (p[i] != -1) {
                    //cout << "rev_next" << reverse_next[p[i]][i] << endl;
                    a.push_back(reverse_next[p[i]][i]);
                    i = p[i];
                }
                break;
            }
            
        }
        cout << a.size()<<endl;
        return a;
        
    }


    
};

int main() {
    SA a = SA();
    long long n, m, res=0;
    char k;
    cin >> n >> m;
    for (long long i = 0; i < n; ++i) {
        cin >> k;
        res = a.add(res, k);
    }
    a.init_reverse_suf_links();
    a.dfs_of_reverse_links(0);
    vector<char> answer = a.find_max_refren();
    for (long long i = answer.size()-1; i>=0; --i) {
        cout << answer[i] << " ";
    }
   
}
