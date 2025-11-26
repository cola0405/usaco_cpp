#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
using namespace std;

typedef pair<int, pair<int, int>> pii;

int main() {
    int n, m, c, r, k;
    cin >> n >> m >> c >> r >> k;

    // 邻接表存储图
    unordered_map<int, unordered_map<int, int>> g;
    for (int i = 0; i < m; ++i) {
        int u, v, l;
        cin >> u >> v >> l;
        g[u][v] = l;
        g[v][u] = l;
    }

    // 优先队列
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    vector<set<int>> s(n + 1);

    // 初始化优先队列，把充电站放入
    for (int cs = 1; cs <= c; ++cs) {
        pq.push({0, {cs, cs}});
    }

    while (!pq.empty()) {
        pii top = pq.top();
        pq.pop();
        int dis = top.first;
        int x = top.second.first;
        int cs = top.second.second;

        if (s[x].count(cs) || s[x].size() == k || dis > r) continue;
        s[x].insert(cs);

        for (const auto& nxt : g[x]) {
            if (s[nxt.first].size() < k) {
                pq.push({dis + nxt.second, {nxt.first, cs}});
            }
        }
    }

    vector<int> ans;
    for (int i = c + 1; i <= n; ++i) {
        if (s[i].size() >= k) {
            ans.push_back(i);
        }
    }

    cout << ans.size() << endl;
    for (int i : ans) {
        cout << i << endl;
    }

    return 0;
}    