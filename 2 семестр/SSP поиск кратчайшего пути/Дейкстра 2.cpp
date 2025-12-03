#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const long long inf=100000000000000;
int root;
vector<vector<pair<int, int>>> g(200002);
vector<long long> weight(200002, inf);
vector<int> p(200002, inf);

void dijkstra(int s) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
	q.push({ 0, s });
	weight[s] = 0;
	while (!q.empty()) {
		pair<int, int> v = q.top();
		q.pop();
		if (v.first > weight[v.second]) {
			continue;
		}
		for (auto u : g[v.second]) {
			//cout << "u " << u.second << endl;
			if (weight[u.second]>weight[v.second]+u.first) {
				weight[u.second] = min(weight[u.second], weight[v.second] + u.first);
				//cout << "weight "<<u.second << " " << weight[u.second] << endl;
				p[u.second] = v.second;
				q.push(u);
			}
		}
	}
}