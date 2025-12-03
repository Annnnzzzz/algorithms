#include <iostream>
#include <vector>
#include <map>
#include <stdio.h>
#include<algorithm>
#include<fstream>
using namespace std;
 
long long f[2001][2001];
 
void inc(int x, int y, int d) {
    for (int i = x; i < 2001; i = (i | (i + 1))) {
        //cout<<"i"<<i<<endl;
        for (int j = y; j < 2001; j = (j | (j + 1))) {
            //cout<<"j"<<j<<endl;
            f[i][j] += d;
        }
    }
}
 
long long sum_pref(int x, int y) {
    long long rez = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
            rez += f[i][j];
        }
    }
    //cout << "rez" << rez << endl;
    return rez;
}
 
long long sum(int x1,int y1, int x2, int y2) {
    return sum_pref(x2, y2) - sum_pref(x2, y1-1) - sum_pref(x1-1, y2) + sum_pref(x1-1, y1-1);
}
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
   /* ifstream in("inverse.in");
    ofstream out("inverse.out");*/
 
    int n, m, k, len;
    scanf("%d %d %d", &n, &m, &k);
    //cin >> n>>m>>k;
    vector<vector<vector<int>>> lights;
    for (int i = 1; i <= k; i++) {
        scanf("%d", &len);
        //cin >> len;
        vector<vector<int>> coords(len, vector<int>(4));
        for (int j = 0; j < len; j++) {
            coords[j][3] = 1;
            scanf("%d %d %d", &coords[j][0], &coords[j][1], &coords[j][2]);
            //cin >> coords[j][0] >> coords[j][1] >> coords[j][2];
            //cout << coords[j][2]<<endl;
            inc(coords[j][0], coords[j][1], coords[j][2]);
        }
        lights.push_back(coords);
    }
    long long ans=0;
    int q, x;
    int x1, y1, x2, y2;
    char s[6];
    scanf("%d", &q);
    //cin >> q;
    for (int i = 0; i < q; i++) {
        scanf("%s", s);
        //cin >> s;
        if (s[0] == 'S') {
            scanf("%d", &x);
            //cin >> x;
            x--;
            if (lights[x][0][3] == 1) {
                //cout << "yes" << endl;
                for (int j = 0; j < lights[x].size(); j++) {
                    /*cout << lights[x][j][2]<<endl;
                    cout << lights[x][j][2]*(-1)<<endl;*/
                    inc(lights[x][j][0], lights[x][j][1], -lights[x][j][2]);
                }
                lights[x][0][3] = 0;
            }
            else {
                for (int j = 0; j < lights[x].size(); j++) {
                    inc(lights[x][j][0], lights[x][j][1], lights[x][j][2]);
                }
                lights[x][0][3] = 1;
            }
        }
        else {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            //cin >> x1 >> y1 >> x2 >> y2;
            printf("%lld\n", sum(x1, y1, x2, y2));
            //cout << sum(x1, y1, x2, y2) << endl;
        }
    }
	return 0;
}